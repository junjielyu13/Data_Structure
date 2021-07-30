


/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on July 30, 2021, 8:57 PM
 */

#include <cstdlib>
#include <iostream>
#include "Stack.h"

/*
 * 
 */

int main(int argc, char** argv) {

    Stack<int> test1;

    try{

        test1.push(1); test1.push(2); test1.push(3); test1.push(4);
        std::cout << "top: "<< test1.top() << std::endl;

        std::cout << "---------------------------------------------\n";
    

        Stack<int> test2(test1);
        test2.pop();
        std::cout << "size test1: "<< test1.size() << std::endl;
        std::cout << "size test2: "<< test2.size() << std::endl;
        
        std::cout << "---------------------------------------------\n";

        test2.pop(); test2.pop(); test2.pop(); 
        if(test2.empty()){
            std::cout << "stack empty"<< std::endl;
        }
        test2.pop();


    }catch(const std::exception &e){
        std::cerr << e.what() << '\n';
    }
    
    

    return 0;
}

