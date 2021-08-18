/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 14, 2021, 1:51 AM
 */

#include <cstdlib>
#include <iostream>
#include "BTree.h"


int main(int argc, char** argv) {

    BTree<int> t(3);
    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    std::cout << "Traversal of the constructed tree is ";
    t.traverse();


    return 0;
}

