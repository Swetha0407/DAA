#include <iostream>
using namespace std;
int main(){
    int n,s;
    cin >> n;
    int a[n][n],vis[n]={0},q[n],f=0,r=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> a[i][j];
    cin >> s;
    q[r++]=s;
    vis[s]=1;
    cout << "BFS Traversal: ";
    while(f<r){
        int u=q[f++];
        cout<<u<<" ";
        for(int v=0;v<n;v++){
            if(a[u][v]&&!vis[v]){
                vis[v]=1;
                q[r++]=v;
            }
        }
    }
    return 0;
}