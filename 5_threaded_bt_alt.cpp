#include <iostream>
using namespace std;
class nodeth
{
	public:
		int data,thleft,thright;
		nodeth *left,*right;
		nodeth *header = NULL;

		nodeth(){
			thleft=0;
			thright=0;
		}
		nodeth *create(nodeth *root);
		void insert(nodeth *root,nodeth *temp);
		void display(nodeth *root);
		void display1(nodeth *root);
};
nodeth *nodeth::create(nodeth *root)
{
	nodeth *temp;
	char ans;
	do{
		temp=new nodeth;
		cout<<"\nEnter the data: ";
		cin>>temp->data;
		temp->right=temp->left=NULL;
		if(root==NULL)
		{
			root=temp;
			root->left=root->right=header;
			root->thleft=root->thright=1;
		}
		else
		{
			insert(root,temp);
		}
		cout<<"\n\nDo you want to add another node: ";
		cin>>ans;
	}while(ans=='y'||ans=='Y');
	return(root);
}
void nodeth::insert(nodeth *root,nodeth *temp)
{
	char ch;
	cout<<"Want to enter data to left(L) or right(R) of "<<root->data<<": ";
	cin>>ch;
	if(ch=='l'||ch=='L')
	{
		if(root->thleft==1)
		{

			temp->left=root->left;
			root->left=temp;
			temp->right=root;
			root->thleft=0;
			temp->thleft=temp->thright=1;
		}
		else
		{
			insert(root->left,temp);
		}

	}
	else if(ch=='r'||ch=='R')
	{
		if(root->thright==1)
		{
			temp->right=root->right;
			root->right=temp;
			temp->left=root;
			root->thright=0;
			temp->thright=temp->thleft=1;
		}
		else
		{
			insert(root->right,temp);
		}
	}
}
void nodeth::display(nodeth *root)
{
	nodeth *temp=root;
	int flag=0;
	while(temp!=NULL)
	{
		while(flag==0 && temp->thleft==0)
		{
			temp=temp->left;
		}
		cout<<"\t"<<temp->data;
		if(temp->thright==0)
		{
			flag=0;
		}
		else
		{
			flag=1;
		}
		temp=temp->right;
	}
}
void nodeth::display1(nodeth *root)
{
	nodeth *temp=root;
	int flag=0;
	while(temp!=NULL)
	{
		if(flag==0)
		{
			cout<<"\t"<<temp->data;
		}

		if(flag==0 && temp->thleft==0)
		{
			temp=temp->left;
		}
		else
		{
			if(temp->thright==0)
			{
				flag=0;
			}
			else
			{
				flag=1;
			}
			temp=temp->right;
		}
	}
}
int main() {
	nodeth *root=NULL;
	int ch;
	char ch1;
	nodeth th1;
	do
	{
		cout<<"\n\n1. Create Threaded Binary Tree \n2. Inorder Display\n3. Preorder Display";

		cout<<"\nEnter your choice: ";
		cin>>ch;
		switch(ch)
		{
			case 1:
				root=th1.create(root);
				break;
			case 2:
				cout<<"\nInorder Threaded Binary Tree is: ";
				th1.display(root);
				break;
			case 3:
				cout<<"\nPreorder traversal on Threaded Binary Tree is: ";
				th1.display1(root);
				break;
		}
		cout<<"\n Do you want to continue?";
		cin>>ch1;
	}while(ch1=='y'||ch=='Y');
	return 0;
}
