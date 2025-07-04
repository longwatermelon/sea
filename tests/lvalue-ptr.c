void f(int ptr) {
    *ptr = *ptr+*ptr;
}

int main() {
    int x=5;
    int y=&x;
    int z=&y;
    f(*&*&y);
    f(*z);
    return x;
}
