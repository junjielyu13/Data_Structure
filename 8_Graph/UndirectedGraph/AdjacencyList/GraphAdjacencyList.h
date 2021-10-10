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

#include <iostream>
#include <stdexcept>

using namespace std;


template <class V, class E>
class GraphAdjacencyList {

    private:

        template <class A, class C>
        struct Edge{

            int dest;           //The position of the other vertex of the edge     
            E cost;             //Weight
            Edge<A,C>* link;    //Next edge

            Edge(){
            }

            Edge(int num, C weight):dest(num), cost(weight), link(nullptr){
            }

            bool operator!=(Edge<A,C>& R)const{
                return dest!=R.dest;
            }
            
        };

        template <class A, class C>
        struct Vertex{
            A data;         //name of vertex
            Edge<A, C>* adj; //list of vertex
        };


        enum {DEFAULT_VERTICES = 20};


    public:
        GraphAdjacencyList(int size = DEFAULT_VERTICES){
            maxVertices = size;
            numEdges = 0;
            numVertices = 0;
            VertexTable  = new Vertex<V,E>[maxVertices];
            
            
            for(int i=0; i<maxVertices; i++){
                VertexTable[i].adj = nullptr;
            }
        }


        GraphAdjacencyList(const GraphAdjacencyList& orig);


        virtual ~GraphAdjacencyList(){
            for(int i=0; i<numVertices; i++){
                Edge<V,E>* p = VertexTable[i].adj;
                while(p!=nullptr){
                    VertexTable[i].adj = p->link;
                    delete p;
                    p = VertexTable[i].adj;
                }
            }
            delete []VertexTable;
        }

        V getValue(V vertex){
            int pos = getVertexPos(vertex);
            return (pos >= 0 && pos < numVertices) ? VertexTable[pos].data : 0;
        }

        E getWeight(V vertex1, V vertex2){

            int v1 = getVertexPos(vertex1);
            int v2 = getVertexPos(vertex2);

            Edge<V,E>* p = VertexTable[v1].adj;
            while(p!=nullptr && p->dest!=v2){
                p = p->link;
            }
            if(p != nullptr){
                return p->cost;
            }
            return 0;
        }

        void insertVertex(const V& vertex){
            
            if(numVertices == maxVertices){
                reserva(numVertices*2);
            }

            VertexTable[numVertices].data = vertex;
            numVertices++;

        }

        void insertEdge(V vertex1, V vertex2, E weight){

            int v1 = getVertexPos(vertex1);
            int v2 = getVertexPos(vertex2);

            Edge<V,E> *q, *p = VertexTable[v1].adj;

            while(p!=nullptr && p->dest!= v2){
                p = p->link;
            }
            if(p != nullptr){
                throw invalid_argument("Exception: exist.");
            }

            q = new Edge<V,E>;
            p = new Edge<V,E>;

            //Undirecte:
            p->dest = v2;
            p->cost = weight;
            p->link = VertexTable[v1].adj;
            VertexTable[v1].adj = p;

            q->dest = v1;
            q->cost = weight;
            q->link = VertexTable[v2].adj;
            VertexTable[v2].adj = q;

            numEdges++;
        }

        void removeVertex(V vertex){

            int v = getVertexPos(vertex);

            Edge<V,E>  *p, *s, *t;
            int k;

            while(VertexTable[v].adj != nullptr){
                p = VertexTable[v].adj;
                k = p->dest;
                s = VertexTable[k].adj;
                t = nullptr;

                while(s != nullptr && s->dest != v){
                    t = s;
                    s = s->link;
                }
                if(s != nullptr){
                    if(t == nullptr){
                        VertexTable[k].adj = s->link;
                    }else{
                        t->link = s->link;
                    }
                    delete s;
                }
                VertexTable[v].adj = p->link;
                delete p;
                numEdges--;
            }

            numVertices--;
            VertexTable[v].data = VertexTable[numVertices].data;
            p = VertexTable[v].adj = VertexTable[numVertices].adj;

            while(p != nullptr){
                s = VertexTable[p->dest].adj;
                while(p != nullptr){
                    if(s->dest == numVertices){
                        s->dest = v;
                        break;
                    }else{
                        s = s->link;
                    }
                }
                p = p->link;
            }
        }

        void removeEdge(V vertex1, V vertex2){

            int v1 = getVertexPos(vertex1);
            int v2 = getVertexPos(vertex2);

            Edge<V,E> *p = VertexTable[v1].adj, *q = nullptr, *s = p;
            while(p != nullptr && p->dest != v2){
                q = p;
                p = p->link;
            }
            if(p != nullptr){
                if(p == s){
                    VertexTable[v1].adj = p->link;
                }else{
                    if(p == nullptr){
                        q->link = nullptr;
                    }else{
                        q->link = p->link;
                    }
                }
                delete p;
            }else{
                throw invalid_argument("Exception: can't find edge");
            }

            p = VertexTable[v2].adj; 
            q = nullptr; 
            s = p;

            while(p != nullptr && p->dest != v1){
                q = p;
                p = p->link;
            }

            if(p == s){
                VertexTable[v2].adj = p->link;
            }else{
                if(p == nullptr){
                    q->link = nullptr;
                }else{
                    q->link = p->link;
                }
            }

            delete p;
        }

        int NumberOfVertices()const{
            return numVertices;
        }

        int NumberOfEdges()const{
            return numEdges;
        }

        bool isEmpty()const{
            return numEdges == 0;
        }

        bool isFull()const{
            return numVertices == maxVertices || numEdges == maxVertices * (maxVertices-1)/2;
        }

        void reserva(int newCapacity){
            if(newCapacity < numVertices){
                return;
            }    

            Vertex<V,E>* oldVertexTable = VertexTable;
            VertexTable = new Vertex<V,E>[newCapacity];

            for(int i=0; i<maxVertices; i++){
                VertexTable[i].adj = nullptr;
            }

            for(int i=0; i<this->numVertices; i++){
                VertexTable[i] = oldVertexTable[i];
            }

            maxVertices = newCapacity;
            delete []oldVertexTable;
        }


        void printGraphList(){
            for(int i=0; i<numVertices; i++){
                cout << VertexTable[i].data << " --> ";
                Edge<V,E> *p = VertexTable[i].adj;
                while(p != nullptr){
                    cout << VertexTable[p->dest].data<< " (cost : "<< p->cost << " ) --> ";
                    p = p->link;
                }
                cout << endl;
            }
        }


    private:
        int numVertices;
        int numEdges;
        int maxVertices;

        Vertex<V,E>* VertexTable;

        int getVertexPos(const V& vertex){
            for(int i=0; i<numVertices; i++){
                if(VertexTable[i].data == vertex){
                    return i;
                }
            }
            throw out_of_range("Exception: can't find vertex.");
        }

};

#endif /* GRAPHADJACENCYLIST_H */

