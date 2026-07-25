#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    int arr[n];
    for(int i=0;i<n;i++)
        cin >> arr[i];
    int tar;
    cin >> tar;
    int low=0,high=n-1;
    while(low<=high) {
        int mid=(low+high)/2;
        if(arr[mid]==tar) {
            cout << "Element found at index: " << mid;
            return 0;
        }
        else if(arr[mid]<tar) {
            low=mid+1;
        }
        else {
            high=mid-1;
        }
    }
}