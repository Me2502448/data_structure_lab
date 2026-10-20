// Task 1: Bank Customer Service System
// Simple (linear) queue using an array

#include <iostream>
using namespace std;

#define MAX 5

class BankQueue {
private:
    int arr[MAX];
    int front, rear;

public:
    BankQueue() {
        front = -1;
        rear = -1;
    }

    // add a customer token at the rear
    void enqueue(int token) {
        if (rear == MAX - 1) {
            cout << "Queue Overflow! No more customers can be added.\n";
            return;
        }
        if (front == -1)
            front = 0;

        rear++;
        arr[rear] = token;
        cout << "Customer " << token << " is added to the queue.\n";
    }

    // serve the customer at the front
    void dequeue() {
        if (front == -1) {
            cout << "Queue Underflow! No customer is waiting.\n";
            return;
        }

        cout << "Customer " << arr[front] << " is served.\n";
        front++;

        // queue became empty, reset it
        if (front > rear) {
            front = -1;
            rear = -1;
        }
    }

    // show all waiting customers
    void display() {
        if (front == -1) {
            cout << "No customer is waiting.\n";
            return;
        }

        cout << "Waiting customers: ";
        for (int i = front; i <= rear; i++)
            cout << arr[i] << " ";
        cout << endl;
    }

    // number of waiting customers
    int countWaiting() {
        if (front == -1)
            return 0;
        return rear - front + 1;
    }
};

int main() {
    BankQueue q;
    int choice, token;

    do {
        cout << "\n===== Bank Customer Service System =====\n";
        cout << "1. Add customer (Enqueue)\n";
        cout << "2. Serve customer (Dequeue)\n";
        cout << "3. Display waiting customers\n";
        cout << "4. Number of waiting customers\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter token number: ";
            cin >> token;
            q.enqueue(token);
            break;
        case 2:
            q.dequeue();
            break;
        case 3:
            q.display();
            break;
        case 4:
            cout << "Customers waiting: " << q.countWaiting() << endl;
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
