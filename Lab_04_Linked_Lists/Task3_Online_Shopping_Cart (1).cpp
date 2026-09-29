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

void deleteByValue(Node*& head, string key) {
    if (head == NULL) {
        cout << "Cart is empty." << endl;
        return;
    }
    if (head->data == key) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }
    Node* temp = head;
    while (temp->next != NULL && temp->next->data != key) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        cout << "Product not found." << endl;
        return;
    }
    Node* del = temp->next;
    temp->next = del->next;
    delete del;
}

int main() {
    Node* head = NULL;

    insertAtEnd(head, "P101");
    insertAtEnd(head, "P205");
    insertAtEnd(head, "P310");
    insertAtEnd(head, "P415");

    cout << "Shopping Cart:" << endl;
    display(head);

    string id;
    cout << endl << "Remove Product: ";
    cin >> id;
    deleteByValue(head, id);

    cout << endl << "Updated Cart:" << endl;
    display(head);

    return 0;
}
