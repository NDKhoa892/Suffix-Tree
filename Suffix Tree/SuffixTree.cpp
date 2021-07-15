//
//  SuffixTree.cpp
//  Suffix Tree
//
//  Created by Harry Nguyen on 14/07/2021.
//

#include "SuffixTree.h"

// Suffix Tree :: Node

SuffixTree::Node::Node(Node* root, int start, int* end) {
    for (int i = 0; i < MAX_CHAR; ++i)
        children[i] = nullptr;
    
    suffixLink = root;
    
    this -> start = start;
    this -> end = end;
    
    suffixIndex = -1;
}

SuffixTree::Node::~Node() {
    for (int i = 0; i < MAX_CHAR; ++i)
        if (children[i] != nullptr)
            delete children[i];
    
    if (suffixIndex == -1) delete end;
}

int SuffixTree::Node::getEdgeLength() {
    return *end - start + 1;
}

// Suffix Tree

SuffixTree::SuffixTree(string text) {
    this -> text = text;
    
    root = new Node(nullptr, -1, new int(-1));
    
    lastNewNode = nullptr;
    
    activeNode = root;
    activeCharIndex = -1;
    activeLength = 0;
    
    remainingSuffixCount = 0;
    
    leafEnd = -1;
    size = int(text.size());
    
    for (int i = 0; i < size; ++i)
        extendSuffixTree(i);
    
    setSuffixIndexByDFS(root, 0);
}

SuffixTree::~SuffixTree() {
    if (root) delete root;
}

bool SuffixTree::walkDown(Node* curNode) {
    // APCFWD
    if (activeLength >= curNode -> getEdgeLength()) {
        activeCharIndex += curNode -> getEdgeLength();
        activeLength -= curNode -> getEdgeLength();
        activeNode = curNode;
        
        return true;
    }
    
    return false;
}

void SuffixTree::extendSuffixTree(int pos) {
    leafEnd = pos;
    
    ++remainingSuffixCount;
    
    lastNewNode = nullptr;
    
    while (remainingSuffixCount > 0) {
        // APCFALZ
        if (activeLength == 0)
            activeCharIndex = pos;

        int activeEdge = text[activeCharIndex] - ' ';
        
        if (activeNode -> children[activeEdge] == nullptr) {
            // Extension Rule 2 (A new leaf edge gets created)
            activeNode -> children[activeEdge] = new Node(root, pos, &leafEnd);
            
            if (lastNewNode != nullptr) {
                lastNewNode -> suffixLink = activeNode;
                lastNewNode = nullptr;
            }
        } else {
            Node* next = activeNode -> children[activeEdge];
            
            if (walkDown(next)) continue;
            
            // Extension Rule 3 (Current character is already on the edge)
            if (text[next -> start + activeLength] == text[pos]) {
                if (lastNewNode != nullptr && activeNode != root) {
                    lastNewNode -> suffixLink = activeNode;
                    lastNewNode = nullptr;
                }
                
                // APCFER3
                ++activeLength;
                
                break;
            }
            
            // Extension Rule 2 (A new leaf edge and a new internal node get created)
            int* splitEnd = new int(next -> start + activeLength - 1);
            
            Node* split = new Node(root, next -> start, splitEnd);
            activeNode -> children[activeEdge] = split;
            
            split -> children[text[pos] - ' '] = new Node(root, pos, &leafEnd);
            next -> start += activeLength;
            split -> children[text[next -> start] - ' '] = next;
            
            if (lastNewNode != nullptr)
                lastNewNode -> suffixLink = split;
            
            lastNewNode = split;
        }
        
        --remainingSuffixCount;
        
        if (activeNode == root && activeLength > 0) {   // APCFER2C1
            --activeLength;
            activeEdge = text[pos - remainingSuffixCount + 1] - ' ';
        } else if (activeNode != root)                  // APCFER2C2
            activeNode = activeNode -> suffixLink;
    }
}

void SuffixTree::printSubText(int i, int j) {
    for ( ; i <= j; ++i)
        cout << text[i];
}

void SuffixTree::setSuffixIndexByDFS(Node* node, int labelHeight) {
    if (node == nullptr) return;
    
    bool leaf = true;
    
    for (int i = 0; i < MAX_CHAR; ++i)
        if (node -> children[i] != nullptr) {
            leaf = false;
            
            setSuffixIndexByDFS(node -> children[i], labelHeight + node -> children[i] -> getEdgeLength());
        }
    
    if (leaf)
        node -> suffixIndex = size - labelHeight;
}

void SuffixTree::print(Node* node) {
    if (!node) return;
    
    if (node -> start != -1) {
        printSubText(node -> start, *(node -> end));
        cout << ' ' << node -> suffixIndex << '\n';
    }
    
    for (int i = 0; i < MAX_CHAR; ++i)
        if (node -> children[i] != nullptr)
            print(node -> children[i]);
}

void SuffixTree::print() {
    print(root);
}
