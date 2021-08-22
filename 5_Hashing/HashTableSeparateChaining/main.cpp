/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 22, 2021, 11:31 AM
 */

#include <cstdlib>
#include "HashTableSeparateChaining.h"
using namespace std;

int main(int argc, char** argv) {

    HashTableSeparateChaining<int> test1(17);
    
    for(int i=0; i<20; i++){
        int numrandinsert  = rand();
        std::cout << "numrandinsert = " << numrandinsert << endl;
        test1.insert(numrandinsert);
    }

    test1.insert(21);
    test1.insert(22);
    if(test1.contains(21) && test1.contains(22)){
        cout << "find"<< endl;
    }else{
        cout << "can't find"<< endl;
    }

    cout << "------------------------------------------------------------"<< endl;

    HashTableSeparateChaining<int>test2(test1);

    test1.remove(21);
    test1.remove(22);

    if(test1.contains(22)&&test1.contains(21)){
        cout << "find"<< endl;
    }else{
        cout << "can't find"<< endl;
    }

    cout << "------------------------------------------------------------"<< endl;

    if(test2.contains(22)&&test2.contains(21)){
        cout << "find"<< endl;
    }else{
        cout << "can't find"<< endl;
    }
    
    return 0;
}

