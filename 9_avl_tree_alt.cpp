#include <iostream>

template <typename T>
class AVLNode
{
  public:
	T data;
	AVLNode *left;
	AVLNode *right;
	int height;

	AVLNode(T data)
	{
		this->data = data;
		left = right = NULL;
		height = 1;
	}

};

template <typename T>
class AVLTree
{
	AVLNode<T> *root;

	AVLNode<T> *insert(AVLNode<T> *root, T data)
	{
		if (root == NULL) {
			return (new AVLNode<T>(data));
		}

		if (data < root->data) {
			root->left = insert(root->left, data);
		} else if (data > root->data) {
			root->right = insert(root->right, data);
		}

		root->height = 1 + std::max(get_height(root->left), get_height(root->right));
		int balance = get_balance(root);

		// First case - LL
		if (balance > 1 && get_balance(root->left) >= 0) {
			return right_rotate(root);
		}

		// Second case - RR
		if (balance < -1 && get_balance(root->right) <= 0) {
			return left_rotate(root);
		}

		// Third case - LR
		if (balance > 1 && get_balance(root->left) < 0) {
			root->left = left_rotate(root->left);
			return right_rotate(root);
		}

		// Fourth case - RL
		if (balance < -1 && get_balance(root->right) > 0) {
			root->right = right_rotate(root->left);
			return left_rotate(root);
		}

		return root;
	}
	int get_height(AVLNode<T> *n)
	{
		if (n == NULL) {
			return 0;
		}
		return n->height;
	}

	int get_balance(AVLNode<T> *n)
	{
		if (n == NULL) {
			return 0;
		}
		return get_height(n->left) - get_height(n->right);
	}

	AVLNode<T> *right_rotate(AVLNode<T> *n)
	{
		AVLNode<T> *l_child = n->left;
		n->left = l_child->right;
		l_child->right = n;

		l_child->height = 1 + std::max(get_height(l_child->left), get_height(l_child->right));
		n->height = 1 + std::max(get_height(n->left), get_height(n->right));
		std::cout << "Right rotation performed\n";
		return l_child;
	}

	AVLNode<T> *left_rotate(AVLNode<T> *n)
	{
		AVLNode<T> *r_child = n->right;
		n->right = r_child->left;
		r_child->left = n;

		r_child->height = 1 + std::max(get_height(r_child->left), get_height(r_child->right));
		n->height = 1 + std::max(get_height(n->left), get_height(n->right));
		std::cout << "Left rotation performed\n";
		return r_child;
	}

	

	void display_inorder(AVLNode<T> *root)
	{
		if (root != NULL) {
			display_inorder(root->left);
			std::cout << root->data << " ";
			display_inorder(root->right);
		}
	}

	void print_tree(AVLNode<T> *root, std::string indent, bool last)
	{
		if (root != NULL) {
			std::cout << indent;
			if (last) {
				std::cout << "R----";
				indent += "   ";
			} else {
				std::cout << "L----";
				indent += "|  ";
			}
			std::cout << root->data << std::endl;
			print_tree(root->left, indent, false);
			print_tree(root->right, indent, true);
		}
	}
		
  public:
	AVLTree() : root(NULL) {}

	void add_node()
	{
		T data;
		std::cout << "Enter the data for new node: ";
		std::cin >> data;

		root = insert(root, data);
	}

	void display()
	{
		// display_inorder(root);
		print_tree(root, "", true);
	}
};

int main()
{
	int choice;
	AVLTree<int> avt;

	do {
		std::cout << "\n\nAVL Tree\n1. Add node\n2. Display\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
			case 1:
				avt.add_node();
				break;
			
			case 2:
				// std::cout << "Inorder traversal: ";
				std::cout << "Display tree: \n";
				avt.display();
				std::cout << std::endl;
				break;
			default:
				std::cout << "Invalid choice!\n";
		}
	} while (choice != 6);

	return 0;	
}
