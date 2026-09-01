#include <iostream>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;

    int a[m][n],covered[n]={0},elements=0,sets=0;

    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];

    cout<<"Selected sets: ";

    while(elements<n){
        int best=-1,maxCover=0;

        for(int i=0;i<m;i++){
            int c=0;
            for(int j=0;j<n;j++)
                if(a[i][j]&&!covered[j])
                    c++;

            if(c>maxCover){
                maxCover=c;
                best=i;
            }
        }

        if(best==-1)
            break;

        cout<<best+1<<" ";
        sets++;

        for(int j=0;j<n;j++){
            if(a[best][j]&&!covered[j]){
                covered[j]=1;
                elements++;
            }
            a[best][j]=0;
        }
    }

    cout<<"\nNumber of sets: "<<sets;
    return 0;
}