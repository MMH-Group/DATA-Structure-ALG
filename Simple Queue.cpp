#include<iostream>
using namespace std;

struct Queue {
    string name;
    int age;
    char gender;
};

struct Node {
    Queue data;
    Node* next;
};

class linkedlist {
private:
    Node* head;
    int front = -1;
    int rare = -1;

public:
    linkedlist() {
        head = NULL;
    }

    void insertQueue() {
        rare++;
        Node* point = new Node();
        cout << "\nEnter Name:";
        cin >> point->data.name;
        cout << "\nEnter Age:";
        cin >> point->data.age;
        cout << "\nEnter Gender (M/F):";
        cin >> point->data.gender;

        point->next = NULL; 

        if (rare == 0) {
            front = 0;
        }

        if (head == NULL) {
            head = point;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = point;  
        }
    }

    void serveQueue() {
        if (front >= 0) {
            if (head == NULL) {
                cout << "\nThe Queue is Empty!\n";
                return;
            }
            
            cout << "Processing...... " << head->data.name << " has been served\n";

            switch (head->data.gender) {
                case 'M': case 'm':
                    cout << "Because he is " << head->data.age << " years old\n";
                    break;
                case 'F': case 'f':
                    cout << "Because she is " << head->data.age << " years old\n";
                    break;
                default:
                    cout << "Because (he/she) is " << head->data.age << " years old\n";
                    break;
            }

            Node* temp = head;
            head = head->next;  
            delete temp;

            rare--;  
            if (rare < 0) front = -1;
        } else {
            cout << "\nThe Queue is Empty!\n";
        }
    }

    void displayQueue() {
        if (front >= 0 && head != NULL) {
            Node* temp = head;
            int i = 1;

            while (temp) {
                cout << "\nPerson " << i << ":\n";
                cout << "Name: " << temp->data.name << "\n";
                cout << "Age: " << temp->data.age << "\n";
                cout << "Gender: " << temp->data.gender << "\n";
                temp = temp->next;
                i++;
            }
        } else {
            cout << "\nThe Queue is Empty!\n";
        }
    }
};

int main() {
    linkedlist hospital;
    int n;
    menu:
    cout << "\n1. Enter a person in the Queue.";
    cout << "\n2. Serve a person.";
    cout << "\n3. Show the list.";
    cout << "\n4. Exit\n";
    cout << "Enter choice: ";
    cin >> n;

    switch (n) {
        case 1:
            hospital.insertQueue();
            goto menu;
        case 2:
            hospital.serveQueue();
            goto menu;
        case 3:
            hospital.displayQueue();
            goto menu;
        case 4:
            return 0;
        default:
            cout << "\nInvalid choice! Try again.\n";
            goto menu;
    }
}
