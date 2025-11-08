struct Heap {
    cap:int,
    len:int,
    is_max:int,
    data:int*
}

fn heap_new(is_max:int) -> Heap*;
fn heap_free(h:Heap*) -> void;
fn heap_size(h:Heap*) -> int;
fn heap_peek(h:Heap*) -> int;
fn heap_push(h:Heap*, x:int) -> void;
fn heap_pop(h:Heap*) -> int;

