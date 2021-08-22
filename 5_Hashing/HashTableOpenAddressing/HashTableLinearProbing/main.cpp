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
#include "HashTableLinearProbing.h"
using namespace std;

int main(int argc, char** argv) {

    HashTableLinearProbing<int> test1(12);
    int numlist[] = {18, 41, 22, 44, 59, 32, 31, 73};

    for(int i=0; i<8; i++){
        test1.insert(numlist[i]);
    }
    test1.printArray();

    return 0;
}

