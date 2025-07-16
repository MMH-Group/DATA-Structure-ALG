#include <iostream>
using namespace std;

const int SIZE = 10;

class HashTable {
private:
    int table[SIZE];

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = -1; // -1 means empty
    }

    // Hash function
    int hashFunction(int key) {
        return key % SIZE;
    }

    // Insert using quadratic probing
    void insert(int key) {
        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            index = (hashFunction(key) + i * i) % SIZE;
            i++;

            if (i == SIZE) {
                cout << "Hash table is full! Cannot insert " << key << endl;
                return;
            }
        }

        table[index] = key;
    }

    // Search using quadratic probing
    bool search(int key) {
        int index = hashFunction(key);
        int i = 1;

        while (table[index] != -1) {
            if (table[index] == key)
                return true;
            index = (hashFunction(key) + i * i) % SIZE;
            i++;
            if (i == SIZE)
                break;
        }

        return false;
    }

    // Display the hash table
    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " --> ";
            if (table[i] != -1)
                cout << table[i];
            else
                cout << "EMPTY";
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    int n, val;

    cout << "Enter number of elements to insert: ";
    cin >> n;

    cout << "Enter " << n << " values:\n";
    for (int i = 0; i < n; i++) {
        cin >> val;
        ht.insert(val);
    }

    ht.display();

    cout << "\nEnter a value to search: ";
    cin >> val;
    if (ht.search(val))
        cout << val << " found in the hash table.\n";
    else
        cout << val << " not found in the hash table.\n";

    return 0;
}
