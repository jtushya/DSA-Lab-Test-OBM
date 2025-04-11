#include <iostream>
using namespace std;

// Node to represent a letter and its frequency
struct Node {
    char letter;  // The character (letter) being represented
    int freq;     // The frequency of the character
    Node* left;   // Left child in the tree
    Node* right;  // Right child in the tree

    // Constructor
    Node(char l, int f) : letter(l), freq(f), left(nullptr), right(nullptr) {}
};

// MinHeap class to manage the priority queue of nodes
class MinHeap {
public:
    Node* heap[26];  // Array of nodes to store the min-heap
    int size;        // Current size of the heap

    MinHeap() : size(0) {}

    // Push a node to the heap
    void push(Node* node) {
        int i = size++;
        while (i > 0 && node->freq < heap[(i - 1) / 2]->freq) {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        heap[i] = node;
    }

    // Pop the node with the minimum frequency from the heap
    Node* pop() {
        if (size == 0) return nullptr;
        Node* minNode = heap[0];
        heap[0] = heap[--size];
        heapify(0);
        return minNode;
    }

    // Heapify to maintain the min-heap property
    void heapify(int i) {
        int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < size && heap[left]->freq < heap[smallest]->freq)
            smallest = left;
        if (right < size && heap[right]->freq < heap[smallest]->freq)
            smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
};

// Function to build the Huffman Tree
Node* buildHuffmanTree(int freq[26]) {
    MinHeap minHeap;

    // Create a node for each letter and push it to the heap
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {  // Only add nodes with non-zero frequency
            Node* node = new Node('A' + i, freq[i]);
            minHeap.push(node);
        }
    }

    // Build the Huffman tree by combining the two least frequent nodes
    while (minHeap.size > 1) {
        // Pop two nodes with the lowest frequencies
        Node* right = minHeap.pop();
        Node* left = minHeap.pop();

        // Create a new internal node with the combined frequency
        Node* internalNode = new Node('\0', left->freq + right->freq);
        internalNode->left = left;
        internalNode->right = right;

        // Push the internal node back into the heap
        minHeap.push(internalNode);
    }

    // The last remaining node is the root of the Huffman tree
    return minHeap.pop();
}

// Function to generate the Huffman codes from the tree
void generateCodes(Node* root, string* codes, string curr = "") {
    // If it's a leaf node, store the code for the letter
    if (root->left == nullptr && root->right == nullptr) {
        codes[root->letter - 'A'] = curr;
        return;
    }

    // Traverse the left and right subtrees
    if (root->left) generateCodes(root->left, codes, curr + "0");
    if (root->right) generateCodes(root->right, codes, curr + "1");
}

int main() {
    // Frequency of each letter (example input)
    int freq[26] = {117, 44, 52, 32, 28, 40, 16, 42, 73, 5,
                    9, 24, 38, 23, 76, 43, 2, 28, 67, 160, 12, 8, 
                    55, 0, 7, 0};

    // Build the Huffman tree
    Node* root = buildHuffmanTree(freq);

    // Array to store the Huffman codes for each letter
    string codes[26];

    // Generate the Huffman codes
    generateCodes(root, codes);

    // Output the Huffman codes for each letter
    for (int i = 0; i < 26; i++) {
        if (codes[i] != "") {
            cout << (char)('A' + i) << ": " << codes[i] << endl;
        }
    }

    return 0;
}
