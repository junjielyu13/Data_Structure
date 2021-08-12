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
    
    RedBlackTree<int> test2;
    test2.insert(2); test2.insert(10); test2.insert(6); test2.insert(7);
    test2.insert(8); test2.insert(9); test2.insert(5); test2.insert(1);
    test2.insert(3); test2.insert(4);

    std::cout << "Preorder: ";
    test2.printPreorderTree();
    std::cout << "\nInorder: ";
    test2.printInorderTree();
    std::cout << "\n --------------------------------------------------------\n";

    test2.remove(10);
    std::cout << "remove 10: \n";
    std::cout << "Preorder: ";
    test2.printPreorderTree();
    std::cout << "\nInorder: ";
    test2.printInorderTree();
    std::cout << "\n --------------------------------------------------------\n";

    //RedBlackTree<int> test3(test2);

    std::cout << "finish";
    return 0;
}

