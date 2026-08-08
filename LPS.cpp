#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
int main(){
    string s;
    cin>>s;
    int n=s.length();
    int dp[n][n]={0};
    for(int i=0;i<n;i++)
        dp[i][i]=1;
    for(int len=2;len<=n;len++){
        for(int i=0;i<=n-len;i++){
            int j=i+len-1;
            if(s[i]==s[j])
                dp[i][j]=2+(len==2?0:dp[i+1][j-1]);
            else
                dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
        }
    }
    cout<<"LPS length: "<<dp[0][n-1];
    return 0;
}