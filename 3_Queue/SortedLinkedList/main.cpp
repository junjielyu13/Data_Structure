/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on July 31, 2021, 11:34 PM
 */

#include <cstdlib>
#include <iostream>
#include "SortedLinkedList.h"

using namespace std;


int main(int argc, char** argv) {

    SortedLinkedList<int> test1;
    test1.add(30); test1.add(20); test1.add(50); test1.add(40);
    test1.add(25); test1.add(35); test1.add(45);
    for(int i : test1){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for( SortedLinkedList<int> ::iterator itr=test1.begin(); itr!=test1.end(); itr++){
        std::cout << *itr << " ";
    }
    std::cout << std::endl;

    
    std::cout << "---------------------------------------------\n";


    std::cout << "front: " <<test1.front() <<std::endl;
    std::cout << "back: "  <<test1.back() <<std::endl;

    std::cout << "---------------------------------------------\n";



    std::cout << "finsh" << std::endl;

    return 0;
}

