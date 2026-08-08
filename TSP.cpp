#include <iostream>
#include <vector>
#include <climits>
using namespace std;
int n;
int cost[10][10];
int dp[1<<10][10];
int tsp(int mask,int pos){
    if(mask==(1<<n)-1)
        return cost[pos][0];
    if(dp[mask][pos]!=-1)
        return dp[mask][pos];
    int ans=INT_MAX;
    for(int city=0;city<n;city++){
        if(!(mask&(1<<city))){
            int x=cost[pos][city]+tsp(mask|(1<<city),city);
            ans=min(ans,x);
        }
    }
    return dp[mask][pos]=ans;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>cost[i][j];
    for(int i=0;i<(1<<n);i++)
        for(int j=0;j<n;j++)
            dp[i][j]=-1;
    cout<<"Minimum cost: "<<tsp(1,0);
    return 0;
}