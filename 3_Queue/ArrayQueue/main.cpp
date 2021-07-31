/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on July 31, 2021, 10:06 PM
 */

#include <cstdlib>
#include <iostream>
#include "ArrayQueue.h"

using namespace std;


int main(int argc, char** argv) {

    ArrayQueue<int> test1;
    test1.push(1); test1.push(2); test1.push(3);
    std::cout << "front: " << test1.front() << std::endl; 
    std::cout << "back: " << test1.back() << std::endl; 

    std::cout << "----------------------------------------------\n";


    ArrayQueue<int> test2(test1);
    test2.pop();
    std::cout << "size test1: " << test1.size() << std::endl; 
    std::cout << "size test2: " << test2.size() << std::endl; 

    std::cout << "----------------------------------------------\n";


    test1.push(4); test1.push(5);
    while(!test1.empty()){
        std::cout << test1.back() << " ";
        test1.pop();
    }

    std::cout << std::endl;

    std::cout << "size test1: " << test1.size() << std::endl; 
    std::cout << "size test2: " << test2.size() << std::endl;


    return 0;
}

