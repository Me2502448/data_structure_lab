
#include <iostream>
#include <string>
using namespace std;

#define MAX 10

class Patient {
public:
    string id;
    int priority;
};

class PriorityQueue {
private:
    Patient arr[MAX];
    int size;

public:
    PriorityQueue() {
        size = 0;
    }

    // insert patient in the correct place so the array is always sorted by priority
    void enqueue(string id, int priority) {
        if (size == MAX) {
            cout << "Queue is full! Cannot add patient " << id << ".\n";
            return;
        }

        // find the position where the new patient should go
        int pos = size;
        while (pos > 0 && arr[pos - 1].priority > priority) {
            arr[pos] = arr[pos - 1];   // shift right
            pos--;
        }

        arr[pos].id = id;
        arr[pos].priority = priority;
        size++;
        cout << "Patient " << id << " added with priority " << priority << ".\n";
    }

    // treat the patient at the front (highest priority)
    void dequeue() {
        if (size == 0) {
            cout << "Queue is empty! No patient is waiting.\n";
            return;
        }

        cout << "Treating patient " << arr[0].id << " (priority " << arr[0].priority << ").\n";

        // shift everything left
        for (int i = 0; i < size - 1; i++)
            arr[i] = arr[i + 1];
        size--;
    }

    void display() {
        if (size == 0) {
            cout << "No patients waiting.\n";
            return;
        }

        cout << "Waiting patients:\n";
        for (int i = 0; i < size; i++)
            cout << "  " << arr[i].id << "  -> priority " << arr[i].priority << endl;
    }
};

int main() {
    PriorityQueue pq;
    int choice, priority;
    string id;

    do {
        cout << "\n===== Hospital Emergency Department =====\n";
        cout << "1. Add patient\n";
        cout << "2. Treat next patient\n";
        cout << "3. Display waiting patients\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter patient ID (e.g. P101): ";
            cin >> id;
            cout << "Enter priority (1 = highest): ";
            cin >> priority;
            pq.enqueue(id, priority);
            break;
        case 2:
            pq.dequeue();
            break;
        case 3:
            pq.display();
            break;
        case 0:
            cout << "Program ended.\n";
            break;
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 0);

    return 0;
}
