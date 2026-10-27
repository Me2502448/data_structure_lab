
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

//
bool readInt(const string& prompt, int& out) {
    string line;
    while (true) {
        cout << prompt;
        if (!getline(cin, line)) return false;
        try {
            size_t pos = 0;
            long v = stol(line, &pos);
            while (pos < line.size() && isspace((unsigned char)line[pos])) pos++;
            if (pos != line.size() || v < 0 || v > 2000000000L)
                throw invalid_argument("bad");
            out = static_cast<int>(v);
            return true;
        } catch (...) {
            cout << "  Invalid input. Please enter a positive whole number.\n";
        }
    }
}


class StaffNode {
public:
    string name;
    StaffNode* left;
    StaffNode* right;

    StaffNode(const string& n) : name(n), left(nullptr), right(nullptr) {}
};

class StaffTree {
private:
    StaffNode* root;

    void destroy(StaffNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    // Pre-order walk: print each node with its children (NULL if absent)
    void showRelations(StaffNode* node) const {
        if (node == nullptr) return;
        cout << "  " << node->name
             << "  -> Left: "  << (node->left  ? node->left->name  : "NULL")
             << " | Right: "   << (node->right ? node->right->name : "NULL") << endl;
        showRelations(node->left);
        showRelations(node->right);
    }

    void inorder(StaffNode* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->name << " | ";
        inorder(node->right);
    }

public:
    StaffTree() : root(nullptr) {}
    ~StaffTree() { destroy(root); }
    StaffTree(const StaffTree&) = delete;
    StaffTree& operator=(const StaffTree&) = delete;

    // Manually link 7 staff members (no ordering rule is applied)
    void build() {
        root               = new StaffNode("Dr. Khan");     // Vice Chancellor
        root->left         = new StaffNode("Ms. Sana");     // Dean
        root->right        = new StaffNode("Mr. Bilal");    // Registrar
        root->left->left   = new StaffNode("Dr. Zara");     // HOD
        root->left->right  = new StaffNode("Mr. Ali");      // HOD
        root->right->left  = new StaffNode("Ms. Hina");     // Accountant
        root->right->right = new StaffNode("Dr. Umar");     // Librarian
    }

    void displayRelations() const {
        cout << "Staff member and their children:\n";
        showRelations(root);
    }

    void displayInorder() const {
        cout << "In-order traversal of names: ";
        inorder(root);
        cout << endl;
    }
};

// =============
// ============================================================
class BSTNode {
public:
    int id;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value) : id(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // ---- memory helpers -------------------------------------
    static void destroy(BSTNode* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    // Deep copy of a whole subtree (used for the "fresh copy")
    static BSTNode* clone(const BSTNode* node) {
        if (node == nullptr) return nullptr;
        BSTNode* copy = new BSTNode(node->id);
        copy->left  = clone(node->left);
        copy->right = clone(node->right);
        return copy;
    }

    // ---- insertion ------------------------------------------
    BSTNode* insert(BSTNode* node, int value, bool& inserted) {
        if (node == nullptr) {
            inserted = true;
            return new BSTNode(value);
        }
        if (value < node->id)
            node->left = insert(node->left, value, inserted);
        else if (value > node->id)
            node->right = insert(node->right, value, inserted);
        // value == node->id : duplicate, nothing changes
        return node;
    }

    // ---- deletion -------------------------------------------
    BSTNode* findMin(BSTNode* node) const {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // 'report' = print which deletion case happened
    BSTNode* remove(BSTNode* node, int value, bool& found, bool report) {
        if (node == nullptr) return nullptr;

        if (value < node->id) {
            node->left = remove(node->left, value, found, report);
        } else if (value > node->id) {
            node->right = remove(node->right, value, found, report);
        } else {
            found = true;

            // Case 1 (leaf) and Case 2 (only right child)
            if (node->left == nullptr) {
                if (report) {
                    if (node->right == nullptr)
                        cout << "  [Case 1: leaf node] removed directly.\n";
                    else
                        cout << "  [Case 2: one child] replaced by its right child "
                             << node->right->id << ".\n";
                }
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2 (only left child)
            if (node->right == nullptr) {
                if (report)
                    cout << "  [Case 2: one child] replaced by its left child "
                         << node->left->id << ".\n";
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: two children -> use in-order successor
            BSTNode* successor = findMin(node->right);
            if (report)
                cout << "  [Case 3: two children] replaced by in-order successor "
                     << successor->id << ".\n";
            node->id = successor->id;
            bool dummy = false;
            node->right = remove(node->right, successor->id, dummy, false);
        }
        return node;
    }

    void inorder(const BSTNode* node) const {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->id << " ";
        inorder(node->right);
    }

    void printTree(const BSTNode* node, int depth) const {
        if (node == nullptr) return;
        printTree(node->right, depth + 1);
        cout << string(depth * 6, ' ') << node->id << "\n";
        printTree(node->left, depth + 1);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    // Copy constructor + assignment: deep copy ("fresh copy")
    BST(const BST& other) : root(clone(other.root)) {}
    BST& operator=(const BST& other) {
        if (this != &other) {
            destroy(root);
            root = clone(other.root);
        }
        return *this;
    }

    // Returns true if inserted, false if duplicate
    bool insert(int value) {
        bool inserted = false;
        root = insert(root, value, inserted);
        return inserted;
    }

    // Returns true if found. 'visits' = number of nodes examined.
    bool search(int value, int& visits) const {
        visits = 0;
        const BSTNode* cur = root;
        while (cur != nullptr) {
            visits++;
            if (value == cur->id) return true;
            cur = (value < cur->id) ? cur->left : cur->right;
        }
        return false;
    }

    // Returns true if the ID existed and was deleted
    bool remove(int value) {
        bool found = false;
        root = remove(root, value, found, true);
        return found;
    }

    void display() const {
        if (root == nullptr) { cout << "(tree is empty)\n"; return; }
        inorder(root);
        cout << endl;
    }

    // Sideways view of the tree (root on the left, right subtree on top)
    void showShape() const {
        if (root == nullptr) { cout << "(tree is empty)\n"; return; }
        printTree(root, 0);
    }
};

// ------------------------------------------------------------
// Helper: run and print one search
// ------------------------------------------------------------
void runSearch(const BST& tree, int id) {
    int visits = 0;
    bool found = tree.search(id, visits);
    cout << "  Search " << id << ": "
         << (found ? "FOUND" : "NOT FOUND")
         << "  (node visits = " << visits << ")\n";
}

// ============================================================
// MAIN
// ============================================================
int main() {
    // ---------------- PART A : general binary tree -----------
    cout << "========== PART A: General Binary Tree (Staff Names) ==========\n";
    StaffTree staff;
    staff.build();
    staff.displayRelations();
    cout << endl;
    staff.displayInorder();
    cout << "(Notice: this is NOT in alphabetical order.)\n\n";

    // ---------------- PART B : BST ---------------------------
    cout << "========== PART B: Binary Search Tree (Staff IDs) ==========\n";
    BST tree;
    int initial[] = {48, 28, 68, 18, 38, 58, 78};
    for (int id : initial) tree.insert(id);

    // Keep an untouched copy of the ORIGINAL BST for deletion tests
    const BST original(tree);

    cout << "Initial IDs inserted: 48 28 68 18 38 58 78\n";
    cout << "In-order: ";
    tree.display();
    cout << "Tree shape (rotate head left; root at left edge):\n";
    tree.showShape();

    // ---- Requirement 5: three additional IDs ----------------
    cout << "\n--- Insert three additional staff IDs ---\n";
    int added = 0;
    while (added < 3) {
        int id;
        if (!readInt("Enter additional staff ID (" + to_string(added + 1) + "/3): ", id)) {
            cout << "\nInput ended.\n";
            return 0;
        }
        if (tree.insert(id)) {
            cout << "  ID " << id << " inserted.\n";
            added++;
        } else {
            cout << "  ID " << id << " already exists -> REJECTED, tree not modified.\n";
        }
    }
    cout << "Current IDs (in-order): ";
    tree.display();

    // ---- Requirements 6 & 7: searching ----------------------
    cout << "\n--- Search tests (counting node visits) ---\n";
    cout << "Existing ID:\n";                  runSearch(tree, 38);
    cout << "Missing ID:\n";                   runSearch(tree, 99);
    cout << "ID smaller than all IDs:\n";      runSearch(tree, 5);

    int userSearch;
    if (readInt("\nEnter a staff ID to search: ", userSearch))
        runSearch(tree, userSearch);

    // ---- Requirement 8: deletion cases on FRESH copies ------
    cout << "\n--- Deletion tests (each on a fresh copy of the original BST) ---\n";
    cout << "Original BST (in-order): ";
    original.display();

    {
        cout << "\nTest 1: delete LEAF node 18\n";
        BST t(original);                   // fresh copy
        t.remove(18);
        cout << "  Result: "; t.display();
    }
    {
        cout << "\nTest 2: delete node with ONE child\n";
        cout << "  (Setup: insert 20 into the fresh copy so 18 has exactly one child)\n";
        BST t(original);                   // fresh copy
        t.insert(20);
        cout << "  Before: "; t.display();
        cout << "  Delete 18\n";
        t.remove(18);
        cout << "  Result: "; t.display();
    }
    {
        cout << "\nTest 3a: delete node with TWO children (28)\n";
        BST t(original);                   // fresh copy
        t.remove(28);
        cout << "  Result: "; t.display();
    }
    {
        cout << "\nTest 3b: delete ROOT with two children (48)\n";
        BST t(original);                   // fresh copy
        t.remove(48);
        cout << "  Result: "; t.display();
    }

    // ---- Requirement 8 (user-entered deletion) & 9 ----------
    cout << "\n--- Delete a staff ID entered by the user (on the working tree) ---\n";
    cout << "Before: "; tree.display();
    int delId;
    if (readInt("Enter staff ID to delete: ", delId)) {
        if (tree.remove(delId))
            cout << "  ID " << delId << " deleted.\n";
        else
            cout << "  ID " << delId << " not found -> tree unchanged.\n";
    }
    cout << "Remaining staff IDs in ascending order (in-order): ";
    tree.display();

    // ---- Requirement 10: explanation ------------------------
    cout << "\n========== Explanation ==========\n"
         << "A general binary tree has no rule that relates a node's value to the\n"
         << "values in its subtrees; nodes are linked wherever the programmer puts\n"
         << "them. In-order traversal (Left -> Root -> Right) only follows the\n"
         << "STRUCTURE, so the output order is arbitrary (see the staff names above).\n\n"
         << "A valid BST enforces: for EVERY node, all values in the left subtree are\n"
         << "smaller and all values in the right subtree are larger. In-order\n"
         << "traversal visits all smaller values first, then the node, then all\n"
         << "larger values, and applies this recursively at every node. Therefore\n"
         << "the output is always in ascending sorted order.\n";

    return 0;   // destructors free all dynamically allocated nodes
}
