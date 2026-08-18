#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;

    int key[n],freq[n];
    for(int i=0;i<n;i++)
        cin>>key[i]>>freq[i];

    int cost[n][n];

    for(int i=0;i<n;i++)
        cost[i][i]=freq[i];

    for(int len=2;len<=n;len++){
        for(int i=0;i<=n-len;i++){
            int j=i+len-1;
            cost[i][j]=999999;

            int sum=0;
            for(int k=i;k<=j;k++)
                sum+=freq[k];

            for(int r=i;r<=j;r++){
                int left=(r>i)?cost[i][r-1]:0;
                int right=(r<j)?cost[r+1][j]:0;
                cost[i][j]=min(cost[i][j],left+right+sum);
            }
        }
    }

    cout<<"Minimum cost: "<<cost[0][n-1];
    return 0;
}