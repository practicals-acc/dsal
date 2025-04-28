#include <iostream>

using namespace std;

class Node
{
  public:
	int data;
	Node *left;
	Node *right;

	Node(int n)
	{
		data = n;
		left = right = NULL;
	}
};

class BinaryTree
{
  public:
	Node *root;
	BinaryTree()
	{
		root = NULL;
	}


	void insert_node_rec(Node *root, Node *n)
	{
		while (true) {
			char choice;
			cout << "Insert to the left or right of " << root->data << "? ";
			cin >> choice;
			
			if (choice == 'l' || choice == 'L') {
				if (root->left == NULL) {
					root->left = n;
				} else {
					insert_node_rec(root->left, n);
				}
				break;
			} else if (choice == 'r' || choice == 'R') {
				if (root->right == NULL) {
					root->right = n;
				} else {
					insert_node_rec(root->right, n);
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

		Node *new_node = new Node(data);
		if (root == NULL) {
			root = new_node;
		} else {
			insert_node_rec(root, new_node);
		}
	}

	void display_preorder_rec(Node *root)
	{
		if (root != NULL) {
			cout << root->data << " ";
			display_preorder_rec(root->left);
			display_preorder_rec(root->right);
		}
	}

	void display_inorder_rec(Node *root)
	{
		if (root != NULL) {
			display_inorder_rec(root->left);
			cout << root->data << " ";
			display_inorder_rec(root->right);
		}
	}

	void display_postorder_rec(Node *root)
	{
		if (root != NULL) {
			display_postorder_rec(root->left);
			display_postorder_rec(root->right);
			cout << root->data << " ";
		}
	}

	/*
	void insert_node(node *n, bool left)
	{
		while (true) {
			node *temp = root;
			char choice;
			cout << "Insert to the left or right of " << temp->name << "? ";
			cin >> choice;
			

			if (choice == 'l' || choice == 'L') {
				while (temp->left != NULL) {
					temp = temp->left;
				}
				temp->left = n;
				break;
			} else if (choice == 'r' || choice == 'R') {
				while (temp->right != NULL) {
					temp = temp->right;
				}
				temp->right = n;
				break;
			} else {
				cout << "Invalid choice! Node not inserted\n";
				continue;
			}
		}
	}
	*/
};


int main()
{
	int choice;
	BinaryTree bt;

	do {
		cout << "\n1. Add node\n2. Display Preorder\n3. Display Inorder\n4. Display Postorder\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				bt.add_node();
				break;
			case 2:
				cout << "Preorder traversal: ";
				bt.display_preorder_rec(bt.root);
				cout << endl;
				break;
			case 3:
				cout << "Inorder traversal: ";
				bt.display_inorder_rec(bt.root);
				cout << endl;
				break;
			case 4:
				cout << "Postorder traversal: ";
				bt.display_postorder_rec(bt.root);
				cout << endl;
				break;
			default:
				cout << "Invalid choice!\n";
		}
	} while (choice != 6);

	return 0;
}
