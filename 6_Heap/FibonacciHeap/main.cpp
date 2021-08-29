/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 27, 2021, 5:10 PM
 */

#include <cstdlib>
#include <iostream>
#include "FibonacciHeap.h"

using namespace std;

int main(int argc, char** argv) {

    FibonacciHeap<int> test1;
    test1.Insert(5);
    test1.Insert(2);
    test1.Insert(8);

    FibonacciHeap<int> test2;
    test2.Insert(7);
    test2.Insert(1);
    test2.Insert(3);

    test1.Union(test2);


    while(!test1.isEmpty()){
        cout << test1.findMin() << " ";
        test1.Extract_Min();
    }

    cout << "\n-------------------------------------------------\n";

    return 0;
}

