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
                      4    7         22  32  59
    */


    return 0;
}

