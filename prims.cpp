#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int a[n][n];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];

    int key[n],parent[n],vis[n];

    for(int i=0;i<n;i++){
        key[i]=999;
        parent[i]=-1;
        vis[i]=0;
    }

    key[0]=0;

    for(int k=0;k<n;k++){
        int u=-1;
        for(int i=0;i<n;i++)
            if(!vis[i]&&(u==-1||key[i]<key[u]))
                u=i;

        vis[u]=1;

        for(int v=0;v<n;v++)
            if(a[u][v]&&!vis[v]&&a[u][v]<key[v]){
                key[v]=a[u][v];
                parent[v]=u;
            }
    }

    int cost=0;
    cout<<"Edges in MST:\n";

    for(int i=1;i<n;i++){
        cout<<parent[i]<<" - "<<i<<" : "<<a[i][parent[i]]<<endl;
        cost+=a[i][parent[i]];
    }

    cout<<"Minimum cost: "<<cost;
    return 0;
}