#include <iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int a[n][n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];
    int s;
    cin>>s;
    const int INF=999;
    int dist[n],vis[n];
    for(int i=0;i<n;i++){
        dist[i]=INF;
        vis[i]=0;
    }
    dist[s]=0;
    for(int k=0;k<n;k++){
        int u=-1;
        for(int i=0;i<n;i++)
            if(!vis[i]&&(u==-1||dist[i]<dist[u]))
                u=i;
        vis[u]=1;
        for(int v=0;v<n;v++)
            if(a[u][v]!=0&&!vis[v]&&dist[u]+a[u][v]<dist[v])
                dist[v]=dist[u]+a[u][v];
    }
    cout<<"Vertex Distance\n";
    for(int i=0;i<n;i++)
        cout<<i<<" "<<dist[i]<<endl;
    return 0;
}