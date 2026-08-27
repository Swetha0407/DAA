#include <iostream>
using namespace std;

int n,a[20][20],path[20];

bool safe(int v,int pos){
    if(!a[path[pos-1]][v])
        return false;

    for(int i=0;i<pos;i++)
        if(path[i]==v)
            return false;

    return true;
}

bool hamilton(int pos){
    if(pos==n)
        return a[path[pos-1]][path[0]];

    for(int v=1;v<n;v++){
        if(safe(v,pos)){
            path[pos]=v;
            if(hamilton(pos+1))
                return true;
            path[pos]=-1;
        }
    }

    return false;
}

int main(){
    cin>>n;

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];

    for(int i=0;i<n;i++)
        path[i]=-1;

    path[0]=0;

    if(hamilton(1)){
        cout<<"Hamiltonian Circuit: ";
        for(int i=0;i<n;i++)
            cout<<path[i]<<" ";
        cout<<path[0];
    }
    else
        cout<<"No Hamiltonian Circuit";

    return 0;
}