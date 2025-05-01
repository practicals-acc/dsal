#include <iostream>
#include <string>
#include <sstream>

// Class for storing keyword-meaning pairs
class DictionaryEntry
{
  public:
	std::string keyword;
	std::string meaning;
	
	DictionaryEntry() : keyword(""), meaning("") {}
	
	DictionaryEntry(const std::string& key, const std::string& value) 
		: keyword(key), meaning(value) {}
		
	// Used for comparison in AVL tree
	bool operator<(const DictionaryEntry& other) const {
		return keyword < other.keyword;
	}
	
	bool operator>(const DictionaryEntry& other) const {
		return keyword > other.keyword;
	}
	
	bool operator==(const std::string& key) const {
		return keyword == key;
	}
	
	friend std::ostream& operator<<(std::ostream& os, const DictionaryEntry& entry) {
		os << entry.keyword << ": " << entry.meaning;
		return os;
	}
};

// AVL Tree Node
template <typename T>
class AVLNode
{
  public:
	T data;
	AVLNode* left;
	AVLNode* right;
	int height;

	AVLNode(T data) {
		this->data = data;
		left = right = nullptr;
		height = 1;
	}
};

// AVL Tree implementation
template <typename T>
class AVLTree
{
  private:
	AVLNode<T>* root;
	int comparisonCount; // For tracking comparisons

	// Helper functions
	int getHeight(AVLNode<T>* node)
	{
		if (node == nullptr) {
			return 0;
		}
		return node->height;
	}

	int getBalanceFactor(AVLNode<T>* node)
	{
		if (node == nullptr) {
			return 0;
		}
		return getHeight(node->left) - getHeight(node->right);
	}

	AVLNode<T>* rightRotate(AVLNode<T>* y)
	{
		AVLNode<T>* x = y->left;
		AVLNode<T>* T2 = x->right;

		// Perform rotation
		x->right = y;
		y->left = T2;

		// Update heights
		y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
		x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

		std::cout << "Right rotation performed at node with keyword: " << y->data.keyword << "\n";
		return x;
	}

	AVLNode<T>* leftRotate(AVLNode<T>* x)
	{
		AVLNode<T>* y = x->right;
		AVLNode<T>* T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		// Update heights
		x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
		y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;

		std::cout << "Left rotation performed at node with keyword: " << x->data.keyword << "\n";
		return y;
	}

	AVLNode<T>* insert(AVLNode<T>* node, T data)
	{
		// Standard BST insert
		if (node == nullptr) {
			return new AVLNode<T>(data);
		}

		if (data < node->data) {
			node->left = insert(node->left, data);
		} else if (data > node->data) {
			node->right = insert(node->right, data);
		} else {
			// Update meaning if keyword already exists
			node->data = data;
			return node;
		}

		// Update height
		node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

		// Get balance factor
		int balance = getBalanceFactor(node);

		// Left Left Case
		if (balance > 1 && data < node->left->data) {
			return rightRotate(node);
		}

		// Right Right Case
		if (balance < -1 && data > node->right->data) {
			return leftRotate(node);
		}

		// Left Right Case
		if (balance > 1 && data > node->left->data) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// Right Left Case
		if (balance < -1 && data < node->right->data) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		return node;
	}

