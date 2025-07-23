#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> studentMarks;
    int choice;
    string name;
    int marks;

    do {
        cout << "\n===== Student Marks Mapping =====\n";
        cout << "1. Insert student record\n";
        cout << "2. Search for a student\n";
        cout << "3. Display all records\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter student name: ";
            cin >> name;
            cout << "Enter marks: ";
            cin >> marks;
            studentMarks[name] = marks;
            cout << "Record added.\n";
            break;

        case 2:
            cout << "Enter name to search: ";
            cin >> name;
            if (studentMarks.find(name) != studentMarks.end()) {
                cout << name << "'s marks: " << studentMarks[name] << endl;
            } else {
                cout << "Student not found.\n";
            }
            break;

        case 3:
            cout << "\nAll Student Records:\n";
            for (auto& pair : studentMarks) {
                cout << pair.first << " => " << pair.second << endl;
            }
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
