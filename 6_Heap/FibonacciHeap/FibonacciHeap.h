/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FibonacciHeap.h
 * Author: Junjie_Li
 *
 * Created on August 27, 2021, 5:10 PM
 */

#include <vector>
#include <stdexcept>
#include <iostream>
#include <math.h>

using namespace std;

#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

template<typename Comparable>
class FibonacciHeap {

    public:
        FibonacciHeap(){
            minRoot = nullptr;
        }
        // FibonacciHeap(const FibonacciHeap& orig);
        virtual ~FibonacciHeap(){
            makeEmpty();
            minRoot = nullptr;
        }


        /**
         * Insert a node in heap, if necessary change minroot
        */
        void Insert(const Comparable& key){
            FibonacciNode* x = new FibonacciNode(key);
            x->left = x;
            x->right = x;
            if(minRoot != nullptr){
                minRoot->left->right = x;
                x->right = minRoot;
                x->left = minRoot->left;
                minRoot->left = x;
                if(x->element < minRoot->element){
                    minRoot = x;
                }
            }else{
                minRoot = x;
            }
            currentSize++;
        }   


        /**
         * Decrease key of nodes in fibonnaci heap
        */
        void Decrease_Key(const Comparable& x, const Comparable& key){
            if(isEmpty()){
                throw std::out_of_range("Exception: Underflow.");
            }

            FibonacciNode* found = findNode(minRoot,x);
            if(found == nullptr){
                throw std::invalid_argument("Exception: not found in the heap.");
            }

            if(found->element < key){
                throw std::invalid_argument("Exception: Entered key greater than current key, can't do this operation.");
            }

            found->element = key;
            FibonacciNode* temp = found->parent;
            if(temp != nullptr && found->element < temp->element){
                Cut(found,temp);
                Cascading_cut(temp);
            }
            if (found->element < minRoot->element){
                minRoot = found;
            }
        }

        /**
         * Decrease key of nodes in fibonnaci heap
        */
        void Delete_Key(const Comparable& key){
            if(isEmpty()){
                throw std::out_of_range("Exception: Underflow.");
            }

            FibonacciNode* temp = findNode(minRoot,key);
            Extract_Min();
        }

