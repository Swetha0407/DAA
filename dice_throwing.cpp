#include <iostream>
#include <vector>
using namespace std;
int main(){
    int n,m,sum;
    cin>>n>>m>>sum;
    vector<vector<int>> dp(n+1,vector<int>(sum+1,0));
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=sum;j++){
            for(int k=1;k<=m&&k<=j;k++)
                dp[i][j]+=dp[i-1][j-k];
        }
    }
    cout<<"Ways: "<<dp[n][sum];
    return 0;
}