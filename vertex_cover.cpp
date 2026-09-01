#include <iostream>
using namespace std;

int main(){
    int n,e;
    cin>>n>>e;

    int a[n][n]={0};

    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        a[u][v]=a[v][u]=1;
    }

    bool cover[n]={0};

    for(int u=0;u<n;u++){
        for(int v=u+1;v<n;v++){
            if(a[u][v]&&!cover[u]&&!cover[v]){
                cover[u]=cover[v]=1;

                for(int k=0;k<n;k++){
                    a[u][k]=a[k][u]=0;
                    a[v][k]=a[k][v]=0;
                }
            }
        }
    }

    cout<<"Vertex Cover: ";
    for(int i=0;i<n;i++)
        if(cover[i])
            cout<<i<<" ";

    return 0;
}