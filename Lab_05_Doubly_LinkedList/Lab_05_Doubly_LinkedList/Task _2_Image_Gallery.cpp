#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string image;
    Node* prev;
    Node* next;
    Node(string img) : image(img), prev(nullptr), next(nullptr) {}
};

class ImageGallery {
    Node* head = nullptr;
    Node* tail = nullptr;
public:
    void addImage(string img) {
        Node* newNode = new Node(img);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    void displayImages() {
        cout << "Gallery (Forward): ";
        for (Node* temp = head; temp; temp = temp->next) cout << temp->image << " | ";
        cout << "\nGallery (Backward): ";
        for (Node* temp = tail; temp; temp = temp->prev) cout << temp->image << " | ";
        cout << endl;
    }
};

int main() {
    ImageGallery gallery;
    gallery.addImage("data_pipeline_arch.png");
    gallery.addImage("eda_plot.jpg");
    gallery.addImage("model_metrics.png");
    gallery.addImage("portfolio_hero.jpg");
    gallery.addImage("logic_gate_circuit.png");
    
    gallery.displayImages();
    return 0;
}