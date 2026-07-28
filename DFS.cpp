#include <iostream>
using namespace std;
void dfs(int a[][10],int vis[],int n,int u){
    vis[u]=1;
    cout << u << " ";
    for(int v=0;v<n;v++)
        if(a[u][v]&&!vis[v])
            dfs(a,vis,n,v);
}
int main(){
    int n,s;
    cin >> n;
    int a[10][10],vis[10]={0};
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin >> a[i][j];
    cin >> s;
    cout << "DFS Traversal: ";
    dfs(a,vis,n,s);
    return 0;
}