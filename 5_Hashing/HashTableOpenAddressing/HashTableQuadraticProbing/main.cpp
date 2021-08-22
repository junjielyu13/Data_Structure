/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 22, 2021, 6:01 PM
 */

#include <cstdlib>
#include <iostream>
#include "HashTableQuadraticProbing.h"

using namespace std;

int main(int argc, char** argv) {

    HashTableQuadraticProbing<int>test1(17);
    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl;
        test1.insert(numrandinsert);
    }
    test1.printArray();
    cout << "\n----------------------------------------------------------------------\n";


    HashTableQuadraticProbing<int>test2(test1);
    test1.remove(41);
    test1.remove(24464);
    test1.printArray();

    cout << "\n----------------------------------------------------------------------\n";

    test2.printArray();
    cout << "\n finish \n";
    
    // HashTableQuadraticProbing<int> test1(16);
    // int numlist[] = {5,8,10,8,5,11,6,7,3};
    // for(int i=0; i<9; i++){
    //     test1.insert(numlist[i]);
    // }
    // test1.printArray();


    return 0;
}

