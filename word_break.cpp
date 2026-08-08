#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    string s;
    int n;
    cin>>s>>n;
    vector<string> dict(n);
    for(int i=0;i<n;i++)
        cin>>dict[i];
    vector<bool> dp(s.length()+1,false);
    dp[0]=true;
    for(int i=1;i<=s.length();i++){
        for(string w:dict){
            int len=w.length();
            if(i>=len&&dp[i-len]&&s.substr(i-len,len)==w){
                dp[i]=true;
                break;
            }
        }
    }
    cout<<(dp[s.length()]?"Yes":"No");
    return 0;
}