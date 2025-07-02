int f(int addr) {
    return *addr;
}

int main() {
    int x=5;
    int y=&x;
    return 1+*f(&y)+1;
}
