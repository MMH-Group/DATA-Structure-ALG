#include <iostream>
#include <string>

using namespace std;

struct transation {
    int transaction_ID = 1;
    string type;
    int purchase;
    transation* next;
    transation* prv;
};

struct accounts {
    int acc_id = 1;
    string user_name;
    accounts* next;
    transation* head;
    accounts* prv;
};

class tran {
public:
    void insertinlink(transation*& head) {
        char ck;
        do {
            int purchase;
            string tp;

            cout << "\nEnter Purchase: ";
            cin >> purchase;
            cin.ignore(); 

            cout << "\nEnter Note: ";
            getline(cin, tp);

            transation* node = new transation();
            node->purchase = purchase;
            node->type = tp;

            if (head) {
                transation* temp = head;
                while (temp->next) {
                    temp = temp->next;
                }
                node->transaction_ID = temp->transaction_ID + 1;
                temp->next = node;
                node->prv = temp;
            } else {
                head = node;
            }

            node->next = NULL;

            cout << "\nPress 'Y' to enter another transaction: ";
            cin >> ck;
        } while (ck == 'Y' || ck == 'y');
    }

    void searchtran(transation* head) {
        transation* temp = head;
        while (temp) {
            cout << "\nTransaction ID: " << temp->transaction_ID << endl;
            cout << "Purchase: " << temp->purchase << endl;
            cout << "Note: " << temp->type << endl;
            temp = temp->next;
        }
    }

    void totaltransations(transation* head) {
        transation* temp = head;
        int sum = 0;
        while (temp) {
            sum += temp->purchase;
            temp = temp->next;
        }
        cout << "\nThe Total amount you have spent is: " << sum << " Rs\n";
    }

    void display(transation* head) {
        transation* temp = head;
        while (temp) {
            cout << "\nTransaction ID: " << temp->transaction_ID << endl;
            cout << "Purchase: " << temp->purchase << endl;
            cout << "Note: " << temp->type << endl;
            temp = temp->next;
        }
    }
};

class record {
    accounts* acc_head;
    int count = 0;

public:
    record() {
        acc_head = NULL;
    }

    void newaccount() {
        string name;
        cout << "\nEnter Name: ";
        cin.ignore();
        getline(cin, name);

        accounts* acc = new accounts();
        count++;

        if (acc_head) {
            accounts* temp = acc_head;
            while (temp->next) {
                temp = temp->next;
            }
            acc->acc_id = temp->acc_id + 1;
            temp->next = acc;
            acc->prv = temp;
        } else {
            acc_head = acc;
            acc->prv = NULL;
        }

        cout << "\nYour Account ID is: " << acc->acc_id << endl;
        acc->user_name = name;
        acc->next = NULL;
        acc->head = NULL;

        tran chain;
        chain.insertinlink(acc->head);
    }

    void searchaccount() {
        int acid, attempts = 3;
        string pn;

        while (attempts > 0) {
            cout << endl << "Enter Name: ";
            cin.ignore();
            getline(cin, pn);
            cout << endl << "Enter Account ID: ";
            cin >> acid;

            accounts* temp = acc_head;
            while (temp) {
                if (pn == temp->user_name && acid == temp->acc_id) {
                    cout << "\n \t Transaction records\n\n";
                    tran temp1;
                    temp1.searchtran(temp->head);
                    return;
                }
                temp = temp->next;
            }

            attempts--;
            if (attempts > 0) {
                cout << endl << "Invalid ID or Name! Attempts left: " << attempts << endl;
            } else {
                cout << endl << "Access limit reached! Returning to menu..." << endl;
            }
        }
    }

    void addtoaccount() {
        int acid, attempts = 3;
        string pn;

        while (attempts > 0) {
            cout << endl << "Enter Name: ";
            cin.ignore();
            getline(cin, pn);
            cout << endl << "Enter Account ID: ";
            cin >> acid;

            accounts* temp = acc_head;
            while (temp) {
                if (pn == temp->user_name && acid == temp->acc_id) {
                    tran temp1;
                    temp1.insertinlink(temp->head);
                    return;
                }
                temp = temp->next;
            }

            attempts--;
            if (attempts > 0) {
                cout << endl << "Invalid ID or Name! Attempts left: " << attempts << endl;
            } else {
                cout << endl << "Access limit reached! Returning to menu..." << endl;
            }
        }
    }

    int totalacc() {
        return count;
    }

    void totalexpense() {
        int acid, attempts = 3;
        string pn;

        while (attempts > 0) {
            cout << endl << "Enter Name: ";
            cin.ignore();
            getline(cin, pn);
            cout << endl << "Enter Account ID: ";
            cin >> acid;

            accounts* temp = acc_head;
            while (temp) {
                if (pn == temp->user_name && acid == temp->acc_id) {
                    tran temp1;
                    temp1.totaltransations(temp->head);
                    return;
                }
                temp = temp->next;
            }

            attempts--;
            if (attempts > 0) {
                cout << endl << "Invalid ID or Name! Attempts left: " << attempts << endl;
            } else {
                cout << endl << "Access limit reached! Returning to menu..." << endl;
            }
        }
    }

    void display() {
        accounts* temp = acc_head;
        while (temp) {
            cout << "\nName: " << temp->user_name << endl;
            cout << "Account ID: " << temp->acc_id << endl;
            char ans;
            cout << "\nPress 'Y' if you want transaction details: ";
            cin >> ans;
            if (ans == 'y' || ans == 'Y') {
                tran temp1;
                temp1.display(temp->head);
            }
            temp = temp->next;
        }
    }
};

int main() {
    int a, pass = 1234, p;
    record m;

    while (true) {
        cout << "\t\tMenu\n";
        cout << endl << "1. New Account.";
        cout << endl << "2. Search Account.";
        cout << endl << "3. Add Transaction to Existing Account.";
        cout << endl << "4. Display Number of Accounts.";
        cout << endl << "5. Total Transactions of an Account.";
        cout << endl << "6. Display All Accounts.";
        cout << endl << "7. Exit.";

        cout << endl << "\nEnter choice: ";
        cin >> a;

        switch (a) {
            case 1: 
				m.newaccount(); 
				break;
            case 2: 
				m.searchaccount(); 
				break;
            case 3: 
				m.addtoaccount(); 
				break;
            case 4: 
				cout << "\nTotal accounts are: " << m.totalacc() << endl; 
				break;
            case 5: 
				m.totalexpense(); 
				break;
            case 6:
                cout << "Enter Password: ";
                cin >> p;
                if (pass == p) m.display();
                else cout << "\nInvalid password!\n";
                break;
            case 7: 
				return 0;
            default: cout << "\nInvalid choice! Try again.\n";
        }
    }
}
