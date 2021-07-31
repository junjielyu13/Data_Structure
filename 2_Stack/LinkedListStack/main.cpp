/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on July 30, 2021, 8:57 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "LinkedListStack.h"

using namespace std;


int main(int argc, char** argv) {
        
    LinkedListStack<int> test1;
    test1.push(1); test1.push(2); test1.push(3);
    std::cout << "top: " << test1.top() << std::endl; 

    std::cout << "----------------------------------------------\n";


    LinkedListStack<int> test2(test1);
    test2.pop();
    std::cout << "size test1: "<< test1.size() << std::endl;
    std::cout << "size test2: "<< test2.size() << std::endl;

    std::cout << "----------------------------------------------\n";
    
    
    test1.push(4); test1.push(5);
    std::cout << "top test1: "<< test1.top() << std::endl;
    std::cout << "top test2: "<< test2.top() << std::endl;

    std::cout << "----------------------------------------------\n";

    while(!test1.empty()){
        std::cout << test1.top() << " ";
        test1.pop();
    }
    std::cout << std::endl;

    std::cout << "----------------------------------------------\n";


    std::cout << "size test1: "<< test1.size() << std::endl;
    std::cout << "size test2: "<< test2.size() << std::endl;

    std::cout << "----------------------------------------------\n";


    std::cout << "finish\n";

    return 0;
}

