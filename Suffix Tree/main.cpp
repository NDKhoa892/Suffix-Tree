//
//  main.cpp
//  Suffix Tree
//
//  Created by Harry Nguyen on 14/07/2021.
//

#include "SuffixTree.h"

int main() {
    string text;
    cout << "Enter text: ";
    cin >> text;
    
    SuffixTree* suffixTree = new SuffixTree(text);
    
    suffixTree -> print();
    
    delete suffixTree;
}
