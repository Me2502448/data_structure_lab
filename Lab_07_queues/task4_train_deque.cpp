

#include <iostream>
using namespace std;

#define MAX 5

class Deque {
private:
    int arr[MAX];
    int front, rear;
    int count;

public:
    Deque() {
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isFull() {
        return count == MAX;
    }

    bool isEmpty() {
        return count == 0;
    }

    // insert at the front
    void insertFront(int id) {
        if (isFull()) {
            cout << "Deque is full! Cannot insert " << id << " at front.\n";
            return;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            front = (front - 1 + MAX) % MAX;   // move front one step back
        }
        arr[front] = id;
        count++;
        cout << id << " inserted at front.\n";
    }

    // insert at the rear
    void insertRear(int id) {
        if (isFull()) {
            cout << "Deque is full! Cannot insert " << id << " at rear.\n";
            return;
        }

        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % MAX;
        }
        arr[rear] = id;
        count++;
        cout << id << " inserted at rear.\n";
    }

    // remove from the front
    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque is empty! Nothing to remove from front.\n";
            return;
        }

        cout << arr[front] << " removed from front.\n";
        front = (front + 1) % MAX;
        count--;
    }

    // remove from the rear
    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque is empty! Nothing to remove from rear.\n";
            return;
        }

        cout << arr[rear] << " removed from rear.\n";
        rear = (rear - 1 + MAX) % MAX;
        count--;
    }

    // display from front to rear
    void display() {
        if (isEmpty()) {
            cout << "Deque is empty.\n";
            return;
        }

        cout << "Front -> ";
        int i = front;
        for (int n = 0; n < count; n++) {
            cout << arr[i];
            if (n != count - 1)
                cout << ", ";
            i = (i + 1) % MAX;
        }
        cout << " <- Rear\n";
    }
};

int main() {
    Deque d;
    int choice, id;

    do {
        cout << "\n===== Train Station Passenger Management =====\n";
        cout << "1. Insert request at front\n";
        cout << "2. Insert request at rear\n";
        cout << "3. Remove request from front\n";
        cout << "4. Remove request from rear\n";
        cout << "5. Display all requests\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter request ID: ";
            cin >> id;
            d.insertFront(id);
            break;
        case 2:
            cout << "Enter request ID: ";
            cin >> id;
            d.insertRear(id);
            break;
        case 3:
            d.deleteFront();
            break;
        case 4:
            d.deleteRear();
            break;
        case 5:
            d.display();
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
