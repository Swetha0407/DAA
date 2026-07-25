#include <iostream>
#include <cmath>
using namespace std;
long long karatsuba(long long x,long long y) {
    if (x<10 || y<10)
        return x*y;
    int n=max((int)log10(x)+1,(int)log10(y)+1);
    int m=n/2;
    long long p=pow(10,m);
    long long a=x/p,b=x%p;
    long long c=y/p,d=y%p;
    long long ac=karatsuba(a,c);
    long long bd=karatsuba(b,d);
    long long adbc=karatsuba(a+b,c+d)-ac-bd;
    return ac*p*p+adbc*p+bd;
}
int main() {
    long long x,y;
    cin >> x >> y;
    cout << "Product: "<< karatsuba(x,y);
    return 0;
}