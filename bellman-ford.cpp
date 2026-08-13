#include <iostream>
using namespace std;

struct Edge{
    int u,v,w;
};

int main(){
    int V,E,s;
    cin>>V>>E;
    Edge e[E];

    for(int i=0;i<E;i++)
        cin>>e[i].u>>e[i].v>>e[i].w;

    cin>>s;

    const int INF=999999;
    int d[V];

    for(int i=0;i<V;i++)
        d[i]=INF;
    d[s]=0;

    for(int i=1;i<V;i++){
        for(int j=0;j<E;j++){
            int u=e[j].u,v=e[j].v,w=e[j].w;
            if(d[u]!=INF&&d[u]+w<d[v])
                d[v]=d[u]+w;
        }
    }

    for(int j=0;j<E;j++){
        int u=e[j].u,v=e[j].v,w=e[j].w;
        if(d[u]!=INF&&d[u]+w<d[v]){
            cout<<"Negative weight cycle detected";
            return 0;
        }
    }

    cout<<"Vertex Distance\n";
    for(int i=0;i<V;i++)
        cout<<i<<" "<<d[i]<<endl;

    return 0;
}