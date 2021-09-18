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
        struct Edge{

            int dest;           //The position of the other vertex of the edge     
            E cost;             //Weight
            Edge<V,E>* link;    //Next edge

            Edge(int num, E weight):dest(num), cost(weight), link(nullptr){
            }

            bool operator!=(Edge<V,E>& R)const{
                return dest!=R.dest
            }
            
        };


        struct Vertex{
            V data;         //name of vertex
            Edge<V.E>* adj; //list of vertex
        };
        
        

        enum {DEFAULT_VERTICES = 100};


    public:
        GraphAdjacencyList(int size = DEFAULT_VERTICES){
            maxVertices = size;
            numEdges = 0;
            numVertices = 0;
            VertexTable  = new VertexTable[maxVertices];
            
            for(int i=0; i<maxVertices; i++){
                VertexTable[i] = 0;
            }
        }


        GraphAdjacencyList(const GraphAdjacencyList& orig);


        virtual ~GraphAdjacencyList(){
            for(int i=0; i<numVertices; i++){
                Edge<V,E>* p = VertexTable[i].adj;
                while(p!=nullptr){
                    VertexTable[i].adj = p->link
                    delete p;
                    p = VertexTable[i].adj;
                }
            }
            delete []VertexTable;
        }

        T getValue(int v){
            return (v >= 0 && i < numVertices)? VertexTable[i] : 0;
        }

        E getWeight(int v1, int v2){
            Edge<V,E>* P = VertexTable[v1].adj;
            while(p!=nullptr && p->dest!=v2){
                p = p->link;
            }
            if(p != nullptr){
                return p->cost;
            }
            return 0;
        }

        void insertVertex(const T& vertex){
            
            if(numVertices == maxVertices){
                reserva(numVertices*2);
            }

            VertexTable[numVertices].data == vertex;
            numVertices++;

        }

        void insertEdge(int v1, int v2, E weight){
            if(v1 < 0 && v1 > numVertices && v2 < 0 && v2 > numVertices){
                throw invalid_argument("Exception: argument incorrect.")
            }

            Edge<V,E> *q, *p = VertexTable[v1].adj;

            while(p!=nullptr && p->dest!= v2){
                p = p->link;
            }
            if(p != nullptr){
                throw invalid_argument("Exception: edge exist.")
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

        void removeVertex(int v){
            if(numVertices == 1 || v < 0 || v >= numVertices){
                throw out_of_range("Exception: out of range.");
            }

            Edge<V,E>  *p, *q, *s, *t;
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
                if(s->dest == numVertices){
                    s->dest = v;
                    break;
                }else{
                    s = s->link;
                }
                p = p->link;
            }

        }

        void removeEdge(int v1, int v2){
            if(v1 < 0 && v1 > numVertices && v2 < 0 && v2 > numVertices){
                throw invalid_argument("Exception: argument incorrect.")
            }

            Edge<V,E> *p = VertexTable[v1].adj, *q =nullptr, *s = p;
            while(p != nullptr && p->dest != v2){
                q = p;
                p = p->link;
            }
            if(p != nullptr){
                if(p == s){
                    VertexTable[v1].adj = p->link;
                }else{
                    q->link = p->link;
                }
                delete p;
            }else{
                throw invalid_argument("Exception: can't find edge");
            }

            p = VertexTable[v2].adj; q =nullptr; s = p;
            while(p != nullptr && p->dest != v1){
                q = p;
                p = p->link;
            }
            if(p == s){
                VertexTable[v2].adj = p->link;
            }else{
                q->link = p->link;
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
            VertexTable = new VertexTable[newCapacity];

            for(int i=0; i<maxVertices; i++){
                VertexTable[i] = 0;
            }

            for(int i=0; i<this->numVertices; i++){
                VertexTable[i] = oldVertexTable[i];
            }

            maxVertices = newCapacity;
            delete []oldVertexTable;
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

        void printGraphVertx(){
            for(int i=0; i<numVertices; i++){
                cout << VertexTable[i].data << " --> ";
                Edge<V,E> *p = VertexTable[i].adj;
                while(p != nullptr){
                    cout << p->dest << " (cost : "<< p->cost << " ) --> ";
                    p = p->link
                }
                cout << endl;
            }
        }



    private:
        int numVertices;
        int numEdges;
        int maxVertices;

        Vertex<V,E>* VertexTable;


        int getVertexPos(V vertex){
            for(int i=0; i<numVertices; i++){
                if(VertexTable[i].data == vertex){
                    return i;
                }
            }
            throw out_of_range("Exception: can't find vertex.");
        }

};

#endif /* GRAPHADJACENCYLIST_H */

