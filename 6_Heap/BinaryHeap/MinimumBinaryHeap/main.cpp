/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 24, 2021, 8:41 PM
 */

#include <cstdlib>
#include <iostream>
#include "MinimumBinaryHeap.h"

using namespace std;


int main(int argc, char** argv) {

    MinimumBinaryHeap<int> test1;
    int numlist[] = {13,21,16,24,31,19,68,65,26,32};
    for(int i=0; i<10; i++){
        test1.insert(numlist[i]);
    }

    MinimumBinaryHeap<int> test2(test1);

    while(!test1.isEmpty()){
        cout << test1.findMin() << " ";
        test1.deleteMin();
    }

    cout << "\n---------------------------------------------------\n";
    test2.insert(14);
    while(!test2.isEmpty()){
        cout << test2.findMin() << " ";
        test2.deleteMin();
    }

    cout << "\nfinish";


    return 0;
}

