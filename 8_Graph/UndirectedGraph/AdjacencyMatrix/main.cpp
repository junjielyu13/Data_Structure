/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Junjie_Li
 *
 * Created on September 18, 2021, 12:05 PM
 */

#include <cstdlib>
#include <iostream>
#include "GraphAdjacencyMatrix.h"


using namespace std;

int main(int argc, char** argv) {
    
    GraphAdjacencyMatrix<int,int> graph;

    graph.insertVertex(1);
    graph.insertVertex(2);
    graph.insertVertex(3);
    graph.insertVertex(4);
    graph.insertVertex(5);


    graph.insertEdge(1,2,12);
    graph.insertEdge(1,5,15);

    graph.insertEdge(2,5,25);
    graph.insertEdge(2,3,23);
    graph.insertEdge(2,4,24);

    graph.insertEdge(3,4,34);

    graph.insertEdge(4,5,45);


    graph.printMatrixTable();

    cout << "-------------------------------------------------------------" << endl;

    graph.removeVertex(2);
    graph.printMatrixTable();

    cout << "-------------------------------------------------------------" << endl;

    graph.removeEdge(1,5);
    graph.printMatrixTable();

    return 0;
}

