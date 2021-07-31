/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on July 31, 2021, 12:48 AM
 */

#include <cstdlib>
#include <iostream>
#include "DoublyLinkedList.h"


int main(int argc, char** argv) {

    DoublyLinkedList<int> test1;

    test1.push_back(1);  test1.push_back(2); test1.push_front(99);
    for(DoublyLinkedList<int> ::iterator itr=test1.begin(); itr!=test1.end(); itr++){
        std::cout << *itr << " ";
    }
    std::cout << std::endl;

    std::cout << "---------------------------------------------\n";


    std::cout << "front: " <<test1.front() <<std::endl;
    std::cout << "back: "  <<test1.back() <<std::endl;

    std::cout << "---------------------------------------------\n";


    DoublyLinkedList<int> test2(test1);
    test2.pop_back();
    std::cout << "size test1 : " << test1.size() << std::endl;
    std::cout << "size test2 : " << test2.size() << std::endl;

    std::cout << "---------------------------------------------\n";
    test1.push_back(3); test1.push_back(4); test1.push_back(5); test1.push_back(6);
    for(int i: test1){
        std::cout << i <<" ";
    }
    std::cout << "\n";
    test1.pop_front();
    for(DoublyLinkedList<int> ::iterator itr=test1.begin(); itr!=test1.end(); itr++){
        std::cout << *itr  << " ";
    }
    

    return 0;
}

