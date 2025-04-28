#include <iostream>

using namespace std;

class ThreadedNode
{
  public:
	int data;
	bool lthread, rthread;
	ThreadedNode *left;
	ThreadedNode *right;

	ThreadedNode(int n)
	{
		data = n;
		left = right = NULL;
		lthread = rthread = true;
	}
};

class ThreadedBinaryTree
{
  public:
	ThreadedNode *root;
	ThreadedNode *dummy = NULL;
	
	ThreadedBinaryTree()
	{
		root = NULL;
	}


	void insert_node_rec(ThreadedNode *parent, ThreadedNode *n)
	{
		while (true) {
			char choice;
			cout << "Insert to the left or right of " << parent->data << "? ";
			cin >> choice;
			
			if (choice == 'l' || choice == 'L') {
				if (parent->lthread) {
					n->left = parent->left;
					n->right = parent;
					parent->left = n;
					parent->lthread = false;
				} else {
					insert_node_rec(parent->left, n);
				}
				break;
			} else if (choice == 'r' || choice == 'R') {
				if (parent->rthread) {
					n->right = parent->right;
					n->left = parent;
					parent->right = n;
					parent->rthread = false;
				} else {
					insert_node_rec(parent->right, n);
				}
				break;
			} else {
				cout << "Invalid choice!\n";
				continue;
			}
		}
	}

	void add_node()
	{
		int data;
		cout << "Enter the data for new node: ";
		cin >> data;

		ThreadedNode *new_node = new ThreadedNode(data);
		if (root == NULL) {
			root = new_node;
			root->left = root->right = dummy;
			root->lthread = root->rthread = true;
		} else {
			insert_node_rec(root, new_node);
		}
	}

	void display_preorder()
	{
		if (root != NULL) {
			ThreadedNode *temp = root;
			bool leaf = false;
			while (temp != NULL) {
				cout << temp->data << " ";
				if (!temp->lthread && !leaf) {
					temp = temp->left;
				} else {
					if (!temp->rthread) {
						leaf = false;
					} else {
						leaf = true;
					}
					temp = temp->right;
				}
			}
		} else {
			cout << "The tree is empty!\n";
		}
	}

	void display_inorder()
	{
		if (root != NULL) {
			ThreadedNode *temp = root;
			bool leaf = false;
			while (temp != NULL) {
				while (!temp->lthread && !leaf) {
					temp = temp->left;
				}
				cout << temp->data << " ";
				if (!temp->rthread) {
					leaf = false;
				} else {
					leaf = true;
				}
				temp = temp->right;
			}
		} else {
			cout << "The tree is empty!\n";
		}
	}
};


int main()
{
	int choice;
	ThreadedBinaryTree tbt;

	do {
		cout << "\nThreaded Binary Tree\n1. Add node\n2. Display Inorder (Using threads)\n3. Display Preorder (Using threads)\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				tbt.add_node();
				break;
			
			case 2:
				cout << "Inorder traversal: ";
				tbt.display_inorder();
				cout << endl;
				break;
			case 3:
				cout << "Preorder traversal: ";
				tbt.display_preorder();
				cout << endl;
				break;
			default:
				cout << "Invalid choice!\n";
		}
	} while (choice != 6);

	return 0;
}
