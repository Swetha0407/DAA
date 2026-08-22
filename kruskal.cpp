#include <iostream>
#include <algorithm>
using namespace std;

struct Edge{
    int u,v,w;
};

bool cmp(Edge a,Edge b){
    return a.w<b.w;
}

int find(int p[],int x){
    if(p[x]==x)
        return x;
    return p[x]=find(p,p[x]);
}

int main(){
    int n,e;
    cin>>n>>e;

    Edge a[e];
    for(int i=0;i<e;i++)
        cin>>a[i].u>>a[i].v>>a[i].w;

    sort(a,a+e,cmp);

    int p[n];
    for(int i=0;i<n;i++)
        p[i]=i;

    int cost=0,count=0;

    cout<<"Edges in MST:\n";

    for(int i=0;i<e&&count<n-1;i++){
        int x=find(p,a[i].u);
        int y=find(p,a[i].v);

        if(x!=y){
            cout<<a[i].u<<" - "<<a[i].v<<" : "<<a[i].w<<endl;
            cost+=a[i].w;
            p[x]=y;
            count++;
        }
    }

    cout<<"Minimum cost: "<<cost;
    return 0;
}