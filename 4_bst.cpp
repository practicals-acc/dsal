#include <iostream>
using namespace std;

// Node structure for BST
struct Node
{
	int data;
	Node* left;
	Node* right;

	Node(int value) {
		data = value;
		left = right = NULL;
	}
};

// Insert node into BST
Node* insert(Node* root, int value)
{
	if (root == NULL) {
		return new Node(value);
	}

	if (value < root->data) {
		root->left = insert(root->left, value);
	} else {
		root->right = insert(root->right, value);
	}

	return root;
}

// Find height (longest path from root)
int findHeight(Node* root)
{
	if (root == NULL) return 0;
	int leftHeight = findHeight(root->left);
	int rightHeight = findHeight(root->right);
	return max(leftHeight, rightHeight) + 1;
}

// Find minimum value in BST
int findMin(Node* root)
{
	if (root == NULL) {
		cout << "Tree is empty.\n";
		return -1;
	}

	Node* current = root;
	while (current->left != NULL) {
		current = current->left;
	}
	return current->data;
}

// Mirror the tree
void mirrorTree(Node* root)
{
	if (root == NULL) return;

	// Swap left and right children
	Node* temp = root->left;
	root->left = root->right;
	root->right = temp;

	// Recur for subtrees
	mirrorTree(root->left);
	mirrorTree(root->right);
}

// Search for a value
bool search(Node* root, int value)
{
	if (root == NULL)
		return false;
	if (root->data == value)
		return true;
	else if (value < root->data)
		return search(root->left, value);
	else
		return search(root->right, value);
}

// In-order traversal (to display tree)
void inorder(Node* root)
{
	if (root == NULL) return;
	inorder(root->left);
	cout << root->data << " ";
	inorder(root->right);
}

int main()
{
	Node* root = NULL;
	int values[] = {50, 30, 20, 40, 70, 60, 80};
	int n = sizeof(values) / sizeof(values[0]);

	// 1. Construct BST
	for (int i = 0; i < n; i++) {
		root = insert(root, values[i]);
	}

	cout << "In-order Traversal of Original BST: ";
	inorder(root);
	cout << endl;

	// 2. Insert new node
	root = insert(root, 65);
	cout << "After inserting 65, In-order Traversal: ";
	inorder(root);
	cout << endl;

	// 3. Longest path from root (Height)
	cout << "Height (Longest path from root): " << findHeight(root) << endl;

	// 4. Minimum value
	cout << "Minimum value in BST: " << findMin(root) << endl;

	// 5. Mirror the tree
	mirrorTree(root);
	cout << "In-order Traversal of Mirrored Tree: ";
	inorder(root);
	cout << endl;

	// 6. Search a value
	int searchValue = 20;
	cout << "Searching for " << searchValue << ": ";
	if (search(root, searchValue))
		cout << "Found\n";
	else
		cout << "Not Found\n";

	return 0;
}
