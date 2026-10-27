
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;


bool readInt(const string& prompt, int& out) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) return false;
        try {
            size_t pos = 0;
            long v = stol(line, &pos);
            while (pos < line.size() && isspace((unsigned char)line[pos])) pos++;
            if (pos != line.size() || v < -2000000000L || v > 2000000000L)
                throw invalid_argument("bad");
            out = static_cast<int>(v);
            return true;
        } catch (...) {
            cout << "  Invalid input. Please enter a whole number.\n";
        }
    }
}

// IDs must be positive
bool readId(const string& prompt, int& id) {
    while (true) {
        if (!readInt(prompt, id)) return false;
        if (id > 0) return true;
        cout << "  ID must be a positive number.\n";
    }
}

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    Node* root;

    // ---- helpers (recursive) --------------------------------
    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    Node* insertNode(Node* node, int value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(value);
        }
        if (value < node->data)
            node->left = insertNode(node->left, value, inserted);
        else if (value > node->data)
            node->right = insertNode(node->right, value, inserted);
        return node;                       // duplicate: nothing changes
    }

    Node* findMin(Node* node) const {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int value, bool& found) {
        if (node == nullptr) return nullptr;

        if (value < node->data) {
            node->left = deleteNode(node->left, value, found);
        } else if (value > node->data) {
            node->right = deleteNode(node->right, value, found);
        } else {
            found = true;
            // Case 1 (leaf) & Case 2 (only right child)
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2 (only left child)
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: two children -> copy in-order successor, delete it
            Node* successor = findMin(node->right);
            node->data = successor->data;
            bool dummy = false;
            node->right = deleteNode(node->right, successor->data, dummy);
        }
        return node;
    }

    void inorder(const Node* n) const {
        if (n == nullptr) return;
        inorder(n->left);
        cout << n->data << " ";
        inorder(n->right);
    }
    void preorder(const Node* n) const {
        if (n == nullptr) return;
        cout << n->data << " ";
        preorder(n->left);
        preorder(n->right);
    }
    void postorder(const Node* n) const {
        if (n == nullptr) return;
        postorder(n->left);
        postorder(n->right);
        cout << n->data << " ";
    }
    void collectInorder(const Node* n, vector<int>& out) const {
        if (n == nullptr) return;
        collectInorder(n->left, out);
        out.push_back(n->data);
        collectInorder(n->right, out);
    }

    int countHelper(const Node* n) const {
        if (n == nullptr) return 0;
        return 1 + countHelper(n->left) + countHelper(n->right);
    }

    int heightHelper(const Node* n) const {
        if (n == nullptr) return 0;
        int l = heightHelper(n->left);
        int r = heightHelper(n->right);
        return 1 + (l > r ? l : r);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }              // releases every node

    // Copying would double-free nodes, so it is disabled
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    bool isEmpty() const { return root == nullptr; }

    // ---- 1. Insert -----------------------------------------
    bool insert(int value) {
        bool inserted = false;
        root = insertNode(root, value, inserted);
        if (inserted)
            cout << "  ID " << value << " inserted successfully.\n";
        else
            cout << "  ID " << value << " already exists. Duplicate rejected, tree unchanged.\n";
        return inserted;
    }

    // ---- 2. Search -----------------------------------------
    bool search(int value) const {
        if (root == nullptr) {
            cout << "  Tree is empty. Cannot search for " << value << ".\n";
            return false;
        }
        const Node* cur = root;
        while (cur != nullptr) {
            if (value == cur->data) {
                cout << "  ID " << value << " FOUND in the tree.\n";
                return true;
            }
            cur = (value < cur->data) ? cur->left : cur->right;
        }
        cout << "  ID " << value << " NOT FOUND in the tree.\n";
        return false;
    }

    // ---- 3. Delete -----------------------------------------
    bool remove(int value) {
        if (root == nullptr) {
            cout << "  Tree is empty. Nothing to delete.\n";
            return false;
        }
        bool found = false;
        root = deleteNode(root, value, found);
        if (!found) {
            cout << "  ID " << value << " does not exist. Tree unchanged.\n";
            return false;
        }
        cout << "  ID " << value << " deleted successfully.\n";
        cout << "  Updated IDs: ";
        if (root == nullptr) cout << "(tree is now empty)";
        else inorder(root);
        cout << endl;
        return true;
    }

    // ---- 4, 5, 6. Traversals --------------------------------
    void displayInorder() const {
        if (root == nullptr) { cout << "  Tree is empty.\n"; return; }
        cout << "  In-order   : "; inorder(root);   cout << endl;
    }
    void displayPreorder() const {
        if (root == nullptr) { cout << "  Tree is empty.\n"; return; }
        cout << "  Pre-order  : "; preorder(root);  cout << endl;
    }
    void displayPostorder() const {
        if (root == nullptr) { cout << "  Tree is empty.\n"; return; }
        cout << "  Post-order : "; postorder(root); cout << endl;
    }

    // ---- 7, 8. Count & height -------------------------------
    int countNodes() const { return countHelper(root); }
    int height() const     { return heightHelper(root); }

    // For the prediction test
    vector<int> inorderValues() const {
        vector<int> v;
        collectInorder(root, v);
        return v;
    }
};

// ------------------------------------------------------------
// Requirement 9, 10, 11 : prediction test + repeated deletion
// ------------------------------------------------------------
struct Operation {
    char type;      // 'I' = insert, 'D' = delete
    int  id;
};

