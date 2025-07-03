int main() {
    int arr = stalloc(4,int);
    *arr = 10;
    *(arr+1*8) = 20;
    *(arr+2*8) = 30;
    *(arr+3*8) = 40;
    return *(arr+2*8);
}
