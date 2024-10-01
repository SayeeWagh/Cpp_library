#include <iostream>
#include<stack>
#include<string>

using namespace std;

struct Node{
    char data;
    Node* left;
    Node* right;
};

Node* newNode(char data)
{

    Node* node = new Node();
    node->data = data;
    node->left = 0;
    node->right = 0;
    return node;
}

bool isOperator(char c)
{

    return c =='+' || c == ' -' || c == '/' || c == '*';
}

Node* constructPostfixTree(const string& postfix)
{
    stack<Node*>st;
    for(char ch : postfix)
    {
        if(!isOperator(ch))
        {
            st.push(newNode(ch));
        }
        else{
            Node* op2 = st.top(); st.pop();
            Node* op1 = st.top(); st.pop();
            Node* opNode = newNode(ch);
            opNode->left = op1;
            opNode->right = op2;
            st.push(opNode);
        }
    }
    return st.top();
}

Node* constructPrefixTree(const string& prefix)
{
    stack<Node*>st;
    for(int i = prefix.size()-1 ; i>=0 ; i--)
    {
        char ch = prefix[i];
        if(!isOperator(ch))
        {
            st.push(newNode(ch));
        }
        else{
            Node* op1 = st.top() ; st.pop();
            Node* op2 = st.top() ; st.pop();
            Node* opNode = newNode(ch);
            opNode->left = op1;
            opNode->right = op2;
            st.push(opNode);
        }
    }
    return st.top();
}

void inOrderRecursive(Node* root)
{

    if(root == 0){
        return;
    }
    inOrderRecursive(root->left);
    cout<< root->data <<" ";
    inOrderRecursive(root->right);
}

void preOrderRecursive(Node* root)
{
    if(root == 0){
        return;
    }
    cout<<root->data<<" ";
    preOrderRecursive(root->left);
    preOrderRecursive(root->right);
}

void postOrderRecursive(Node* root)
{
    if(root == 0){
        return;
    }
    postOrderRecursive(root->left);
    postOrderRecursive(root->right);
    cout<<root->data<<" ";
}

void inOrderNonrecursive(Node* root)
{
    stack<Node*>st;
    Node* temp = root;
    while(true)
    {
        while(temp != 0)
        {
            st.push(temp);
            temp = temp->left;
        }
        if(st.empty()){
            break;
        }
        temp = st.top();
        st.pop();
        cout<<temp->data<<" ";
        temp = temp->right;
    }
}

void preOrderNonRecursive(Node* root)
{
    if(root == 0){
        return;
    }
    stack<Node*>st;
    st.push(root);

    while(!st.empty())
    {
        Node* temp = st.top();
        st.pop();
        cout<<temp->data<<" ";

        if(temp->right != 0)
        {
            st.push(temp->right);
        }
        if(temp->left != 0)
        {
            st.push(temp->left);
        }
    }
}

void postOrderNonRecursive(Node* root)
{
    if(root == 0){
        return;
    }

    stack<Node*>st;
    Node* lastVisited = 0;
    Node* temp = root;

    while(true)
    {
        while(temp!=0)
        {
            st.push(temp);
            temp = temp->left;
        }

        Node* topNode = st.top();

        if(topNode->right != 0 && lastVisited!=topNode->right)
        {
            temp = topNode->right;
        }
        else{
            cout<<topNode->data<<" ";
            lastVisited = topNode;
            st.pop();
        }

        if(st.empty())
        {
            break;
        }
    }
}

int main()
{
    string expression;
    int choice;
    int type;

    cout<<"1.Postfix Expression \n2.Prefix Expression"<<endl;
    cout<<"Enter expression type:";
    cin>>type;
    cout<<endl;
    cout<<"Enter the Expression:";
    cin>>expression;

    Node* root = 0;

    if(type == 1){
        root = constructPostfixTree(expression);
    }
    else if(type == 2)
    {
        root = constructPrefixTree(expression);
    }
    else{
        cout<<"Enter valid expression type!!"<<endl;
        return 0;
    }
    do{

    cout<<endl;
    cout<<"Types of Traversal:"<<endl;
    cout<<"1.In-Order Recursive"<<endl;
    cout<<"2.In-Order Non-Recursive"<<endl;
    cout<<"3.Pre-Order Recursive"<<endl;
    cout<<"4.Pre-Order Non-Recursive"<<endl;
    cout<<"5.Post-Order Recursive"<<endl;
    cout<<"6.Post-Order Non-Recursive"<<endl;
    cout<<"7.Exit"<<endl;
    cout<<endl;
    cout<<"Enter Choice:";
    cin>>choice;
    cout<<endl;

    switch(choice)
    {
    case 1:
        cout<<"In-Order Recursive Traversal:";
        inOrderRecursive(root);
        cout<<endl;
        break;

    case 2:
        cout<<"In-Order Non-Recursive Traversal:";
        inOrderNonrecursive(root);
        cout<<endl;
        break;

    case 3:
        cout<<"Pre-Order Recursive Traversal:";
        preOrderRecursive(root);
        cout<<endl;
        break;

    case 4:
        cout<<"Pre-Order Non-Recursive Traversal:";
        preOrderNonRecursive(root);
        cout<<endl;
        break;

    case 5:
        cout<<"Post-Order Recursive Traversal:";
        postOrderRecursive(root);
        cout<<endl;
        break;

    case 6:
        cout<<"Post-Order Non-Recursive Traversal:";
        postOrderNonRecursive(root);
        cout<<endl;
        break;

    case 7:
        cout<<"EXIT..."<<endl;
        break;

    default :
        cout<<"Enter valid Choice!!"<<endl;
        break;
    }

    }while(choice != 7);

    return 0;
}

