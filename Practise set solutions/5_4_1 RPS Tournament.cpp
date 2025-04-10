#include <iostream>
using namespace std;

class Node {
public:
    int idx;        // Player index (1-based)
    char move;      // 'R', 'P', or 'S'
    Node* left, *right;
    Node() : idx(-1), move(0), left(nullptr), right(nullptr) {}
};

// Function to build the binary tree recursively
Node* blankTree(int k, int idx, string s) {
    Node* node = new Node();
    if (k == 0) {
        node->idx = idx + 1;
        node->move = s[idx];
        return node;
    }
    node->left = blankTree(k - 1, (idx * 2), s);
    node->right = blankTree(k - 1, (idx * 2) + 1, s);
    return node;
}

// Helper to determine winner based on Rock-Paper-Scissors rules
Node* getWinner(Node* a, Node* b) {
    char A = a->move, B = b->move;

    // Match result print
    cout << a->idx << " vs " << b->idx << "\n";
    cout << a->idx << " picks " << A << "\n";
    cout << b->idx << " picks " << B << "\n";

    // RPS logic
    if ((A == 'R' && B == 'S') ||
        (A == 'S' && B == 'P') ||
        (A == 'P' && B == 'R') ||
        (A == B)) {
        // A wins or tie
        cout << a->idx << " wins!\n\n";
        return a;
    } else {
        // B wins
        cout << b->idx << " wins!\n\n";
        return b;
    }
}

// Function to simulate the tournament from the leaves up
void simulateTournament(Node* tree) {
    if (!tree->left || !tree->right) return;

    simulateTournament(tree->left);
    simulateTournament(tree->right);

    Node* winner = getWinner(tree->left, tree->right);
    tree->idx = winner->idx;
    tree->move = winner->move;
}

int main() {
    int k, n = 1;
    cin >> k;

    // Compute 2^k
    for (int i = 0; i < k; i++) n *= 2;

    string moves;
    cin >> moves;

    Node* tree = blankTree(k, 0, moves);
    simulateTournament(tree);

    cout << tree->idx << " wins the tournament!\n";
    return 0;
}
