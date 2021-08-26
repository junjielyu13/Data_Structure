/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 26, 2021, 6:18 PM
 */

#include <cstdlib>
#include <iostream>
#include "SkewHeap.h"

using namespace std;

int main(int argc, char** argv) {

    SkewHeap<int> test1;
    int numList1[] = {12,5,10};
    for(int i=0; i<3; i++){
        test1.insert(numList1[i]);
    }

    cout << "\npreorder: ";
    test1.printPreorderTree();
    cout << "\ninorder : ";
    test1.printInorderTree();


    cout <<"\n----------------------------------------------\n";

    SkewHeap<int> test2;
    int numList2[] = {3,7,8,14};
    for(int i=0; i<4; i++){
        test2.insert(numList2[i]);
    }

    cout << "\npreorder: ";
    test2.printPreorderTree();
    cout << "\ninorder : ";
    test2.printInorderTree();

    cout <<"\n----------------------------------------------\n";


    cout << "merge : ";
    test1.merge(test2);
    cout << "\npreorder: ";
    test1.printPreorderTree();
    cout << "\ninorder : ";
    test1.printInorderTree();

    cout <<"\n----------------------------------------------\n";

    while(!test1.isEmpty()){
        cout << test1.findMin() << " ";
        test1.deleteMin();
    }

    cout <<"\n----------------------------------------------\n";



    

    return 0;
}

