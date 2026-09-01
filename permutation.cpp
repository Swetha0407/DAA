#include <iostream>
using namespace std;

int a[20],n;

void perm(int l){
    if(l==n){
        for(int i=0;i<n;i++)
            cout<<a[i]<<" ";
        cout<<endl;
        return;
    }

    for(int i=l;i<n;i++){
        swap(a[l],a[i]);
        perm(l+1);
        swap(a[l],a[i]);
    }
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];

    perm(0);
    return 0;
}