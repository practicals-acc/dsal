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

  public:
	GeneralTree()
	{
		root = NULL;
	}

	~GeneralTree()
	{
		delete root;
	}

	void create_tree();
	void display_tree();
};

void GeneralTree::create_tree()
{
	if (root != NULL) {
		delete root;
	}

	root = new Node;

	cout << "Enter the name of root (Subject): ";
	cin >> root->name;

	cout << "Enter the number of chapters: ";
	cin >> root->count;
	root->children = new Node *[root->count];

	for (int i = 0; i < root->count; i++) {
		root->children[i] = new Node;
		cout << "Enter the name of chapter " << (i + 1) << ": ";
		cin >> root->children[i]->name;

		cout << "Enter the number of sections: ";
		cin >> root->children[i]->count;
		root->children[i]->children = new Node *[root->children[i]->count];
		for (int j = 0; j < root->children[i]->count; j++) {
			root->children[i]->children[j] = new Node;
			cout << "Enter the name of section " << (j + 1) << ": ";
			cin >> root->children[i]->children[j]->name; 

			cout << "Enter the number of sub sections: ";
			cin >> root->children[i]->children[j]->count;
			root->children[i]->children[j]->children = new Node *[root->children[i]->children[j]->count];

			for (int k = 0; k < root->children[i]->children[j]->count; k++) {
				root->children[i]->children[j]->children[k] = new Node;
				cout << "Enter the name of sub-section " << (k + 1) << ": ";
				cin >> root->children[i]->children[j]->children[k]->name;
			}
		}
	}
}

void GeneralTree::display_tree()
{
	if (!root) {
		cout << "Tree is empty.\n";
		return;
        }

	cout << "Root: " << root->name << endl;
	
	for (int i = 0; i < root->count; i++) {
		cout << "\tChapter " << (i + 1) << ": " << root->children[i]->name << endl;

		for (int j = 0; j < root->children[i]->count; j++) {
			cout << "\t\tSection " << (j + 1) << ": " << root->children[i]->children[j]->name << endl; 

			for (int k = 0; k < root->children[i]->children[j]->count; k++) {
				cout << "\t\t\tSub-section " << (k + 1) << ": " <<  root->children[i]->children[j]->children[k]->name << endl;
			}
		}
	}
}

int main()
{
	int choice;
	GeneralTree gt;

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
				cout << "Exitting\n";
				break;
			default:
				cout << "Enter a valid choice!\n";
		}
	} while (choice != 3);

	return 0;
}
