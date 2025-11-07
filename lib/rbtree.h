struct RbNode {
    key:int,
    val:int,
    color:int,
    left:RbNode*,
    right:RbNode*,
    parent:RbNode*
}

struct RbTree {
    len:int,
    root:RbNode*,
    min:RbNode*,
    max:RbNode*
}

fn rbtree_new() -> RbTree*;
fn rbtree_free(t:RbTree*) -> void;
fn rbtree_size(t:RbTree*) -> int;
fn rbtree_contains(t:RbTree*, k:int) -> int;
fn rbtree_get(t:RbTree*, k:int) -> int;
// Returns 1 if inserted new key, 0 if updated existing
fn rbtree_set(t:RbTree*, k:int, v:int) -> int;
fn rbtree_erase(t:RbTree*, k:int) -> int;
fn rbtree_min_key(t:RbTree*) -> int;
fn rbtree_max_key(t:RbTree*) -> int;

fn rbtree_begin(t:RbTree*) -> RbNode*;
fn rbtree_next(n:RbNode*) -> RbNode*;
fn rbtree_node_key(n:RbNode*) -> int;
fn rbtree_node_val(n:RbNode*) -> int;
