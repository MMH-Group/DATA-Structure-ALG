#include <iostream>
using namespace std;

const int MAX = 100;

struct Patient {
    char name[50];
    int priority; // 1 = Critical, 2 = Emergency, etc.
};

int main() {
    Patient queue[MAX];
    int n;

    cout << "Enter number of patients: ";
    cin >> n;

    // Input patients
    for (int i = 0; i < n; i++) {
        cout << "\nEnter name of patient " << i + 1 << ": ";
        cin >> queue[i].name;

        cout << "Enter priority (1=Critical, 2=Emergency, 3=Urgent...): ";
        cin >> queue[i].priority;
    }

    // Sort patients by priority (bubble sort)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (queue[i].priority > queue[j].priority) {
                Patient temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }

    // Display patients in treatment order
    cout << "\n--- Treatment Order ---\n";
    for (int i = 0; i < n; i++) {
        cout << queue[i].name << " (Priority: " << queue[i].priority << ")\n";
    }

    return 0;
}
