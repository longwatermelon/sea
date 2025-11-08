/*
  Web worker to run the Sea compiler (compiled to WebAssembly via Emscripten).
  Expected companion file: docs/sea.js (built separately), exposing a module
  factory (e.g., SeaModule or Module). See README notes in the PR message.
*/

let sea = null; // Emscripten module instance
let FS = null;
let libsCached = new Map();
let initialized = false;

function post(type, payload = {}) { self.postMessage({ type, ...payload }); }

async function loadModule() {
  if (sea) return sea;
  const moduleConfig = {
    noInitialRun: true,
    print: (x) => console.log(x),
    printErr: (x) => console.error(x),
  };
  try {
    // Try classic non-ES module build first
    importScripts('sea.js');
  } catch (e) {
    // If this fails, we can't load the module here
    throw new Error('Failed to load sea.js in worker. Ensure it is built for worker and placed in docs/.');
  }

  if (typeof self.SeaModule === 'function') {
    sea = await self.SeaModule(moduleConfig);
  } else if (typeof self.Module === 'function') {
    sea = await self.Module(moduleConfig);
  } else if (typeof self.Module === 'object') {
    sea = self.Module; // already instantiated
  } else {
    throw new Error('sea.js did not expose a known factory (SeaModule/Module).');
  }
  FS = sea.FS;
  return sea;
}

async function fetchText(path) {
  const res = await fetch(path);
  if (!res.ok) throw new Error('fetch failed: ' + path);
  return await res.text();
}

async function ensureLibs(libList) {
  if (!FS) throw new Error('FS not ready');
  try { FS.mkdir('/work'); } catch {}
  try { FS.mkdir('/work/lib'); } catch {}
  try { FS.mkdir('/work/examples'); } catch {}
  try { FS.mkdir('/work/.sea'); } catch {}

  for (const p of libList) {
    if (!p.startsWith('lib/')) continue;
    if (!libsCached.has(p)) {
      const txt = await fetchText(p); // relative to docs/
      libsCached.set(p, txt);
    }
    const txt = libsCached.get(p);
    FS.writeFile('/work/' + p, txt);
  }
}

const headerToSea = new Map([
  ['io.h', 'io.sea'],
  ['malloc.h', 'malloc.sea'],
  ['rbtree.h', 'rbtree.sea'],
  ['quicksort.h', 'quicksort.sea'],
  ['set.h', 'set.sea'],
  ['heap.h', 'heap.sea'],
  ['util.h', 'util.sea'],
]);

const seaDeps = new Map([
  ['rbtree.sea', ['malloc.sea']],
  ['set.sea', ['rbtree.sea', 'malloc.sea']],
  ['heap.sea', ['malloc.sea']],
]);

function inferLibsFromSource(src) {
  const libs = new Set(['io.sea', 'util.sea']);
  const rx = /#\s*include\s*"([^"]+)"/g;
  let m;
  while ((m = rx.exec(src)) !== null) {
    const inc = m[1];
    const name = inc.split('/').pop();
    const seaName = headerToSea.get(name);
    if (seaName) libs.add(seaName);
  }
  // add transitive deps
  const queue = Array.from(libs);
  const added = new Set(queue);
  while (queue.length) {
    const k = queue.pop();
    const deps = seaDeps.get(k) || [];
    for (const d of deps) {
      if (!added.has(d)) { added.add(d); libs.add(d); queue.push(d); }
    }
  }
  return Array.from(libs);
}

async function compileToAsm(path, text, libList) {
  await loadModule();
  await ensureLibs(libList);
  // write current source
  FS.writeFile('/work/' + path, text);

  // infer libs from current source
  const needed = inferLibsFromSource(text);
  const args = [ '/work/' + path ];
  for (const name of needed) args.push('/work/lib/' + name);
  args.push('--bundle', '-o', '/work/.sea_out.s', '-arch', 'x86-64', '--no-entry', '-b', '/work/.sea');

  try {
    const rc = sea.callMain(args);
    if (rc !== 0) throw new Error('compiler exited with code ' + rc);
  } catch (err) {
    throw new Error('compile error: ' + (err && err.message ? err.message : String(err)));
  }

  try {
    const data = FS.readFile('/work/.sea_out.s', { encoding: 'utf8' });
    return data;
  } catch (err) {
    throw new Error('missing .sea_out.s output');
  }
}

self.onmessage = async (ev) => {
  const { type } = ev.data || {};
  if (type === 'init') {
    try {
      await loadModule();
      await ensureLibs(ev.data.libs || []);
      initialized = true;
      post('init', { ok: true });
    } catch (err) {
      post('init', { ok: false, msg: String(err && err.message ? err.message : err) });
    }
  } else if (type === 'compile') {
    if (!initialized) { post('compile', { ok: false, msg: 'not initialized' }); return; }
    try {
      const asmText = await compileToAsm(ev.data.path, ev.data.text, ev.data.libs || []);
      post('compile', { ok: true, asmText });
    } catch (err) {
      post('compile', { ok: false, msg: String(err && err.message ? err.message : err) });
    }
  }
};

