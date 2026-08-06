#include <iostream>
#include <vector>
using namespace std;
vector<long long> dp;
long long fib(int n){
    if(n<=1)
        return n;
    if(dp[n]!=-1)
        return dp[n];
    return dp[n]=fib(n-1)+fib(n-2);
}
int main(){
    int n;
    cin>>n;
    dp.assign(n+1,-1);
    cout<<"Fibonacci: "<<fib(n);
    return 0;
}