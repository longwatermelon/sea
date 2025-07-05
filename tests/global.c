let var:int=4;

fn f(ptr:int) -> void {
    *ptr = 2**ptr;
}

fn main() -> int {
    let x:int=2;
    let y:int=&var;
    f(&*&*&*&*&*&*y);
    return x+var;
}
