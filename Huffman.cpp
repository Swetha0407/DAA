#include <iostream>
#include <queue>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node *left,*right;

    Node(char c,int f){
        ch=c;
        freq=f;
        left=right=NULL;
    }
};

struct Compare{
    bool operator()(Node* a,Node* b){
        return a->freq>b->freq;
    }
};

void printCodes(Node* root,string code){
    if(!root) return;

    if(!root->left&&!root->right)
        cout<<root->ch<<" : "<<code<<endl;

    printCodes(root->left,code+"0");
    printCodes(root->right,code+"1");
}

int main(){
    int n;
    cin>>n;

    priority_queue<Node*,vector<Node*>,Compare> pq;

    for(int i=0;i<n;i++){
        char ch;
        int freq;
        cin>>ch>>freq;
        pq.push(new Node(ch,freq));
    }

    while(pq.size()>1){
        Node* a=pq.top(); pq.pop();
        Node* b=pq.top(); pq.pop();

        Node* p=new Node('\0',a->freq+b->freq);
        p->left=a;
        p->right=b;
        pq.push(p);
    }

    cout<<"Huffman Codes:\n";
    printCodes(pq.top(),"");

    return 0;
}