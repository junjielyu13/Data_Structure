/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 25, 2021, 10:10 PM
 */

#include <cstdlib>
#include <iostream>
#include "LeftistHeap.h"

using namespace std;

int main(int argc, char** argv) {

    LeftistHeap<int> test1;
    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl; 
        test1.insert(numrandinsert);
    }

    cout << "\npreorder: ";
    test1.printPreorderTree();
    cout << "\ninorder : ";
    test1.printInorderTree();

    LeftistHeap<int> test2;
    
    cout <<"\n----------------------------------------------\n";

    
    test2.makeEmpty();
    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl; 
        test2.insert(numrandinsert);
    }

    test1.merge(test2);
    cout << "\npreorder: ";
    test1.printPreorderTree();
    cout << "\ninorder : ";
    test1.printInorderTree();

    cout <<"\n----------------------------------------------\n";


    cout << "merge: " << endl;
    while(!test1.isEmpty()){
        cout << test1.findMin() << " ";
        test1.deleteMin();
    }

    cout <<"\n----------------------------------------------\n";


    return 0;
}

