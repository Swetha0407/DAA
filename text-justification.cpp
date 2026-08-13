#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    int n,W;
    cin>>n>>W;
    vector<int> len(n);
    for(int i=0;i<n;i++)
        cin>>len[i];

    vector<int> dp(n+1,INT_MAX);
    dp[n]=0;

    for(int i=n-1;i>=0;i--){
        int spaces=0;
        for(int j=i;j<n;j++){
            spaces+=len[j];
            if(j>i) spaces++;
            if(spaces>W) break;

            int extra=W-spaces;
            int cost=(j==n-1)?0:extra*extra;

            if(dp[j+1]!=INT_MAX)
                dp[i]=min(dp[i],cost+dp[j+1]);
        }
    }

    cout<<"Minimum cost: "<<dp[0];
    return 0;
}