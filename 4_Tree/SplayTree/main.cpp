/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 5, 2021, 6:46 PM
 */

#include <cstdlib>
#include <iostream>
#include "SplayTree.h"


int main(int argc, char** argv) {

    SplayTree<int> test1;
    int list[] = {100, 0, 200, 50, 150, 25, 75, 125, 175};
    for(int i=0; i<9; i++){
        std::cout << "insert: "<< list[i] <<std::endl;
        test1.insert(list[i]);
        std::cout << "Preorder:";
        test1.printPreorderTree();
        std::cout << "\nInorder:";
        test1.printInorderTree();
        std::cout <<"\n----------------------------------------\n";
    }
    std::cout << "Find min: "<< test1.findMin() << std::endl;
    std::cout << "Preorder:";
    test1.printPreorderTree();
    std::cout << "\nInorder:";
    test1.printInorderTree();
    std::cout <<"\n----------------------------------------\n";


    std::cout << "Find max: "<< test1.findMax() << std::endl;
    std::cout << "Preorder:";
    test1.printPreorderTree();
    std::cout << "\nInorder:";
    test1.printInorderTree();
    std::cout <<"\n----------------------------------------\n";


    std::cout << "Contains 100 "<< test1.contains(100) << std::endl;
    std::cout << "Preorder:";
    test1.printPreorderTree();
    std::cout << "\nInorder:";
    test1.printInorderTree();
    std::cout <<"\n----------------------------------------\n";


    std::cout << "remove 100 \n";
    test1.remove(100);
    std::cout << "Preorder:";
    test1.printPreorderTree();
    std::cout << "\nInorder:";
    test1.printInorderTree();
    std::cout <<"\n----------------------------------------\n";
    
    
    std::cout << "\nfinish"<<std::endl;

    return 0;
}

