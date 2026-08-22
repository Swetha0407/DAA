#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge{
    int u,v,w;
};

int find(int p[],int x){
    if(p[x]==x) return x;
    return p[x]=find(p,p[x]);
}

void unite(int p[],int a,int b){
    p[find(p,a)]=find(p,b);
}

int main(){
    int n,e;
    cin>>n>>e;

    Edge a[e];
    for(int i=0;i<e;i++)
        cin>>a[i].u>>a[i].v>>a[i].w;

    int p[n];
    for(int i=0;i<n;i++)
        p[i]=i;

    int cost=0,count=0;

    cout<<"Edges in MST:\n";

    while(count<n-1){
        int cheap[n];

        for(int i=0;i<n;i++)
            cheap[i]=-1;

        for(int i=0;i<e;i++){
            int x=find(p,a[i].u);
            int y=find(p,a[i].v);

            if(x==y) continue;

            if(cheap[x]==-1||a[i].w<a[cheap[x]].w)
                cheap[x]=i;

            if(cheap[y]==-1||a[i].w<a[cheap[y]].w)
                cheap[y]=i;
        }

        for(int i=0;i<n;i++){
            if(cheap[i]!=-1){
                int j=cheap[i];
                int x=find(p,a[j].u);
                int y=find(p,a[j].v);

                if(x!=y){
                    cout<<a[j].u<<" - "<<a[j].v<<" : "<<a[j].w<<endl;
                    cost+=a[j].w;
                    unite(p,x,y);
                    count++;
                }
            }
        }
    }

    cout<<"Minimum cost: "<<cost;
    return 0;
}