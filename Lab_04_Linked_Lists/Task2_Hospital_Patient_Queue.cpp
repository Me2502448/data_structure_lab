#include <iostream>
#include <string>
using namespace std;

struct Node {
    string patientId;
    Node* next;
};

class PatientQueue {
private:
    Node* head;

public:
    PatientQueue() {
        head = NULL;
    }

    void addPatient(string patientId) {
        Node* newNode = new Node;
        newNode->patientId = patientId;
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
            cout << "No patients waiting." << endl;
            return;
        }

        Node* temp = head;
        while (temp != NULL) {
            cout << temp->patientId;
            if (temp->next != NULL) {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    void servePatient() {
        if (head == NULL) {
            cout << "No patients to serve." << endl;
            return;
        }

        Node* temp = head;
        head = head->next;
        cout << "Patient " << temp->patientId << " is being served." << endl;
        delete temp;
    }
};

int main() {
    PatientQueue queue;

    queue.addPatient("P101");
    queue.addPatient("P102");
    queue.addPatient("P103");
    queue.addPatient("P104");

    cout << "Waiting Patients:" << endl;
    queue.display();

    cout << endl;
    queue.servePatient();

    cout << endl << "Updated Queue:" << endl;
    queue.display();

    return 0;
}
