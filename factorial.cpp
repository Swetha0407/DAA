#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    long long dp[n+1];
    dp[0]=1;
    for(int i=1;i<=n;i++)
        dp[i]=dp[i-1]*i;
    cout<<"Factorial: "<<dp[n];
    return 0;
}