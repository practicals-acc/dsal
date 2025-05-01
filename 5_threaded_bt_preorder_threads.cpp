#include <iostream>
using namespace std;

// Structure for a preorder threaded binary tree node
struct Node
{
	int data;
	Node* left;
	Node* right;
	bool isLeftThread;	// True if left pointer is a thread
	bool isRightThread; // True if right pointer is a thread
	
	// Constructor
	Node(int value) {
		data = value;
		left = right = NULL;
		isLeftThread = isRightThread = false;
	}
};

// Function to insert a node and maintain preorder threading using a recursive approach
Node* insert(Node* root, int value)
{
	// If tree is empty, create a new node
	if (root == NULL) {
		return new Node(value);
	}
	
	// Insert into left subtree
	if (value < root->data) {
		// If left child exists
		if (root->left && !root->isLeftThread) {
			Node* leftSubtree = insert(root->left, value);
			root->left = leftSubtree;
		} else {
			// Create new node
			Node* newNode = new Node(value);
			
			// Set left child pointer
			newNode->left = root->left;
			newNode->isLeftThread = root->isLeftThread;
			
			// In preorder, after this new node, we visit its right child
			// If it doesn't have a right child, we visit the parent's right child
			newNode->right = root;
			newNode->isRightThread = true;
			
			// Update root's left pointer
			root->left = newNode;
			root->isLeftThread = false;
		}
	}
	// Insert into right subtree
	else {
		// If right child exists
		if (root->right && !root->isRightThread) {
			Node* rightSubtree = insert(root->right, value);
			root->right = rightSubtree;
		} else {
			// Create new node
			Node* newNode = new Node(value);
			
			// In preorder, after this new right child, we visit whatever the parent would visit next
			newNode->right = root->right;
			newNode->isRightThread = root->isRightThread;
			
			// Update root's right pointer
			root->right = newNode;
			root->isRightThread = false;
		}
	}
	
	return root;
}

// Function to perform preorder traversal of a preorder threaded binary tree
// without using a stack
void preorderTraversal(Node* root)
{
	if (root == NULL)
		return;
	
	Node* current = root;
	
	// Traverse until there are no more nodes to visit
	while (current != NULL) {
		// Process the current node
		cout << current->data << " ";
		
		// If left pointer is not a thread, move to left child
		if (!current->isLeftThread) {
			current = current->left;
		}
		// If left is a thread (or NULL), move to right child if it's not a thread
		else if (!current->isRightThread) {
			current = current->right;
		}
		// If both left and right are threads (or NULL), follow right thread
		else {
			// Keep following right threads until we find a real right child or NULL
			while (current != NULL && current->isRightThread) {
				current = current->right;
			}
			
			// If we found a node with a real right child, move to it
			if (current != NULL)
				current = current->right;
		}
	}
}

// Main function to demonstrate usage
int main()
{
	// Create a preorder threaded binary tree by inserting nodes recursively
	Node* root = NULL;
	
	// Insert nodes and maintain threading simultaneously
	root = insert(root, 10);
	root = insert(root, 5);
	root = insert(root, 15);
	root = insert(root, 3);
	root = insert(root, 7);
	root = insert(root, 12);
	root = insert(root, 18);
	
	// Perform preorder traversal without using stack
	cout << "Preorder traversal using threads (without stack): ";
	preorderTraversal(root);
	cout << endl;
	
	return 0;
}
