/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 24, 2021, 8:42 PM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "MaximumBinaryHeap.h"

using namespace std;

int main(int argc, char** argv) {

    MaximumBinaryHeap<int> test1;
    int numlist[] = {13,21,16,24,31,19,68,65,26,32};
    for(int i=0; i<10; i++){
        test1.insert(numlist[i]);
    }

    MaximumBinaryHeap<int> test2(test1);

    while(!test1.isEmpty()){
        cout << test1.findMax() << " ";
        test1.deleteMax();
    }

    cout << "\n---------------------------------------------------\n";
    test2.insert(14);
    while(!test2.isEmpty()){
        cout << test2.findMax() << " ";
        test2.deleteMax();
    }

    cout << "\n---------------------------------------------------\n";
    vector<int> list;
    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl; 
        list.push_back(numrandinsert);
    }
    
    MaximumBinaryHeap<int> test6(list);
    test6.print();
    cout << endl;
    while(!test6.isEmpty()){
        cout << test6.findMax()<< " ";
        test6.deleteMax();
    }


    cout << "\nfinish";


    return 0;
}

