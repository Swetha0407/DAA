#include <iostream>
using namespace std;

int n,x[20];

bool safe(int row,int col){
    for(int i=0;i<row;i++)
        if(x[i]==col||abs(x[i]-col)==abs(i-row))
            return false;
    return true;
}

bool solve(int row){
    if(row==n)
        return true;

    for(int col=0;col<n;col++){
        if(safe(row,col)){
            x[row]=col;
            if(solve(row+1))
                return true;
            x[row]=-1;
        }
    }
    return false;
}

int main(){
    cin>>n;

    for(int i=0;i<n;i++)
        x[i]=-1;

    if(solve(0)){
        cout<<"Solution:\n";
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++)
                cout<<(x[i]==j?"Q ":"- ");
            cout<<endl;
        }
    }
    else
        cout<<"No solution";

    return 0;
}