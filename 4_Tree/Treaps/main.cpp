/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 19, 2021, 6:39 PM
 */

#include <cstdlib>
#include <iostream>
#include "Treap.h"


int main(int argc, char** argv) {

    Treap<int> test1;

    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert; 
        test1.insert(numrandinsert);
    }


    std::cout << "\nPreoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();

    std::cout <<"\n------------------------------------------------------\n";

    test1.remove(17035);
    std::cout << "remove 17035: ";
    std::cout << "\nPreoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();

    std::cout <<"\n------------------------------------------------------\n";

    test1.remove(3902);
    std::cout << "remove 3902: ";
    std::cout << "\nPreoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();



    return 0;
}

