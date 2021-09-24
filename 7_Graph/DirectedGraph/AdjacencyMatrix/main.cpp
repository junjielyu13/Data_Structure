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
    graph.insertVertex(6);



    graph.insertEdge(1,2,12);
    graph.insertEdge(1,4,14);

    graph.insertEdge(2,5,25);

    graph.insertEdge(3,6,36);
    graph.insertEdge(3,5,35);

    graph.insertEdge(4,2,42);

    graph.insertEdge(5,4,54);

    graph.insertEdge(6,6,66);


    graph.printMatrixTable();

    cout << "-------------------------------------------------------------" << endl;

    graph.removeVertex(2);
    graph.printMatrixTable();

    cout << "-------------------------------------------------------------" << endl;

    graph.removeEdge(3,5);
    graph.printMatrixTable();

    return 0;

}

