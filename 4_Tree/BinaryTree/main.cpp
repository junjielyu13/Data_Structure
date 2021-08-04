/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 3, 2021, 5:11 PM
 */

#include <cstdlib>
#include <iostream>
#include "BinaryTree.h"
                                                                                                                                                                                                                                                                                                                                                          
int main(int argc, char** argv) {

    std::cout << "---------------------------------------------\n";

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
    std::cout << "size : " << test1.size() << std::endl;
    std::cout << "height : " << test1.height() << std::endl;
    std::cout << "depth : " << test1.depth() << std::endl;
    std::cout << "Preoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();
    std::cout << "\nPostoreder: "; 
    test1.printPostorderTree();
    std::cout << "\nfind max: " << test1.findMax() << std::endl;
    std::cout << "find min: " << test1.findMin() << std::endl;

    std::cout << "---------------------------------------------\n";

    BinaryTree<int> test2(test1);
    std::cout << "copy test2\n";
    test2.remove(0);  test2.remove(185); test2.remove(100);;
    /*
                                 115
                         /                 \
                        50                 150
                    /        \          /       \
                   25        75        125      175
                 /    \    /    \     /   \    /    
                15    35  65    85   120   135 165  
                      /   /                    /
                     30  60                  160
    */
    std::cout << "size : " << test2.size() << std::endl;
    std::cout << "height : " << test2.height() << std::endl;
    std::cout << "depth : " << test2.depth() << std::endl;
    std::cout << "find max: " << test2.findMax() << std::endl;
    std::cout << "find min: " << test2.findMin() << std::endl;
    std::cout << "Preoreder: "; 
    test2.printPreorderTree();

    std::cout << "\n---------------------------------------------\n";

    if(test2.contains(150)){
        std::cout << "contains!"<<std::endl;
    }
    test2.makeEmpty();
    if(!test2.contains(150)){
        std::cout << "No contains!"<<std::endl;
    }

    std::cout << "---------------------------------------------\n";

    std::cout << "finish!";

    

    return 0;
}

