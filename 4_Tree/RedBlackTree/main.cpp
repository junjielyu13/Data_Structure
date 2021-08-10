/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 9, 2021, 10:13 PM
 */

#include <cstdlib>
#include <iostream>
#include "RedBlackTree.h"


int main(int argc, char** argv) {
    
    RedBlackTree<int> test1;
    for(int i=1; i<11; i++){
        test1.insert(i);
    }
    std::cout << "Preorder: ";
    test1.printPreorderTree();
    std::cout << "\nInorder: ";
    test1.printInorderTree();
    std::cout << "\n --------------------------------------------------------\n";
    std::cout << "finish";
    return 0;
}

