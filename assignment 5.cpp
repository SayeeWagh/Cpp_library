#include<iostream>

using namespace std;

struct Node{
	int key;
	Node* left;
	Node* right;
	Node(int data){
		key = data;
		left = NULL;
		right = NULL;
	}
};

Node* insert(Node* root, int value)
{
	if(root == NULL)
	{
		return new Node(value);
	}
	if(root->key == value)
	{
		return root;
	}
	if(root->key < value)
	{
		root->right = insert(root->right , value);
	}
	else{
		root->left = insert(root->left , value);
	}
}

Node* minvalue(Node* root)
{
	while(root && root->left != NULL)
	{
		root = root->left;
	}
	return root;
}

Node* deleteNode(Node* root, int value)
{
	if(root == NULL)
	{
		return root;
	}
	if( root->key > value)
	{
		root->left = deleteNode(root->left, value);
	}
	else if(value > root->key)
	{
		root->right = deleteNode(root->right , value);
	}
	else{
		if(root->left == NULL)
		{
			Node* temp = root->right;
			delete root;
			return temp;
		}
		else if(root->right == NULL)
		{
			Node* temp = root->left;
			delete root;
			return temp;
		}
		Node* temp = minvalue(root->right);
		root->key = temp->key;
		root->right = deleteNode(root->right , temp->key);
	}
	return root;
}

void inOrder(Node* root)
{
	if(root != NULL)
	{
		inOrder(root->left);
		cout<<root->key<<" ";
		inOrder(root->right);
	}
}

int main()
{
	Node* root =NULL;
	root = insert(root, 10);
	root = insert(root, 3);
	root = insert(root, 8);
	root = insert(root, 4);
	root = insert(root,34);
	root = insert(root, 30);
	root = insert(root, 53);
	root = insert(root, 12);
	cout<<"Tree Traversal after insertion:"<<endl;
	inOrder(root);
	cout<<endl;
	cout<<endl;
	cout<<"Delete Elements '8' , '34' , '3'!!";
	root = deleteNode(root, 8);
	root = deleteNode(root, 34);
	root = deleteNode(root,3);
	cout<<endl;
	cout<<endl;
	cout<<"Tree Traversal after Deletion:"<<endl;
	inOrder(root);
	cout<<endl;
	return 0;
}
