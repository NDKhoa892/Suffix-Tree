//
//  SuffixTree.h
//  Suffix Tree
//
//  Created by Harry Nguyen on 14/07/2021.
//

#ifndef SuffixTree_h
#define SuffixTree_h

#include <iostream>
#include <string>

using namespace std;

const int MAX_CHAR = 256;

class SuffixTree {
private:
    
    struct Node {
        
        Node* children[MAX_CHAR];
        Node* suffixLink;
        
        int start;
        int* end;
        
        int suffixIndex;
        
        Node(Node* root, int start, int* end);
        ~Node();
        
        int getEdgeLength();
        
    };
    
    string text;
    
    Node* root;
    
    Node* lastNewNode;
    
    Node* activeNode;
    int activeCharIndex;
    int activeLength;
    
    int remainingSuffixCount;
    
    int leafEnd;
    int size;
    
    bool walkDown(Node* curNode);
    
    void extendSuffixTree(int pos);
    
    void printSubText(int i, int j);
    
    void setSuffixIndexByDFS(Node* node, int labelHeight);
    
    void print(Node* node);
    
public:
    
    SuffixTree(string text);
    ~SuffixTree();
    
    void print();
    
};

#endif /* SuffixTree_h */
