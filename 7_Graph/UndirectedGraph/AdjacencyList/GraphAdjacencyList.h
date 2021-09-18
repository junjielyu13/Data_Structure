/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GraphAdjacencyList.h
 * Author: Junjie_Li
 *
 * Created on September 18, 2021, 12:14 PM
 */

#ifndef GRAPHADJACENCYLIST_H
#define GRAPHADJACENCYLIST_H

template <class V, class E>
class GraphAdjacencyList {

    private:
        struct Edge{
            int dest
            E cost
        };
        

        enum {DEFAULT_VERTICES = 100};


    public:
        GraphAdjacencyList(int size = DEFAULT_VERTICES);
        GraphAdjacencyList(const GraphAdjacencyList& orig);
        virtual ~GraphAdjacencyList();

        T getValue(int v)
        E getWeight(int v1, int v2);

        void insertVertex(const T& vertex);
        void insertEdge(int v1, int v2, E cost);

        void removeVertex(int v);
        void removeEdge(int v1, int v2);

        int NumberOfVertices()const;
        int NumberOfEdges()const;

        bool isEmpty()const;
        bool isFull()const;


    private:
        int numVertices;
        int numEdges;


};

#endif /* GRAPHADJACENCYLIST_H */

