/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 9, 2021, 7:56 PM
 */

#include <cstdlib>
#include <iostream>
#include "BinaryTree.h"


int main(int argc, char** argv) {

    BinaryTree<int> test1;
    test1.insert(100); test1.insert(50); test1.insert(150);
    test1.insert(25); test1.insert(75); test1.insert(125); test1.insert(175);
    test1.insert(15); test1.insert(35); test1.insert(65); test1.insert(85);
    test1.insert(115); test1.insert(135); test1.insert(165); test1.insert(185);
    test1.insert(0); test1.insert(30); test1.insert(60); test1.insert(120); test1.insert(160);
    /*
                                 100
                         /                 \
                        50                 150
                    /        \          /       \
                   25        75        125      175
                 /    \    /    \     /   \    /    \
                15    35  65    85   115  135 165   185
                /     /    /           \      /
                0    30   60           120   160
    */

    std::cout << "Depth-Frist Recursion: \n";

    std::cout << "Preoreder: "; 
    test1.printPreorderTreeRecursion();
    std::cout << "\nInoreder: "; 
    test1.printInorderTreeRecursion();
    std::cout << "\nPostoreder: "; 
    test1.printPostorderTreeRecursion();
    std::cout <<"\n------------------------------------------------------";

    std::cout << "\nDepth-Frist No Recursion: \n";
    
    std::cout << "Preoreder: "; 
    test1.printPreorderTreeNoRecursion();
    std::cout << "\nInoreder: "; 
    test1.printInorderTreeNoRecursion();
    std::cout << "\nPostoreder: "; 
    test1.printPostorderTreeNoRecursion();

    std::cout <<"\n------------------------------------------------------\n";
    
    std::cout << "Breadth-Frist: \n";
    std::cout << "level order traversal: ";
    test1.printBreadthFirstTraversal();

    std::cout <<"\n------------------------------------------------------\n";
    std::cout <<"finish\n";
    


    return 0;
}

