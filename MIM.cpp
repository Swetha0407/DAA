#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void gen(vector<int>&a,int l,int r,long long sum,vector<pair<long long,vector<int>>>&v,vector<int> sub){
    if(l==r){
        v.push_back({sum,sub});
        return;
    }
    gen(a,l+1,r,sum,v,sub);
    sub.push_back(a[l]);
    gen(a,l+1,r,sum+a[l],v,sub);
}
int main(){
    int n;
    long long target;
    cin>>n>>target;
    vector<int>a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    int mid=n/2;
    vector<pair<long long,vector<int>>> L,R;
    gen(a,0,mid,0,L,{});
    gen(a,mid,n,0,R,{});
    sort(R.begin(),R.end(),[](auto x,auto y){
        return x.first<y.first;
    });
    for(auto x:L){
        long long need=target-x.first;
        auto it=lower_bound(R.begin(),R.end(),need,
            [](auto p,long long val){return p.first<val;});
        if(it!=R.end()&&it->first==need){
            cout<<"Subset: ";
            for(int z:x.second) cout<<z<<" ";
            for(int z:it->second) cout<<z<<" ";
            cout<<"\nSubset exists";
            return 0;
        }
    }
    cout<<"No subset found";
    return 0;
}