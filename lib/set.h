struct Set {
    cap:int,
    len:int,
    data:int*
}

fn set_new() -> Set*;
fn set_free(s:Set*) -> void;
fn set_size(s:Set*) -> int;
fn set_contains(s:Set*, x:int) -> int;
fn set_insert(s:Set*, x:int) -> int;
fn set_erase(s:Set*, x:int) -> int;
fn set_min(s:Set*) -> int;
fn set_max(s:Set*) -> int;