        const Comparable& findMin() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Underflow");
            }
            return minRoot->element;
        }

        /**
         * Extract min node in fibonnaci heap
        */
        void Extract_Min(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Underflow");
            }

            FibonacciNode* temp = minRoot;
            FibonacciNode* ptr = temp;
            FibonacciNode* x = nullptr;
            if(temp->child != nullptr){
                x = temp->child;
                do{
                    //add child to the root list of heap
                    ptr = x->right;
                    minRoot->left->right = x;
                    x->right = minRoot;
                    x->left = minRoot->left;
                    minRoot->left = x;
                    if(x->element < minRoot->element){
                        minRoot = x;
                    }
                    x->parent = nullptr;
                    x = ptr;
                }while(ptr != temp->child);
            }

            //remove temp from the root list of hep
            temp->left->right = temp->right;
            temp->right->left = temp->left;
            minRoot = temp->right;

            if(temp == temp->right && temp->child == nullptr){
                minRoot = nullptr;
            }else{
                minRoot = temp->right;
                consolidate();
            }

            currentSize--;
        }


        /**
         * Union two Fibonnaci Heap
        */
        void Union(FibonacciHeap<Comparable>& rhs){
            minRoot->left->right = rhs.minRoot;
            rhs.minRoot->left->right = minRoot;

            FibonacciNode* temp = minRoot->left;
            minRoot->left = rhs.minRoot->left;
            rhs.minRoot->left = temp;

            if( (minRoot == nullptr) || (rhs.minRoot != nullptr && rhs.minRoot->element < minRoot->element) ){
                minRoot = rhs.minRoot;
            }

            currentSize += rhs.currentSize;
        }

        bool isEmpty() const{
            return minRoot == nullptr;
        }
        
        void makeEmpty(){
            while (!isEmpty()){
                Extract_Min();
            }
        }


    private:
        struct FibonacciNode{
            Comparable element;
            FibonacciNode* parent;
            FibonacciNode* left;
            FibonacciNode* right;
            FibonacciNode* child;
            int degree;
            bool mark;          //black or white mark of the node
            char find;          //flag for assisting in the findnode function

            FibonacciNode(const Comparable& theElement, FibonacciNode* pt = nullptr, FibonacciNode* lt = nullptr, FibonacciNode* rt = nullptr,
                         FibonacciNode* cd = nullptr, int deg = 0, bool mk = false, char fd = 'N'):
                element(theElement), parent(pt), left(lt), right(rt), child(cd), degree(deg), mark(mk), find(fd){
            }
        };
        

        FibonacciNode* minRoot;
        int currentSize;

        /**
         * consolitada node in fibonnaci heap
        */
        void consolidate(){
            float floatsize = log(currentSize)/log(2);
            int intsize = floatsize;

            FibonacciNode* array[intsize];
            for(int i=0; i<=intsize; i++){
                array[i] = nullptr;
            }

            FibonacciNode* x = minRoot;
            FibonacciNode* y;
            FibonacciNode* np;
            FibonacciNode* pt = x;

            int d;
            do{
                pt = pt->right;
                d = x->degree;
                while(array[d] != nullptr){
                    y = array[d];           //another node with the same degree as x
                    if(x->element > y->element){
                        //exchange x with y
                        np = x;
                        x = y;
                        y = np;
                    }
                    if(y == minRoot){
                        minRoot = x;
                    }
                    fibonnaci_link(y,x);
                    if(x->right == x){
                        minRoot = x;
                        array[d] = nullptr;
                    }
                    d++;
                }
                array[d] = x;
                x = x->right;
            }while(x != minRoot);

            minRoot = nullptr;

            for(int j=0; j<=intsize; j++){
                if(array[j] != nullptr){
                    array[j]->left = array[j];
                    array[j]->right = array[j];
                    if(minRoot != nullptr){
                        minRoot->left->right = array[j];
                        array[j]->right = minRoot;
                        array[j]->left = minRoot->left;
                        minRoot->left = array[j];
                        if(array[j]->element < minRoot->element){
                            minRoot = array[j];
                        }
                    }else{
                        minRoot = array[j];
                    }

                    if(minRoot == nullptr){
                        minRoot = array[j];
                    }else if(array[j]->element < minRoot->element){
                        minRoot = array[j];
                    }
                }
            }
        }

        /**
         * Link nodes in fibonnaci heap
        */
        void fibonnaci_link(FibonacciNode* y, FibonacciNode* z){
            //remove y from the root list of heap
            y->left->right = y->right;
            y->right->left = y->left;
            if(z->right == z){
                minRoot = z;
            }

            //make y a child of z
            y->left = y;
            y->right = y;
            y->parent = z;
            if(z->child == nullptr){
                z->child = y;
            }
            y->right = z->child;
            y->left = z->child->left;
            z->child->left->right = y;
            z->child->left = y;
            if(y->element < z->child->element){
                z->child = y;
            }

            //incrementing z.degree
            z->degree++;

            y->mark = false;
        }

        /**
         * Find node in fibonnaci heap
        */
        FibonacciNode* findNode(FibonacciNode* x, const Comparable& key){
            FibonacciNode* found = nullptr;

            FibonacciNode* temp = x;
            temp->find = 'Y';
            if(temp->element == key){
                found = temp;
                temp->find = 'N';
                return found;
            }
            if(found == nullptr){
                if(temp->child != nullptr){
                    found = find(temp->child, key);
                }
                if(temp->right->find != 'Y'){
                    found = find(temp->right, key);
                }
            }
            temp->find = 'N';
            return found;
        }

        /**
         * Cut the link between x and its parent node y, making x the root node
        */
        void Cut(FibonacciNode* x, FibonacciNode* y){
            //remove x from the child list of y, decrementing y.degree
            if(x == x->right){
                y->child = nullptr;
            }
            x->left->right = x->right;
            x->right->left = x->left;
            if(x == y->chiild){
                y->child = x->right;
            }
            y->degree--;

            //add x to the root list of heap
            x->right = x;
            x->left = x;
            minRoot->left->right = x;
            x->right = minRoot;
            x->left = minRoot->left;
            minRoot->left = x;


            x->parent = nullptr;
            x->mark = false;
        }

        /**
         * cascade cutting in fibonnaci heap
        */
        void Cascading_cut(FibonacciNode* y){
            FibonacciNode* z = y->parent;
            if(z != nullptr){
                if(y->mark == false){
                    y->mark = true;
                }else{
                    cut(y,z);
                    Cascading_cut(z);
                }
            }
        }
        

        
};

#endif /* FIBONACCIHEAP_H */

