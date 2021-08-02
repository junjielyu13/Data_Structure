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
#include "CircularLinkedList.h"

using namespace std;


int main(int argc, char** argv) {

    CircularLinkedList<int> test1;
    test1.push(1); test1.push(2); test1.push(3); test1.push(4);
    std::cout << "front: "<< test1.front() << std::endl;
    std::cout << "back: "<< test1.back() << std::endl;

    std::cout << "-----------------------------------------------\n";

    CircularLinkedList<int> test2(test1);
    test2.pop();
    std::cout << "test1 back: " << test1.back() << " ,size : "<< test1.size() <<std::endl;
    std::cout << "test2 back: " << test2.back() << " ,size : "<< test2.size() <<std::endl;

    std::cout << "-----------------------------------------------\n";


    while (!test1.empty()){
        std::cout << test1.back() << " ";
        test1.pop();
    }
    std::cout << std::endl;

    return 0;
}

