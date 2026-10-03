#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string url;
    Node* prev;
    Node* next;
    Node(string u) : url(u), prev(nullptr), next(nullptr) {}
};

class BrowserHistory {
    Node* head;
    Node* tail;
public:
    BrowserHistory() : head(nullptr), tail(nullptr) {}
    void visit(string url) {
        Node* newNode = new Node(url);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void displayForward() {
        cout << "History (First -> Last): ";
        for (Node* temp = head; temp; temp = temp->next)
            cout << temp->url << " -> ";
        cout << "END\n";
    }
    void displayBackward() {
        cout << "History (Last -> First): ";
        for (Node* temp = tail; temp; temp = temp->prev)
            cout << temp->url << " -> ";
        cout << "START\n";
    }
};

int main() {
    BrowserHistory history;
    history.visit("au.edu.pk");
    history.visit("student.au.edu.pk");
    history.visit("github.com/ABUBAKKAR");
    history.visit("leetcode.com");
    history.visit("kaggle.com");
    
    history.displayForward();
    history.displayBackward();
    return 0;
}