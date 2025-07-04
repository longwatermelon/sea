int var=4;

void f(int ptr) {
    *ptr = 2**ptr;
}

int main() {
    int x=2;
    int y=&var;
    f(&*&*&*&*&*&*y);
    return x+var;
}
