#include <iostream>

using namespace std;

class Node
{
  public:
	string name;
	int count;
	Node **children;

	Node()
	{
		count = 0;
		children = NULL;
	}

	~Node()
	{
		for (int i = 0; i < count; i++) {
			delete children[i];
		}
		delete[] children;
	}
};

class GeneralTree
{
  private:
	Node *root;

	const string hierarchy[4] = {"Root (subject)", "Chapter", "Section", "Sub-section"};

	void create_node(Node *node, int depth, int n)
	{
		cout << "Enter the name of " << hierarchy[depth] << " " << n << ": ";
		cin >> node->name;

		if (depth < 3) {
			cout << "Enter the number of " << hierarchy[depth + 1] << "s: "; 
			cin >> node->count;

			if (node->count > 0) {
				node->children = new Node *[node->count];
				for (int i = 0; i < node->count; i++) {
					node->children[i] = new Node();
					create_node(node->children[i], depth + 1, i + 1);
				}
			}
		}
	}

	void display_node(const Node *node, int depth, int n)
	{
		cout << string(depth, '\t') << hierarchy[depth] << " " << n 
			<< ": " << node->name << endl;

		// Without hierarchies
		// cout << string(depth, '\t') << node->name << endl;

		for (int i = 0; i < node->count; i++) {
			display_node(node->children[i], depth + 1, i + 1);
		}
	}

  public:
	GeneralTree()
	{
		root = NULL;
	}

	~GeneralTree()
	{
		delete root;
	}

	void create_tree()
	{
		if (root != NULL) {
			delete root;
		}
		root = new Node();
		create_node(root, 0, 0);
	}

	void display_tree()
	{
		if (root == NULL) {
			cout << "Tree is empty.\n";
			return;
		}
		display_node(root, 0, 0);
	}
};

int main() 
{
	GeneralTree gt;
	int choice;

	do {
		cout << "1. Create tree\n2. Display tree\n3. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			gt.create_tree();
			break;
		case 2:
			gt.display_tree();
			break;
		case 3:
			cout << "Exiting\n";
			break;
		default:
			cout << "Enter a valid choice!\n";
		}
	} while (choice != 3);

	return 0;
}
