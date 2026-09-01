#include <iostream>
using namespace std;

int a[20],x[20],n,r;

void comb(int start,int k){
    if(k==r){
        for(int i=0;i<r;i++)
            cout<<x[i]<<" ";
        cout<<endl;
        return;
    }

    for(int i=start;i<n;i++){
        x[k]=a[i];
        comb(i+1,k+1);
    }
}

int main(){
    cin>>n>>r;
    for(int i=0;i<n;i++)
        cin>>a[i];

    comb(0,0);
    return 0;
}