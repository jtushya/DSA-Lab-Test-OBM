#include <iostream>
#include <climits>
using namespace std;

class Node {
public:
    int subtreeSize;
    Node* child, *sibling;
    Node() : subtreeSize(0), child(nullptr), sibling(nullptr) {}
};

int N;
int minTotalDist = INT_MAX;
int* totalDistArr;

void treeFromInput(Node** tree, int n) {
    for (int i = 0; i < n; i++) tree[i] = new Node();
    for (int i = 1; i < n; i++) {
        int parent;
        cin >> parent;
        parent--;
        if (tree[parent]->child != nullptr)
            tree[i]->sibling = tree[parent]->child;
        tree[parent]->child = tree[i];
    }
}
//codefill1
void calcSubtreeSizes(Node* node) {
    node->subtreeSize = 1;
    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        calcSubtreeSizes(c);
        node->subtreeSize += c->subtreeSize;
    }
}

//codefill2

// Calculate total delivery cost from the root node
int calcTotalDist(Node* node, int depth = 0) {
    int total = depth;
    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        total += calcTotalDist(c, depth + 1);
    }
    return total;
}

//codefill3 - task2 creation - recursive function to calculate total delivery cost
// Rerooting DP: calculate total delivery cost for all nodes
void reroot(Node* node, int totalDist) {
    // Update minimum delivery cost
    minTotalDist = min(minTotalDist, totalDist);

    for (Node* c = node->child; c != nullptr; c = c->sibling) {
        int distFromChild = totalDist - c->subtreeSize + (N - c->subtreeSize);
        reroot(c, distFromChild);
    }
}

int main() {
    cin >> N;
    Node** tree = new Node*[N];
    treeFromInput(tree, N);

    calcSubtreeSizes(tree[0]);                      // Step 1
    int baseTotalDist = calcTotalDist(tree[0]);     // Step 2
    reroot(tree[0], baseTotalDist);                 // Step 3

    cout << "Minimum total delivery cost: " << minTotalDist << '\n';

    delete[] tree;
    return 0;
}
