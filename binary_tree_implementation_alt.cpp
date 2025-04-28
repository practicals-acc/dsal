#include <iostream>
using namespace std;
//#define true 1
//#define false 0

class node{
	public:
	int data;
	node *left,*right;
	node *createnode(node *root);
	void insert(node *root, node *temp);
	void displayLVR(node *root);//inorder
	void displayVLR(node *root);//pre-order
	void displayLRV(node *root);//post-order

};
node *node::createnode(node *root){
	node *temp;
	char c;
	do{
		temp=new node;
		temp->left=NULL;
		temp->right=NULL;
		cout<<"Enter the data: ";
		cin>>temp->data;

		if(root==NULL){
			root=temp;
		}
		else{
			insert(root,temp);
			cout<<"\n\n Want to enter more nodes?(y/n): ";
			cin>>c;
		}
	}while(c=='Y' || c=='y');
	return root;

}
void node::insert(node *root, node *temp){
	char ch;
	cout<<"Insert data to left(l) or right(r) of "<<root->data;
	cin>>ch;
	if(ch=='l'|| ch=='L')
	{
		if(root->left==NULL)
		{
			root->left=temp;
		}//if if end
		else
		{
			insert(root->left, temp);
		}//if else else
	}//if end
	if(ch=='r'|| ch=='R')
	{
		if(root->right==NULL)
		{
			root->right=temp;
		}//if if end
		else
		{
			insert(root->right, temp);
	    }//if else else
	}//if end
}

void node::displayVLR(node *root){
	if(root!=NULL){
		cout<<"\t"<<root->data;
		displayVLR(root->left);
		displayVLR(root->right);
	}
}

void node::displayLVR(node *root){
	if(root!=NULL){
		displayLVR(root->left);
		cout<<"\t"<<root->data;
		displayLVR(root->right);
	}
}

void node::displayLRV(node *root){
	if(root!=NULL){
		displayLRV(root->left);
		displayLRV(root->right);
		cout<<"\t"<<root->data;
	}
}
int main()
{
	node n;
	node *root=NULL;
	root->left=root->right=NULL;
	n.createnode(root);
	cout<<"Preorder: "<<endl;
	n.displayVLR(root);
	cout<<"Inorder: "<<endl;
	n.displayLVR(root);
	cout<<"Postorder: "<<endl;
	n.displayLRV(root);
	return 0;
}
