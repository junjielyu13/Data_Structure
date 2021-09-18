/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphAdjacencyMatrix.h
 * Author: Junjie_Li
 *
 * Created on September 18, 2021, 12:15 PM
 */

#ifndef GRAPHADJACENCYMATRIX_H
#define GRAPHADJACENCYMATRIX_H

#include <iostream>
#include <stdexcept>

using namespace std;


template <class V, class E>
class GraphAdjacencyMatrix {
    
    private:
        enum {DEFAULT_VERTICES = 100};

    public:
        GraphAdjacencyMatrix(int size = DEFAULT_VERTICES){
            maxVertices = size;
            numEdges = 0;
            numVertices = 0;

            verticesList = new verticesList[maxVertices];
            edgeTable = new E *[maxVertices];

            for(int i=0; i<maxVertices; i++){
                edgeTable[i] = new E[maxVertices];
            } 

            for(int i=0; i<maxVertices; i++){
                for(int j=0; j<maxVertices; j++){
                    edgeTable[i][j] = ( i == j ? 0 : -1);
                }
            }
        }

        GraphAdjacencyMatrix(const GraphAdjacencyMatrix& orig);

        virtual ~GraphAdjacencyMatrix(){
            delete []verticesList;
            delete []edgeTable;
        }

        void insertVertex(const V& vertex){
            if(numVertices == maxVertices){
                reserva(numVertices*2);
            }
            verticesList[numVertices++] = vertex;
        }

        void insertEdge(int v1, int v2, E cost){
            if(v1 < 0 && v1 >= numVertices && v2 < 0 && v2 >= numVertices){
                throw out_of_range("Exception: argument incorrect.");
            }

            if(edgeTable[v1][v2] == -1){
                edgeTable[v1][v2] = edgeTable[v2][1] = cost;
                numEdges++;
            }else{
                throw invalid_argument("Exception: edge exist.");
            }
        }

        void removeVertex(int v){
            if(v < 0 || v > numVertices){
                throw out_of_range("Exception: argument invalid");
            }

            verticesList[v] = verticesList[numVertices-1];

            for(int i=0; i<numVertices; i++){
                if(edgeTable[i][v] > 0 && edgeTable[i][v] != -1){
                    numEdges--;                    
                }
            }

            for(int i=0; i<numVertices; i++){
                edgeTable[i][v] = edgeTable[i][numVertices--];
            }

            numVertices--;
            for(int j=0; j<numVertices; j++){
                edgeTable[v][j] = edgeTable[numVertices][j];
            }
        }

        void removeEdge(int v1, int v2){
            if( v1 > -1 && v1 < numVertices && v2 > -< && v2 < numVertices && edgeTable[v1][v2] > 0 && edgeTable[v1][2] != -1){
                edgeTable[v1][v2] = edgeTable[v2][v1] = -1;
                numEdges--;
            }else{
                throw invalid_argument("Exception: invalid argument.");
            }
        }

        V getValue(int v){
            return verticesList[v];
        }

        E getWeight(int v1, int v2){
            return edge[v1][v2];
        }

        int numberOfVertices()const{
            return numVertices;
        }

        int numberOfEdges()const{
            return numEdges;
        }

        bool isEmpty()const{
            return numVertices == 0;
        }

        bool isFull()const{
            return numVertices == maxVertices || numEdges == maxVertices * (maxVertices-1)/2;
        }

        void reserva(int newCapacity){
            if(newCapacity < numVertices){
                return;
            }  

            V* oldVerticesList = verticesList;
            verticesList = new T[newCapacity];

            for(int i=0; i<numVertices; i++){
                verticesList[i] = oldVerticesList[i];
            }
            maxVertices = newCapacity;
            delete []oldVerticesList;


            E** oldEdgeTable = edgeTable;
            edgeTable = new E* [newCapacity];
            for(int i = 0; i<maxVertices; i++){
                edgeTable[i] = new E[maxVertices];
            }
            for(int i=0; i<maxVertices; i++){
                for(int j=0; j<maxVertices; j++){
                    edgeTable[i][j] = ( i == j ? 0 : -1);
                }
            }
            
            for(int i=0; i<numVertices; i++){
                for(int j=0; j<numVertices; j++){
                    edgeTable[i][j] = oldEdgeTable[i][j];
                }
            }

            delete []oldEdgeTable;
        }

        void printGraphWeight(){
            cout << "num vertex: " << numVertices << " , num edge: "<< numEdges << endl;
            for(int i=0; i<numVertices; i++){
                for(int j=i+1; j<numVertices; j++){
                    E weight = getWeight(i,j);
                    if(weight > 0){
                        cout << getValue(i) << " , " << getValue(j) << " , " << weight << endl;
                    }
                }
            }
        }

        void printMatrixTable(){
            cout << "   ";
            for(int i=0; i<numVertices; i++){
                cout << verticesList[i] << "  ";
            }
            cout << endl;

            for(int i=0; i<numVertices; i++){
                cout << verticesList[i] << " ";
                for(int j=0; j<numVertices; j++){
                    cout << edgeTable[i][j] << "  ";
                }
                cout << endl;
            }
        }

    private:
        int maxVertices;
        int numEdges;
        int numVertices;

        T* verticesList;        //list of vertex
        E** edgeTable;          //2 dimension list

        int getVertexPos(T vertex){
            for(int i=0; i<numVertices; i++){
                if(verticesList[i] == vertex){
                    return i;
                }
            }
            throw out_of_range("Exception: can't find vertex.");
        }

};

#endif /* GRAPHADJACENCYMATRIX_H */

