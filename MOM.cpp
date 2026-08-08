#include <iostream>
#include <algorithm>
using namespace std;
int median(int a[],int n){
    sort(a,a+n);
    return a[n/2];
}
int partition(int a[],int n,int pivot){
    int p=0;
    for(int i=0;i<n;i++)
        if(a[i]==pivot){
            swap(a[i],a[n-1]);
            break;
        }
    for(int i=0;i<n-1;i++)
        if(a[i]<pivot)
            swap(a[i],a[p++]);
    swap(a[p],a[n-1]);
    return p;
}
int select(int a[],int n,int k){
    if(n<=5){
        sort(a,a+n);
        return a[k-1];
    }
    int m=(n+4)/5;
    int med[m];
    for(int i=0;i<m;i++){
        int l=i*5,r=min(l+5,n);
        med[i]=median(a+l,r-l);
    }
    int pivot=select(med,m,(m+1)/2);
    int p=partition(a,n,pivot);
    if(k==p+1)
        return a[p];
    if(k<p+1)
        return select(a,p,k);
    return select(a+p+1,n-p-1,k-p-1);
}
int main(){
    int n,k;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    cin>>k;
    cout<<"Kth smallest: "<<select(a,n,k);
    return 0;
}