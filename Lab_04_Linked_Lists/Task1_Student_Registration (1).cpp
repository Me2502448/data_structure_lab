#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = NULL;
    }
};

void insertAtEnd(Node*& head, int value) {
    Node* newNode = new Node(value);
    if (head == NULL) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void display(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->data;
        if (temp->next != NULL) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << endl;
}

bool search(Node* head, int key) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == key) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int main() {
    Node* head = NULL;

    insertAtEnd(head, 101);
    insertAtEnd(head, 105);
    insertAtEnd(head, 108);
    insertAtEnd(head, 112);

    cout << "Registered Students:" << endl;
    display(head);

    int roll;
    cout << endl << "Enter Roll Number to Search: ";
    cin >> roll;

    if (search(head, roll)) {
        cout << "Student Found" << endl;
    } else {
        cout << "Student Not Found" << endl;
    }

    return 0;
}
