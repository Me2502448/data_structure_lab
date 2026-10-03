#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string song;
    Node* next;
    Node(string s) : song(s), next(nullptr) {}
};

class Playlist {
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    void addSong(string s) {
        Node* newNode = new Node(s);
        if (!head) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head;
        }
    }
    void playTwoRounds() {
        if (!head) return;
        Node* temp = head;
        cout << "Playing Playlist (2 Rounds):\n";
        for (int i = 0; i < 10; i++) { 
            cout << "Playing: " << temp->song << "\n";
            temp = temp->next;
        }
    }
};

int main() {
    Playlist p;
    p.addSong("Track 1");
    p.addSong("Track 2");
    p.addSong("Track 3");
    p.addSong("Track 4");
    p.addSong("Track 5");
    
    p.playTwoRounds();
    return 0;
}