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
    if (x==0) {
        print_char(48);
        return 0;
    }

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

int n;
int k;
int a = galloc(101,int);

void solve() {
    int i=1;
    while (i!=n && k!=0) {
        while (k!=0 && *(a + i*sizeof(int))!=0) {
            *(a + i*sizeof(int)) = *(a + i*sizeof(int))-1;
            *(a + n*sizeof(int)) = *(a + n*sizeof(int))+1;
            k = k-1;
        }
        i = i+1;
    }

    i=1;
    while (i!=n) {
        print_int(*(a + i*sizeof(int)));
        print_char(32);
        i=i+1;
    }
    print_int(*(a + n*sizeof(int)));
    print_char(10);
}

int main() {
    int t = read_int();
    while (t!=0) {
        t=t-1;
        n=read_int();
        k=read_int();

        int ind=1;
        while (ind!=n) {
            *(a + ind*sizeof(int)) = read_int();
            ind = ind+1;
        }
        *(a + ind*sizeof(int)) = read_int();

        solve();
    }
}
