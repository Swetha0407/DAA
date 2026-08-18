#include <iostream>
#include <algorithm>
using namespace std;

struct Job{
    string id;
    int deadline,profit;
};

bool cmp(Job a,Job b){
    return a.profit>b.profit;
}

int main(){
    int n;
    cin>>n;

    Job a[n];
    for(int i=0;i<n;i++)
        cin>>a[i].id>>a[i].deadline>>a[i].profit;

    sort(a,a+n,cmp);

    int maxD=0;
    for(int i=0;i<n;i++)
        maxD=max(maxD,a[i].deadline);

    string slot[maxD];
    for(int i=0;i<maxD;i++)
        slot[i]="";

    int profit=0;

    for(int i=0;i<n;i++){
        for(int j=min(maxD,a[i].deadline)-1;j>=0;j--){
            if(slot[j]==""){
                slot[j]=a[i].id;
                profit+=a[i].profit;
                break;
            }
        }
    }

    cout<<"Job sequence: ";
    for(int i=0;i<maxD;i++)
        if(slot[i]!="")
            cout<<slot[i]<<" ";

    cout<<"\nMaximum profit: "<<profit;
    return 0;
}