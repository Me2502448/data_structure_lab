#include <iostream>
using namespace std;

struct Node {
    int rollNo;
    Node* next;
};

class StudentList {
private:
    Node* head;

public:
    StudentList() {
        head = NULL;
    }

    void addStudent(int rollNo) {
        Node* newNode = new Node;
        newNode->rollNo = rollNo;
        newNode->next = NULL;

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

    void display() {
        if (head == NULL) {
            cout << "No students registered." << endl;
            return;
        }

        Node* temp = head;
        while (temp != NULL) {
            cout << temp->rollNo;
            if (temp->next != NULL) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    bool search(int rollNo) {
        Node* temp = head;
        while (temp != NULL) {
            if (temp->rollNo == rollNo) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};

int main() {
    StudentList list;

    list.addStudent(101);
    list.addStudent(105);
    list.addStudent(108);
    list.addStudent(112);

    cout << "Registered Students:" << endl;
    list.display();

    int rollNo;
    cout << endl << "Enter Roll Number to Search: ";
    cin >> rollNo;

    if (list.search(rollNo)) {
        cout << "Student Found" << endl;
    } else {
        cout << "Student Not Found" << endl;
    }

    return 0;
}
