#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Non printable character used as separator between data instead of space
char sep = '\x1c';

struct Student 
{
	int roll_no;
	string name;
	string division;
	string address;
};

void add_student(const string& filename)
{
	ofstream out_file(filename, ios::app);
	if (!out_file) {
		cout << "Error opening file for writing!" << endl;
		return;
	}

	Student student;
	cout << "Enter roll number: ";
	cin >> student.roll_no;
	cin.ignore();  // To ignore the newline character from previous input
	cout << "Enter name: ";
	getline(cin, student.name);
	cout << "Enter division: ";
	getline(cin, student.division);
	cout << "Enter address: ";
	getline(cin, student.address);

	out_file << student.roll_no << sep << student.name << sep << student.division << sep << student.address << sep << endl;
	out_file.close();
	cout << "Student record added successfully!" << endl;
}

void delete_student(const string& filename)
{
	int roll_no;
	cout << "Enter the roll number of the student to delete: ";
	cin >> roll_no;

	ifstream in_file(filename);
	ofstream temp_file("temp.txt");

	if (!in_file || !temp_file) {
		cout << "Error opening files!" << endl;
		return;
	}

	Student student;
	bool found = false;
	while (in_file >> student.roll_no) {
		in_file.ignore();  // To ignore the newline character after the roll number
		getline(in_file, student.name, sep);
		getline(in_file, student.division, sep);
		getline(in_file, student.address, sep);

		if (student.roll_no == roll_no) {
			found = true;
		} else {
			temp_file << student.roll_no << sep << student.name << sep << student.division << sep << student.address << sep << endl;
		}
	}

	in_file.close();
	temp_file.close();

	// Delete the original file and rename the temp file to original filename
	if (found) {
		remove(filename.c_str()); // because remove expects 'char *'
		rename("temp.txt", filename.c_str()); // because rename also expects 'char *'
		cout << "Student record deleted successfully!" << endl;
	} else {
		cout << "No student found with the given roll number!" << endl;
	}
}

void display_student(const string& filename)
{
	int roll_no;
	cout << "Enter the roll number of the student to display: ";
	cin >> roll_no;

	ifstream in_file(filename);
	if (!in_file) {
		cout << "Error opening file for reading!" << endl;
		return;
	}

	Student student;
	bool found = false;
	while (in_file >> student.roll_no) {
		in_file.ignore();  // To ignore the newline character after the roll number
		getline(in_file, student.name, sep);
		getline(in_file, student.division, sep);
		getline(in_file, student.address, sep);

		if (student.roll_no == roll_no) {
			found = true;
			cout << "Roll Number: " << student.roll_no << endl;
			cout << "Name: " << student.name << endl;
			cout << "Division: " << student.division << endl;
			cout << "Address: " << student.address << endl;
			break;
		}
	}

	in_file.close();

	if (!found) {
		cout << "No student found with the given roll number!" << endl;
	}
}

void update_student(const string& filename)
{
	int roll_no;
	cout << "Enter the roll number of the student to update: ";
	cin >> roll_no;

	ifstream in_file(filename);
	ofstream temp_file("temp.txt");

	if (!in_file || !temp_file) {
		cout << "Error opening files!" << endl;
		return;
	}

	Student student;
	bool found = false;

	while (in_file >> student.roll_no) {
		in_file.ignore();  // To ignore the newline character after the roll number
		getline(in_file, student.name, sep);
		getline(in_file, student.division, sep);
		getline(in_file, student.address, sep);

		if (student.roll_no == roll_no) {
			found = true;
			cout << "Enter new name (current: " << student.name << "): ";
			cin.ignore();  // To clear the previous newline
			getline(cin, student.name);

			cout << "Enter new division (current: " << student.division << "): ";
			getline(cin, student.division);

			cout << "Enter new address (current: " << student.address << "): ";
			getline(cin, student.address);
		}

		temp_file << student.roll_no << sep << student.name << sep << student.division << sep << student.address << sep << endl;
	}

	in_file.close();
	temp_file.close();

	if (found) {
		remove(filename.c_str()); // Remove original file
		rename("temp.txt", filename.c_str()); // Rename temp file to original
		cout << "Student record updated successfully!" << endl;
	} else {
		cout << "No student found with the given roll number!" << endl;
	}
}


int main()
{
	string filename = "students.txt";  // File where student records are stored
	int choice;

	while (true) {
		cout << "\nStudent Information System\n";
		cout << "1. Add student\n";
		cout << "2. Delete student\n";
		cout << "3. Display student information\n";
		cout << "4. Update student information\n";
		cout << "5. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
			case 1:
				add_student(filename);
				break;
			case 2:
				delete_student(filename);
				break;
			case 3:
				display_student(filename);
				break;
			case 4:
				update_student(filename);
				break;
			case 5:
				cout << "Exiting program..." << endl;
				return 0;
			default:
				cout << "Invalid choice, please try again!" << endl;
		}
	}

	return 0;
}
