#include <iostream>
using namespace std;

int a[20],n,target,x[20];

void subset(int i,int sum){
    if(sum==target){
        cout<<"Subset: ";
        for(int j=0;j<i;j++)
            if(x[j]) cout<<a[j]<<" ";
        cout<<endl;
        return;
    }

    if(i==n||sum>target)
        return;

    x[i]=1;
    subset(i+1,sum+a[i]);

    x[i]=0;
    subset(i+1,sum);
}

int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>a[i];
    cin>>target;

    subset(0,0);
    return 0;
}