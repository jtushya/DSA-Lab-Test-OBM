#include <iostream>
#include <fstream>
using namespace std;

struct Node {
    char letter;
    int freq;
    Node *left, *right;

    Node(char l, int f) : letter(l), freq(f), left(nullptr), right(nullptr) {}
    Node(int f, Node* l, Node* r) : letter(0), freq(f), left(l), right(r) {}
};

class MinHeap {
public:
    Node* heap[100]; // oversized for safety
    int size;

    MinHeap() : size(0) {}

    void push(Node* node) {
        int i = size++;
        while (i > 0 && node->freq < heap[(i - 1) / 2]->freq) {
            heap[i] = heap[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        heap[i] = node;
    }

    Node* pop() {
        if (size == 0) return nullptr;
        Node* minNode = heap[0];
        heap[0] = heap[--size];
        heapify(0);
        return minNode;
    }

    void heapify(int i) {
        int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < size && heap[left]->freq < heap[smallest]->freq) smallest = left;
        if (right < size && heap[right]->freq < heap[smallest]->freq) smallest = right;
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }
};

Node* buildHuffmanTree(int freq[26]) {
    MinHeap heap;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            heap.push(new Node('A' + i, freq[i]));
        }
    }

    while (heap.size > 1) {
        Node* right = heap.pop();
        Node* left = heap.pop();
        Node* parent = new Node(left->freq + right->freq, left, right);
        heap.push(parent);
    }

    return heap.pop(); // root of the tree
}

void generateCodes(Node* root, string* codes, string curr = "") {
    if (!root) return;

    if (!root->left && !root->right) {
        codes[root->letter - 'A'] = curr;
        return;
    }

    generateCodes(root->left, codes, curr + "0");
    generateCodes(root->right, codes, curr + "1");
}

int main() {
    // Step 1: Read file and count frequencies
    int freq[26] = {0};
    ifstream file("sample.txt");
    char c;
    while (file >> noskipws >> c) {
        if (c >= 'a' && c <= 'z') freq[c - 'a']++;
        else if (c >= 'A' && c <= 'Z') freq[c - 'A']++;
    }
    file.close();

    // Step 2: Build Huffman tree
    Node* root = buildHuffmanTree(freq);

    // Step 3: Generate Huffman codes
    string codes[26];
    generateCodes(root, codes);

    // Step 4: Print results
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            cout << (char)('A' + i) << ": " << codes[i] << '\n';
        }
    }

    return 0;
}
