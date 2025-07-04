int arr = galloc(2,int);

int main() {
    *arr = 8;
    *(arr+8)=10;
    *(arr+8) = *arr + *(arr+8)*2;
    return *(arr+8);
}
