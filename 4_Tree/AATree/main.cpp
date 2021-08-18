/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 18, 2021, 6:01 PM
 */

#include <cstdlib>
#include <iostream>
#include "AATree.h"


int main(int argc, char** argv) {
    
    AATree<int> test1;
    test1.insert(10);test1.insert(85);test1.insert(15);test1.insert(70);test1.insert(20);
    test1.insert(60);test1.insert(30);test1.insert(50);test1.insert(65);test1.insert(80);
    test1.insert(90);test1.insert(40);test1.insert(5);test1.insert(55);test1.insert(35);
    

    std::cout << "Preoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();

    std::cout <<"\n------------------------------------------------------\n";
    test1.insert(45);

    std::cout << "Preoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();

    std::cout << "\nheight: "<< test1.height() << std::endl;

    std::cout <<"\n------------------------------------------------------\n";
    test1.remove(40);
    std::cout << "Preoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();




    return 0;
}

