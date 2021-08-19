/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on August 19, 2021, 12:56 AM
 */

#include <cstdlib>
#include <iostream>
#include "ScapegoatTree.h"


int main(int argc, char** argv) {

    ScapegoatTree<int> test1;
    int list[] = {2,10,6,7,8,9,5,1,4,3};
    int length = sizeof(list)/sizeof(list[0]);

    for(int i = 0; i < 5; i++){
        std::cout << " Test "<< list[i];
        test1.insert(list[i]);
        std::cout << "\nPreoreder: "; 
        test1.printPreorderTree();
        std::cout << "\nInoreder: "; 
        test1.printInorderTree();
        std::cout<<"\n\n";
    }

    std::cout << "\nPreoreder: "; 
    test1.printPreorderTree();
    std::cout << "\nInoreder: "; 
    test1.printInorderTree();


    std::cout << "\n---------------------------------------------\n";




    return 0;
}

