fn f(ptr:int) -> void {
    *ptr = *ptr+*ptr;
}

fn main() -> int {
    let x:int=5;
    let y:int=&x;
    let z:int=&y;
    f(*&*&y);
    f(*z);
    return x;
}
