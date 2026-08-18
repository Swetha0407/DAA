#include <iostream>
#include <algorithm>
using namespace std;

struct Item{
    int wt,val;
    double ratio;
};

int main(){
    int n,W;
    cin>>n>>W;

    Item a[n];

    for(int i=0;i<n;i++){
        cin>>a[i].wt>>a[i].val;
        a[i].ratio=(double)a[i].val/a[i].wt;
    }

    sort(a,a+n,[](Item x,Item y){
        return x.ratio>y.ratio;
    });

    double profit=0;

    for(int i=0;i<n;i++){
        if(W>=a[i].wt){
            W-=a[i].wt;
            profit+=a[i].val;
        }
        else{
            profit+=a[i].ratio*W;
            break;
        }
    }

    cout<<"Maximum profit: "<<profit;
    return 0;
}