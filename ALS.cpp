#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int a[2][n],t[2][n],e[2],x[2];
    for(int i=0;i<2;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];
    for(int i=0;i<2;i++)
        for(int j=0;j<n-1;j++)
            cin>>t[i][j];
    cin>>e[0]>>e[1];
    cin>>x[0]>>x[1];
    int dp[2][n];
    dp[0][0]=e[0]+a[0][0];
    dp[1][0]=e[1]+a[1][0];
    for(int j=1;j<n;j++){
        dp[0][j]=min(dp[0][j-1]+a[0][j], dp[1][j-1]+t[1][j-1]+a[0][j]);
        dp[1][j]=min(dp[1][j-1]+a[1][j], dp[0][j-1]+t[0][j-1]+a[1][j]);
    }
    cout<<"Minimum time: "<<min(dp[0][n-1]+x[0], dp[1][n-1]+x[1]);
    return 0;
}