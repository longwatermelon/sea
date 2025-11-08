fn malloc(n:int) -> byte*;
fn free(p:byte*) -> void;
fn realloc(p:byte*, n:int) -> byte*;
fn memcpy(dst:byte*, src:byte*, n:int) -> void;
fn arena_reset() -> void;