void printVector(const vector<int>& v) {
    for (int x : v) cout << x << " ";
    cout << endl;
}

void runPredictionTest() {
    cout << "==========================================================\n";
    cout << " PREDICTION TEST (Requirement 9, 10, 11)\n";
    cout << "==========================================================\n";

    BST t;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : initial) t.insert(id);
    cout << "\nInitial tree:\n";
    t.displayInorder();
    cout << "  Nodes: " << t.countNodes() << ", Height: " << t.height() << "\n";

    // Instructor-style sequence (replace with the instructor's own list)
    vector<Operation> ops = {
        {'I', 60}, {'I', 30}, {'D', 25}, {'D', 55}, {'D', 45}, {'I', 90}
    };

    cout << "\nOperation sequence: ";
    for (const Operation& op : ops)
        cout << (op.type == 'I' ? "Insert " : "Delete ") << op.id << ", ";
    cout << "\n";

    // ---- Predictions made BEFORE running (worked out by hand) ----
    vector<int> predictedInorder = {30, 35, 40, 50, 60, 65, 75, 85, 90};
    int predictedHeight = 4;
    int predictedCount  = 9;
    cout << "\nPREDICTED in-order : "; printVector(predictedInorder);
    cout << "PREDICTED height   : " << predictedHeight << "\n";
    cout << "PREDICTED nodes    : " << predictedCount << "\n";

    // ---- Run the operations --------------------------------------
    cout << "\nRunning operations...\n";
    for (const Operation& op : ops) {
        if (op.type == 'I') t.insert(op.id);
        else                t.remove(op.id);
    }

    vector<int> actual = t.inorderValues();
    cout << "\nACTUAL in-order    : "; printVector(actual);
    cout << "ACTUAL height      : " << t.height() << "\n";
    cout << "ACTUAL nodes       : " << t.countNodes() << "\n";

    bool match = (actual == predictedInorder) &&
                 (t.height() == predictedHeight) &&
                 (t.countNodes() == predictedCount);
    cout << "\nComparison: " << (match ? "MATCH - prediction was correct."
                                       : "MISMATCH - re-check the prediction.") << "\n";

    // ---- Requirement 10: repeated deletion -----------------------
    cout << "\n--- Repeated deletion of the same ID (40) ---\n";
    cout << "First attempt:\n";  t.remove(40);
    cout << "Second attempt:\n"; t.remove(40);
    cout << "Behaviour: the first call finds and removes 40. The second call walks\n"
         << "the tree, reaches nullptr without finding 40, so 'found' stays false;\n"
         << "the program prints 'does not exist' and the tree is not modified\n"
         << "(no crash, no double free).\n";

    // ---- Requirement 11: explanation -----------------------------
    cout << "\n--- Deleting a node with two children ---\n"
         << "Every value in the left subtree is smaller than the node and every value\n"
         << "in the right subtree is larger. The in-order successor (smallest value\n"
         << "of the right subtree) is larger than everything in the left subtree and\n"
         << "smaller than or equal to everything else in the right subtree. Copying\n"
         << "it into the deleted node's position therefore keeps left < node < right.\n"
         << "The successor has no left child, so removing its old node is a simple\n"
         << "leaf/one-child deletion that cannot break the ordering.\n";
    cout << "==========================================================\n\n";
}

// ------------------------------------------------------------
// Menu
// ------------------------------------------------------------
void showMenu() {
    cout << "\n===== Hospital & Emergency Inventory (BST) =====\n"
         << " 1. Insert an ID\n"
         << " 2. Search for an ID\n"
         << " 3. Delete an ID\n"
         << " 4. Display in-order traversal\n"
         << " 5. Display pre-order traversal\n"
         << " 6. Display post-order traversal\n"
         << " 7. Count the total number of nodes\n"
         << " 8. Calculate the height of the BST\n"
         << " 9. Exit\n"
         << "================================================\n";
}

int main() {
    // Predict-then-verify test runs first on its own separate tree
    runPredictionTest();

    // Main application tree
    BST tree;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    cout << "Loading initial IDs into the application tree...\n";
    for (int id : initial) tree.insert(id);

    int choice = 0;
    do {
        showMenu();
        if (!readInt("Enter your choice (1-9): ", choice)) {
            cout << "\nInput ended. Exiting.\n";
            break;
        }

        int id;
        switch (choice) {
            case 1:
                if (readId("Enter ID to insert: ", id)) tree.insert(id);
                break;
            case 2:
                if (readId("Enter ID to search: ", id)) tree.search(id);
                break;
            case 3:
                if (readId("Enter ID to delete: ", id)) tree.remove(id);
                break;
            case 4: tree.displayInorder();   break;
            case 5: tree.displayPreorder();  break;
            case 6: tree.displayPostorder(); break;
            case 7:
                cout << "  Total number of nodes: " << tree.countNodes() << "\n";
                break;
            case 8:
                cout << "  Height of the BST: " << tree.height()
                     << " level(s)";
                if (tree.isEmpty()) cout << " (tree is empty)";
                cout << "\n";
                break;
            case 9:
                cout << "  Exiting... memory released by destructor. Goodbye!\n";
                break;
            default:
                cout << "  Invalid choice! Please enter a number from 1 to 9.\n";
        }
    } while (choice != 9);

    return 0;
}
