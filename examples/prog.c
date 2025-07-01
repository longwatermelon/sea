int f(int x, int y) {
    int z=2*x+3*y;
    return z+5;
}

int main() {
    int x=5;
    int y=2;
    int z = f(f(1,y),f(x,f(1,1)));
    return z+f(1,2);
}
