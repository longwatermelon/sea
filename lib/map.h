struct MapNode {
    key:int,
    val:int,
    color:int,
    left:MapNode*,
    right:MapNode*,
    parent:MapNode*
}

struct Map {
    len:int,
    root:MapNode*
}

fn map_new() -> Map*;
fn map_free(m:Map*) -> void;
fn map_size(m:Map*) -> int;
fn map_contains(m:Map*, k:int) -> int;
fn map_get(m:Map*, k:int) -> int;
fn map_set(m:Map*, k:int, v:int) -> void;
fn map_erase(m:Map*, k:int) -> int;
fn map_min_key(m:Map*) -> int;
fn map_max_key(m:Map*) -> int;

fn map_begin(m:Map*) -> MapNode*;
fn map_next(n:MapNode*) -> MapNode*;
fn map_node_key(n:MapNode*) -> int;
fn map_node_val(n:MapNode*) -> int;

