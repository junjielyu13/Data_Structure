/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 26, 2021, 7:08 PM
 */

#include <cstdlib>
#include <iostream>
#include "BinomialQueue.h"

using namespace std;


int main(int argc, char** argv) {

    BinomialQueue<int> test1;
    for(int i=1; i<8; i++){
        test1.insert(i);
    }

    BinomialQueue<int> test2(test1);

    while(!test1.isEmpty()){
        cout << test1.findMin() << " ";
        test1.deleteMin();
    }
    cout << "\n---------------------------------------------------\n";

    BinomialQueue<int> test3;
    int numList[] = {14,16,18,21,24,26,65};
    for(int i=0; i<7; i++){
        test3.insert(numList[i]);
    }


    cout << "merge: ";
    test3.merge(test2);
    while(!test3.isEmpty()){
        cout << test3.findMin() << " ";
        test3.deleteMin();
    }
    cout << "\nfnish"<<endl;
    
    return 0;
}

