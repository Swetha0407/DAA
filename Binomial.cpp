#include <iostream>
using namespace std;
int main(){
    int n,r;
    cin>>n>>r;
    int dp[n+1][r+1];
    for(int i=0;i<=n;i++){
        for(int j=0;j<=r&&j<=i;j++){
            if(j==0||j==i)
                dp[i][j]=1;
            else
                dp[i][j]=dp[i-1][j-1]+dp[i-1][j];
        }
    }
    cout<<"Binomial Coefficient: "<<dp[n][r];
    return 0;
}