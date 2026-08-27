#include <iostream>
using namespace std;

int n,m,a[20][20],color[20];

bool safe(int v,int c){
    for(int i=0;i<n;i++)
        if(a[v][i]&&color[i]==c)
            return false;
    return true;
}

bool graphColor(int v){
    if(v==n)
        return true;

    for(int c=1;c<=m;c++){
        if(safe(v,c)){
            color[v]=c;
            if(graphColor(v+1))
                return true;
            color[v]=0;
        }
    }
    return false;
}

int main(){
    cin>>n>>m;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];

    if(graphColor(0)){
        cout<<"Vertex Colors:\n";
        for(int i=0;i<n;i++)
            cout<<"Vertex "<<i<<" : Color "<<color[i]<<endl;
    }
    else
        cout<<"No solution";

    return 0;
}