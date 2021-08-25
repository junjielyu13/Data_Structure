/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 24, 2021, 9:41 PM
 */

#include <cstdlib>
#include <iostream>
#include "dHeap.h"

using namespace std;


int main(int argc, char** argv) {
    
    dHeap<int> test1(3);
    int numlist[] = {1,2,3,5,4,7,10,13,15,6,8,17,9,11,9};

    for(int i=0; i<15; i++){
        test1.insert(numlist[i]);
    }
    
    dHeap<int> test2(test1);
    test1.print();

    cout << "\n---------------------------------------------------\n";

    while(!test1.isEmpty()){
        cout << test1.findMin()<< " ";
        test1.deleteMin();
    }

    cout << "\n---------------------------------------------------\n";
    
    test2.insert(0);
    test2.print();

    cout << "\n---------------------------------------------------\n";

    while(!test2.isEmpty()){
        cout << test2.findMin()<< " ";
        test2.deleteMin();
    }

    cout << "\n---------------------------------------------------\n";
    

    cout << "n = 4\n";
    dHeap<int> test4(4);

    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl; 
        test4.insert(numrandinsert);
    }
    test4.print();
    cout << endl;
    while(!test4.isEmpty()){
        cout << test4.findMin()<< " ";
        test4.deleteMin();
    }


    cout << "\n---------------------------------------------------\n";
    

    cout << "n = 5\n";
    dHeap<int> test5(5);

    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl; 
        test5.insert(numrandinsert);
    }
    test5.print();
    cout << endl;
    while(!test5.isEmpty()){
        cout << test5.findMin()<< " ";
        test5.deleteMin();
    }



    return 0;
}

