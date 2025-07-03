int buffer = 0;

int read_char() {
    syscall(0, 0, &buffer, 1);
    return buffer;
}

void print_char(int c) {
    buffer = c;
    syscall(1, 1, &buffer, 1);
}

int main() {
    int x = read_char();
    print_char(x);
    print_char(10);
    return x;
}
