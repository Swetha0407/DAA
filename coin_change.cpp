#include <iostream>
using namespace std;

int main(){
    int n,amount;
    cin>>n>>amount;

    int coin[n];
    for(int i=0;i<n;i++)
        cin>>coin[i];

    int count=0;

    for(int i=n-1;i>=0;i--){
        while(amount>=coin[i]){
            amount-=coin[i];
            cout<<coin[i]<<" ";
            count++;
        }
    }

    cout<<"\nMinimum coins: "<<count;
    return 0;
}