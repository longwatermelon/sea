int buffer = 0;

int read_char() {
    syscall(0, 0, &buffer, 1);
    return buffer;
}

void print_char(int c) {
    buffer = c;
    syscall(1, 1, &buffer, 1);
}

void read_skip() {
    read_char();
}

int read_int() {
    int ch = read_char();
    int res=0;
    while (ch != 10 && ch != 32) {
        res = res*10 + ch-48;
        ch = read_char();
    }
    return res;
}

void print_int(int x) {
    int arr = stalloc(20,int);
    int ind=0;
    while (x!=0) {
        int rem = x%10;
        x = x/10;
        *(arr+ind*sizeof(int))=rem+48;
        ind = ind+1;
    }

    while (ind!=0) {
        ind = ind-1;
        print_char(*(arr + ind*sizeof(int)));
    }
}


int n=4;
int main() {
    int arr = stalloc(4,int);
    int ind=0;
    while (ind!=n) {
        *(arr + ind*sizeof(int)) = read_int();
        ind = ind+1;
    }
    print_int(*arr+*(arr+8)+*(arr+16)+*(arr+24));
    return 0;
}
