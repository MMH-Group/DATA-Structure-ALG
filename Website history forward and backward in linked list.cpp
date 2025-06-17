#include<iostream>
using namespace std;

class website {
public:
    website* next;
    string WebName;
    website* prev;

    website() {
        next = NULL;
        WebName = "";
        prev = NULL;
    }
};

class browser {
private:
    website* head;
    website* recent;

public:
    browser() {
        head = NULL;
        recent = NULL;
    }

    void search() {
        website* domain = new website();
        cout << "\nEnter Website you want to search: ";
        cin >> domain->WebName;
        cout << "\n" << domain->WebName << " is essential for nowadays. \n";

        if (head == NULL) {
            domain->next = NULL;
            domain->prev = NULL;
            head = domain;
            recent = domain;
            return;
        }

        website* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        domain->prev = temp;
        temp->next = domain;
        recent = domain;
    }

    void history() {
        if (recent == NULL) {
            cout << "\nNo history available.\n";
            return;
        }
        website* temp = recent;
        cout << "\nBrowsing History:\n";
        while (temp != NULL) {
            cout << temp->WebName << "\n";
            temp = temp->prev;
        }
    }

    void forward() {
        if (recent == NULL || recent->next == NULL) {
            cout << "\nThere is no Next Tab\n";
            return;
        }
        recent = recent->next;
        cout << "\nThe Next Tab: " << recent->WebName << endl;
    }

    void previous() {
        if (recent == NULL || recent->prev == NULL) {
            cout << "\nThere is no Previous Tab\n";
            return;
        }
        recent = recent->prev;
        cout << "\nThe Previous Tab: " << recent->WebName << endl;
    }

    void deletehistory() {
        if (head == NULL) {
            cout << "\nHistory is empty.\n";
            return;
        }

        int pos;
        cout << "Enter the position to delete (1-based index): ";
        cin >> pos;

        website* temp = head;
        int count = 1;

        while (temp != NULL && count < pos) {
            temp = temp->next;
            count++;
        }

        if (temp == NULL) {
            cout << "\nInvalid position.\n";
            return;
        }

        if (temp == recent) {
            if (temp->prev)
                recent = temp->prev;
            else if (temp->next)
                recent = temp->next;
            else
                recent = NULL;
        }

        if (temp == head) {
            head = temp->next;
            if (head)
                head->prev = NULL;
        } else {
            temp->prev->next = temp->next;
        }

        if (temp->next)
            temp->next->prev = temp->prev;

        cout << "\nDeleted: " << temp->WebName << endl;
        delete temp;
    }
};

int main() {
    browser google;
    int n = 0;

    do {
        cout << "\n-----MENU-----\n";
        cout << "1. Browse a Website\n";
        cout << "2. Show History\n";
        cout << "3. Forward Tab\n";
        cout << "4. Previous Tab\n";
        cout << "5. Delete History at Position\n";
        cout << "6. Exit\n";
        cout << "Choose Option: ";
        cin >> n;

        switch (n) {
            case 1:
                google.search();
                break;
            case 2:
                google.history();
                break;
            case 3:
                google.forward();
                break;
            case 4:
                google.previous();
                break;
            case 5:
                google.deletehistory();
                break;
            case 6:
                cout << "\nExiting browser...\n";
                break;
            default:
                cout << "\nInvalid Choice!\n";
                break;
        }

    } while (n != 6);

    return 0;
}
