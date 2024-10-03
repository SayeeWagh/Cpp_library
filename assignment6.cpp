#include <iostream>

using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;
    bool isThreaded;

    Node(int value)
    {
        data= value;
        left = 0;
        right = 0;
        isThreaded = false;
    }
};

Node* insert(Node* root, int data)
{
    if(root == 0)
    {
        return new Node(data);
    }
    if(data<root->data)
    {
        root->left = insert(root->left , data);
    }
    if(data>root->data)
    {
        root->right = insert(root->right,data);
    }
    return root;
}

void createThread(Node* root,Node*& prevNode)
{
    if(root == 0) return;

    createThread(root->left, prevNode);

    if(prevNode != 0 && prevNode->right == 0)
    {
        prevNode->right = root;
        prevNode->isThreaded = true;
    }
    prevNode = root;

    createThread(root->right, prevNode);
}

void inOrderTraversal(Node* root)
{
    Node* current = root;

    while(current != 0 && current->left !=0)
    {
        current = current->left;
    }
    cout<<"In-order Traversal:";

    while(current != 0)
    {
        cout<<current->data<<" ";

        if(current->isThreaded)
        {
            current = current->right;
        }
        else{
            current=current->right;
            while(current!=0 && current->left!=0)
            {
                current=current->left;
            }
        }
    }
    cout<<endl;
}

void preOrderTraversal(Node* root)
{
    Node* current = root;
    cout<<"Pre-Order Traversal:";

    while(current != 0)
    {
        cout<<current->data<<" ";
        if(current->left!=0)
        {
            current = current->left;
        }
        else{
            while(current!=0 && current->right!=0 &&current->isThreaded)
            {
                current=current->right;
            }

            if(current!=0)
            {
                current=current->right;
            }
        }
    }
    cout<<endl;
}

int main()
{
    Node* root=0;
    int ch,value,numNodes;

    cout<<"Enter the Number of Nodes you want in Threaded Binary Tree:";
    cin>>numNodes;
    cout<<endl;

    for(int i=0; i<numNodes; i++)
    {
        cout<<"Enter the Value for the Node "<<i+1<<":";
        cin>>value;
        root=insert(root,value);
    }
    cout<<endl;

    Node*prevNode = 0;
    createThread(root, prevNode);

    do{
        cout<<"Choose the Threaded Binary Tree Traversal Method:"<<endl;
        cout<<"1.In-Order Traversal"<<endl;
        cout<<"2.Pre-Order Traversal"<<endl;
        cout<<"3.Exit"<<endl;
        cout<<"Enter your choice:";
        cin>>ch;
        cout<<endl;

        switch(ch){
        case 1:
            inOrderTraversal(root);
            cout<<endl;
            break;

        case 2:
            preOrderTraversal(root);
            cout<<endl;
            break;

        case 3:
            cout<<"Exiting...."<<endl;
            break;

        default :
            cout<<"Enter the Valid Choice!!"<<endl;
            cout<<endl;
            break;
        }
    }while(ch!=3);

    return 0;
}
