int main() {
    int a = stalloc(1,int);
    int i=0;
    while (i!=1) {i=i+1;}
    (*a)=5;
    return 0;
}
