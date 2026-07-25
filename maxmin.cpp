#include <iostream>
using namespace std;
struct MinMax {
    int min,max;
};
MinMax findMinMax(int arr[],int l,int r){
    MinMax m,left,right;
    if(l==r) {
        m.min=m.max=arr[l];
        return m;
    }
    if(r==l+1) {
        if(arr[l]<arr[r]) {
            m.min=arr[l];
            m.max=arr[r];
        }
        else {
            m.min=arr[r];
            m.max=arr[l];
        }
        return m;
    }
    int mid=(l+r)/2;
    left=findMinMax(arr,l,mid);
    right=findMinMax(arr,mid+1,r);
    m.min=(left.min<right.min)?left.min:right.min;
    m.max=(left.max>right.max)?left.max:right.max;
    return m;
}

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++)
        cin>>arr[i];
    MinMax ans=findMinMax(arr,0,n-1);
    cout<<"Minimum: "<<ans.min<<endl;
    cout<<"Maximum: "<<ans.max;
    return 0;
}