	AVLNode<T>* minValueNode(AVLNode<T>* node)
	{
		AVLNode<T>* current = node;
		while (current && current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	AVLNode<T>* deleteNode(AVLNode<T>* root, const std::string& key)
	{
		if (root == nullptr) {
			return root;
		}

		// Standard BST delete
		if (key < root->data.keyword) {
			root->left = deleteNode(root->left, key);
		} else if (key > root->data.keyword) {
			root->right = deleteNode(root->right, key);
		} else {
			// Node with only one child or no child
			if (root->left == nullptr) {
				AVLNode<T>* temp = root->right;
				delete root;
				return temp;
			} else if (root->right == nullptr) {
				AVLNode<T>* temp = root->left;
				delete root;
				return temp;
			}

			// Node with two children
			AVLNode<T>* temp = minValueNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data.keyword);
		}

		// If tree had only one node
		if (root == nullptr) {
			return root;
		}

		// Update height
		root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

		// Get balance factor
		int balance = getBalanceFactor(root);

		// Left Left Case
		if (balance > 1 && getBalanceFactor(root->left) >= 0) {
			return rightRotate(root);
		}

		// Left Right Case
		if (balance > 1 && getBalanceFactor(root->left) < 0) {
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// Right Right Case
		if (balance < -1 && getBalanceFactor(root->right) <= 0) {
			return leftRotate(root);
		}

		// Right Left Case
		if (balance < -1 && getBalanceFactor(root->right) > 0) {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		return root;
	}

	AVLNode<T>* search(AVLNode<T>* root, const std::string& key)
	{
		comparisonCount = 0; // Reset comparison counter
		
		AVLNode<T>* current = root;
		while (current != nullptr) {
			comparisonCount++;
			
			if (key == current->data.keyword) {
				return current;
			} else if (key < current->data.keyword) {
				current = current->left;
			} else {
				current = current->right;
			}
		}
		return nullptr;
	}

	void inorderTraversal(AVLNode<T>* root, bool ascending)
	{
		if (root == nullptr) {
			return;
		}
		
		if (ascending) {
			inorderTraversal(root->left, ascending);
			std::cout << root->data << std::endl;
			inorderTraversal(root->right, ascending);
		} else {
			inorderTraversal(root->right, ascending);
			std::cout << root->data << std::endl;
			inorderTraversal(root->left, ascending);
		}
	}

	void displayTree(AVLNode<T>* root, std::string indent, bool last)
	{
		if (root != nullptr) {
			std::cout << indent;
			if (last) {
				std::cout << "R----";
				indent += "   ";
			} else {
				std::cout << "L----";
				indent += "|  ";
			}
			std::cout << root->data << " (h=" << root->height << ")" << std::endl;
			displayTree(root->left, indent, false);
			displayTree(root->right, indent, true);
		}
	}

	void updateMeaning(AVLNode<T>* root, const std::string& key, const std::string& newMeaning)
	{
		AVLNode<T>* node = search(root, key);
		if (node != nullptr) {
			node->data.meaning = newMeaning;
			std::cout << "Meaning updated successfully!" << std::endl;
		} else {
			std::cout << "Keyword not found!" << std::endl;
		}
	}

  public:
	AVLTree() : root(nullptr), comparisonCount(0) {}
	
	// Add a new entry
	void insert(const std::string& keyword, const std::string& meaning)
	{
		DictionaryEntry entry(keyword, meaning);
		root = insert(root, entry);
	}
	
	// Delete an entry
	void remove(const std::string& keyword)
	{
		root = deleteNode(root, keyword);
	}
	
	// Update meaning of a keyword
	void update(const std::string& keyword, const std::string& newMeaning)
	{
		updateMeaning(root, keyword, newMeaning);
	}
	
	// Search for a keyword
	bool search(const std::string& keyword)
	{
		AVLNode<T>* result = search(root, keyword);
		if (result != nullptr) {
			std::cout << "Found: " << result->data << std::endl;
			std::cout << "Number of comparisons: " << comparisonCount << std::endl;
			return true;
		} else {
			std::cout << "Keyword not found!" << std::endl;
			std::cout << "Number of comparisons: " << comparisonCount << std::endl;
			return false;
		}
	}
	
	// Display all entries
	void display(bool ascending = true)
	{
		if (root == nullptr) {
			std::cout << "Dictionary is empty!" << std::endl;
			return;
		}
		
		std::cout << "\nDictionary Entries (" << (ascending ? "Ascending" : "Descending") << " Order):" << std::endl;
		std::cout << "------------------------" << std::endl;
		inorderTraversal(root, ascending);
	}
	
	// Display tree structure
	void displayStructure()
	{
		if (root == nullptr) {
			std::cout << "Dictionary is empty!" << std::endl;
			return;
		}
		
		std::cout << "\nTree Structure:" << std::endl;
		displayTree(root, "", true);
	}
	
	// Get height of the tree (which is the max comparisons needed)
	int getHeight()
	{
		return getHeight(root);
	}
	
	// Calculate time complexity
	void printComplexity()
	{
		int height = getHeight();
		std::cout << "\nHeight of AVL Tree: " << height << std::endl;
		std::cout << "Maximum number of comparisons required: " << height << std::endl;
		std::cout << "Time Complexity for search operation: O(log n)" << std::endl;
		std::cout << "Space Complexity: O(n)" << std::endl;
	}
};

int main()
{
	AVLTree<DictionaryEntry> dictionary;
	int choice;
	std::string keyword, meaning;

	do {
		std::cout << "\n\nDictionary Using AVL Tree" << std::endl;
		std::cout << "1. Add new keyword" << std::endl;
		std::cout << "2. Delete keyword" << std::endl;
		std::cout << "3. Update meaning" << std::endl;
		std::cout << "4. Search keyword" << std::endl;
		std::cout << "5. Display dictionary (Ascending order)" << std::endl;
		std::cout << "6. Display dictionary (Descending order)" << std::endl;
		std::cout << "7. Display tree structure" << std::endl;
		std::cout << "8. Print complexity analysis" << std::endl;
		std::cout << "9. Exit" << std::endl;
		std::cout << "Enter your choice: ";
		std::cin >> choice;
		
		std::cin.ignore(); // Clear the newline character
		
		switch (choice) {
			case 1:
				std::cout << "Enter keyword: ";
				std::getline(std::cin, keyword);
				std::cout << "Enter meaning: ";
				std::getline(std::cin, meaning);
				dictionary.insert(keyword, meaning);
				std::cout << "Entry added successfully!" << std::endl;
				break;
				
			case 2:
				std::cout << "Enter keyword to delete: ";
				std::getline(std::cin, keyword);
				dictionary.remove(keyword);
				std::cout << "Entry deleted successfully!" << std::endl;
				break;
				
			case 3:
				std::cout << "Enter keyword to update: ";
				std::getline(std::cin, keyword);
				std::cout << "Enter new meaning: ";
				std::getline(std::cin, meaning);
				dictionary.update(keyword, meaning);
				break;
				
			case 4:
				std::cout << "Enter keyword to search: ";
				std::getline(std::cin, keyword);
				dictionary.search(keyword);
				break;
				
			case 5:
				dictionary.display(true); // Ascending order
				break;
				
			case 6:
				dictionary.display(false); // Descending order
				break;
				
			case 7:
				dictionary.displayStructure();
				break;
				
			case 8:
				dictionary.printComplexity();
				break;
				
			case 9:
				std::cout << "Exiting program..." << std::endl;
				break;
				
			default:
				std::cout << "Invalid choice! Please try again." << std::endl;
		}
	} while (choice != 9);

	return 0;
}
