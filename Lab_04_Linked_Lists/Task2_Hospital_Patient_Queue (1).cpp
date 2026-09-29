#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(string value) {
        data = value;
        next = NULL;
    }
};

void insertAtEnd(Node*& head, string value) {
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

void deleteFirst(Node*& head) {
    if (head == NULL) {
        cout << "No patients waiting." << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    cout << "Patient " << temp->data << " is being served." << endl;
    delete temp;
}

int main() {
    Node* head = NULL;

    insertAtEnd(head, "P101");
    insertAtEnd(head, "P102");
    insertAtEnd(head, "P103");
    insertAtEnd(head, "P104");

    cout << "Waiting Patients:" << endl;
    display(head);

    cout << endl;
    deleteFirst(head);

    cout << endl << "Updated Queue:" << endl;
    display(head);

    return 0;
}
