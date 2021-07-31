/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on July 30, 2021, 5:55 PM
 */

#include <cstdlib>
#include <iostream>
#include "Vector.h"

/*
 * 
 */
int main(int argc, char** argv) {


    Vector<int> test1;
    int nums[] = {5,4,1,7,4,5,2,4,7,9,6,3,1,6,8};
    std::cout << "size: " <<test1.size()<<std::endl;
    std::cout << "capacity: " <<test1.capacity()<<std::endl;
    std::cout << "---------------------------------------------\n";


    for(int i=0; i<(sizeof(nums)/sizeof(nums[0])); i++){
        test1.push_back(nums[i]);
    }

    while(!test1.empty()){
        std::cout << test1.back() << " ";
        test1.pop_back();
    }
    std::cout<<std::endl;

    std::cout << "---------------------------------------------\n";


    std::cout << "old size: " <<test1.size()<<std::endl;
    test1.resize(20);
    std::cout << "new size: " <<test1.size()<<std::endl;

    std::cout << "---------------------------------------------\n";


    std::cout << "old capacity: " <<test1.capacity()<<std::endl;
    test1.resize(50);
    std::cout << "new capacity: " <<test1.capacity()<<std::endl;
    
    std::cout << "---------------------------------------------\n";


    test1.clear();
    for(int i=0; i<(sizeof(nums)/sizeof(nums[0])); i++){
        test1.push_back(nums[i]);
    }
    for(int i=0; i<test1.size(); i++){
        std::cout << test1[i] << " ";
        std::cout << test1.at(i) << " ";
    }
    std::cout<<std::endl;

    Vector<int> test2(test1);

    std::cout << "---------------------------------------------\n";


    for(Vector<int>::iterator itr=test2.begin(); itr!=test2.end(); itr++){
        std::cout << *itr << " ";
    }
    std::cout<<std::endl;

    std::cout << "---------------------------------------------\n";


    test2.push_back(99);
    for(int i: test1){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for(int j: test2){
        std::cout << j << " ";
    }

    std::cout<<"\n\n\n";
    std::cout << "finish\n";
    

    return 0;
}

