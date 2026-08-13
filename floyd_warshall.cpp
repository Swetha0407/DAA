#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int d[n][n];

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            cin>>d[i][j];

    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(d[i][k]!=999&&d[k][j]!=999)
                    d[i][j]=min(d[i][j],d[i][k]+d[k][j]);

    cout<<"Shortest Distance Matrix:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<d[i][j]<<" ";
        cout<<endl;
    }

    return 0;
}