/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 27, 2021, 5:12 PM
 */

#include <cstdlib>
#include <iostream>
#include "PairingHeap.h"

using namespace std;


int main(int argc, char** argv) {

    PairingHeap<int> test1;
    for(int i=0; i<20; i++){
        test1.insert(rand());
    }

    PairingHeap<int> test3(test1);


    PairingHeap<int> test2;

    for(int i=0; i<20; i++){
        test2.insert(rand());
    }

    test1.merge(test2);

    while (!test1.isEmpty()){
        cout << test1.findMin() << " ";
        test1.deleteMin();
    }

    cout << "\n------------------------------------------------------------\n";

    

    return 0;
}

