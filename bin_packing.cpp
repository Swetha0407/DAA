#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n,C;
    cin>>n>>C;

    int a[n],bin[n]={0};

    for(int i=0;i<n;i++)
        cin>>a[i];

    sort(a,a+n,greater<int>());

    int bins=0;

    for(int i=0;i<n;i++){
        int j;
        for(j=0;j<bins;j++){
            if(bin[j]+a[i]<=C){
                bin[j]+=a[i];
                break;
            }
        }

        if(j==bins){
            bin[bins]=a[i];
            bins++;
        }
    }

    cout<<"Number of bins: "<<bins<<endl;

    for(int i=0;i<bins;i++)
        cout<<"Bin "<<i+1<<": "<<bin[i]<<endl;

    return 0;
}