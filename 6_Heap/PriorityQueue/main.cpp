/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 27, 2021, 4:40 PM
 */

#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "PriorityQueue.h"

using namespace std;


int main(int argc, char** argv) {

    PriorityQueue<int> test1;
    int numlist[] = {13,21,16,24,31,19,68,65,26,32};
    for(int i=0; i<10; i++){
        test1.push(numlist[i]);
    }

    PriorityQueue<int> test2(test1);

    while(!test1.empty()){
        cout << test1.top() << " ";
        test1.pop();
    }

    cout << "\n---------------------------------------------------\n";
    test2.push(14);
    while(!test2.empty()){
        cout << test2.top() << " ";
        test2.pop();
    }

    cout << "\n---------------------------------------------------\n";
    vector<int> list;
    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl; 
        list.push_back(numrandinsert);
    }
    
    PriorityQueue<int> test6(list);

    cout << endl;
    while(!test6.empty()){
        cout << test6.top()<< " ";
        test6.pop();
    }


    cout << "\nfinish";


    return 0;
}

