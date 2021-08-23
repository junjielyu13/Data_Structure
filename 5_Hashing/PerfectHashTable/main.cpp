/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 23, 2021, 1:08 AM
 */

#include <cstdlib>
#include <iostream>
#include "PerfectHashTable.h"

using namespace std;


int main(int argc, char** argv) {

    PerfectHashTable<int> test1(8);
    int numlist[] = {10, 22, 37, 40, 52, 60, 70, 72, 75};
    for(int i=0; i<9; i++){
        test1.insert(numlist[i]);
    }
    test1.printArray();

    cout << "\n--------------------------------------------------------------------------------------\n";

    PerfectHashTable<int> test2(test1);
    test1.remove(10);
    test2.printArray();

    return 0;
}

