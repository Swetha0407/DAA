#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n,W;
    cin>>n>>W;

    int wt[n];
    for(int i=0;i<n;i++)
        cin>>wt[i];

    sort(wt,wt+n);

    int total=0,count=0;

    for(int i=0;i<n;i++){
        if(total+wt[i]<=W){
            total+=wt[i];
            count++;
        }
        else
            break;
    }

    cout<<"Maximum containers: "<<count;
    cout<<"\nTotal weight: "<<total;

    return 0;
}