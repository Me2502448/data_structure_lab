

#include <iostream>
using namespace std;

#define MAX 5

class PacketQueue {
private:
    int arr[MAX];
    int front, rear;
    int count;   // number of packets currently in the buffer

public:
    PacketQueue() {
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

    // insert a packet id
    void enqueue(int id) {
        if (isFull()) {
            cout << "Buffer is full! Packet " << id << " cannot be stored.\n";
            return;
        }

        rear = (rear + 1) % MAX;   // moves back to 0 after the last index
        arr[rear] = id;
        count++;
        cout << "Packet " << id << " stored at position " << rear << ".\n";
    }

    // transmit the oldest packet
    void dequeue() {
        if (isEmpty()) {
            cout << "Buffer is empty! No packet to transmit.\n";
            return;
        }

        cout << "Packet " << arr[front] << " transmitted from position " << front << ".\n";
        front = (front + 1) % MAX;
        count--;
    }

    // show all packets from front to rear
    void display() {
        if (isEmpty()) {
            cout << "No packets waiting.\n";
            return;
        }

        cout << "Packets waiting: ";
        int i = front;
        for (int n = 0; n < count; n++) {
            cout << arr[i] << " ";
            i = (i + 1) % MAX;
        }
        cout << endl;
    }
};

int main() {
    PacketQueue q;
    int choice, id;

    do {
        cout << "\n===== Network Packet Management =====\n";
        cout << "1. Insert packet\n";
        cout << "2. Transmit packet\n";
        cout << "3. Display waiting packets\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter packet ID: ";
            cin >> id;
            q.enqueue(id);
            break;
        case 2:
            q.dequeue();
            break;
        case 3:
            q.display();
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
