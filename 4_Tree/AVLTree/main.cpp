/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 4, 2021, 5:55 PM
 */

#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include "AVLTree.h"


int main(int argc, char** argv) {

    std::cout << "---------------------------------------------\n";
    AVLTree<int> test1;
    test1.insert(14); test1.insert(6); test1.insert(24); test1.insert(35); 
    test1.insert(59); test1.insert(17); test1.insert(21); test1.insert(32); 
    test1.insert(4); test1.insert(7); test1.insert(15); test1.insert(22);
    /*
                                 17
                            /          \
                           14          24
                         /   \       /     \
                        6     15    21     35
                      /   \          \    / \
                    4      7         22  32  59
    */
    std::cout << "Preoreder: "; 
    test1.printPreorderTree();

    std::cout << "\n---------------------------------------------\n";

    test1.remove(17);
    /* remove 17:
                                 21
                            /          \
                           14          24
                         /   \       /     \
                        6     15    22     35
                      /   \                / \
                    4      7              32  59
    */
   test1.remove(21);
    /* remove 21:
                                 22
                            /          \
                           14          35
                         /   \       /     \
                        6     15    24     59
                      /   \           \     
                    4      7          32    
    */
   test1.remove(22);
    /* remove 21:
                                 24
                            /          \
                           14          35
                         /   \       /     \
                        6     15    32     59
                      /   \                
                    4      7              
    */
   test1.remove(24);
    /* remove 24:
                                 15
                            /          \
                           6           35
                         /   \       /     \
                        4     7     32     59
                               \            
                                14          
    */


    std::cout << "Preoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();


    std::cout << "\n---------------------------------------------\n";

    std::cout << "finish\n";


    return 0;
}

