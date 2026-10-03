#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string player;
    Node* next;
    Node(string p) : player(p), next(nullptr) {}
};

class Game {
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    void addPlayer(string p) {
        Node* newNode = new Node(p);
        if (!head) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head; 
        }
    }
    void simulateTurns() {
        if (!head) return;
        Node* temp = head;
        cout << "Player Turns: \n";
        for (int i = 0; i < 6; i++) { 
            cout << "Turn " << i + 1 << ": " << temp->player << "\n";
            if (i == 4) cout << "--- Round ends, returning to first player ---\n";
            temp = temp->next;
        }
    }
};

int main() {
    Game g;
    g.addPlayer("Abu bakkar");
    g.addPlayer("Rafique");
    g.addPlayer("Player 3");
    g.addPlayer("Player 4");
    g.addPlayer("Player 5");
    
    g.simulateTurns();
    return 0;
}