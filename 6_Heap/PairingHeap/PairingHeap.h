/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PairingHeap.h
 * Author: Junjie_Li
 *
 * Created on August 27, 2021, 5:13 PM
 */

#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;


#ifndef PAIRINGHEAP_H
#define PAIRINGHEAP_H

template<typename Comparable>
class PairingHeap {

    private:
        struct PairNode{
            Comparable element;
            PairNode* prev;
            PairNode* leftChild;
            PairNode* nextSibling;

            PairNode(const Comparable& theElement, PairNode* pv=nullptr, PairNode* lt=nullptr, PairNode* rt=nullptr):
                element(theElement), prev(pv), leftChild(lt), nextSibling(rt){
            }
        };


    public:
        PairingHeap(){
            root = nullptr;
        }
        PairingHeap(const PairingHeap& orig){
            makeEmpty();
            root = nullptr;
            *this = orig;
        }
        virtual ~PairingHeap(){
            makeEmpty();
            root = nullptr;
        }

        const Comparable& findMin(){
            return root->element;
        }

        /**
         * Insert item x into the priority queue, maintaining heap order.
         * Return the position (a pointer to the node) containing the new item
        */
        void insert(const Comparable& x){  
            PairNode* newNode = new PairNode(x);
            if(root == nullptr){
                root = newNode;
            }else{
                compareAndLink(root,newNode);
            }
        }

        /**
         * Remove the minimum item and place it in minItem
        */
        void deleteMin(){
            if(isEmpty()){
                throw std::invalid_argument("Exception: Underflow.");
            }

            PairNode* oldRoot = root;
            if(root->leftChild == nullptr){
                root = nullptr;
            }else{
                root = combineSiblings(root->leftChild);
            }
            delete oldRoot;
        }

        /**
         * Change the value of the item stored in the pairing heap.
         * Throw IllegalArgumentException if newVal is larger than currently stored value.
         * p is a Position returned by insert.
         * newVal is the new value, which must be smaller than the currently sotred value.
        */
        void decreaseKey(PairNode* p, const Comparable& newVal){
            if(p->element < newVal){
                throw std::invalid_argument("Exception: Illegal Argument.");
            }
            p->element = newVal;

            if(p != nullptr){
                if(p->nextSibling != nullptr){
                    p->nextSibling->prev = p->prev;
                }
                if(p->prev->leftChild == p){
                    p->prev->leftChild = p->nextSibling;
                }else{
                    p->prev->nextSibling = p->nextSibling;
                }
                p->nextSibling = nullptr;
                compareAndLink(root, p);

            }
        }

        void merge(PairingHeap<Comparable>& rhs){
            if( this == &rhs){          //avoid aliasing problems
                return;
            }
            if(isEmpty()){
                throw std::invalid_argument("Exception: Underflow.");
            }
            compareAndLink(root, rhs.root);
        }


        bool isEmpty()const{
            return root == nullptr;
        }


        void makeEmpty(){
            while(!isEmpty()){
                deleteMin();
            }
        }

        const PairingHeap& operator=(const PairingHeap<Comparable>& rhs){
            if(this != &rhs){
                makeEmpty();
                cout << "test3";
                root = clone(rhs.root);
            }
            return *this;
        }


    private:

        PairNode* root;

        /**
         * Internal method that is the basic operation to maintain order.
         * Links first and second together to satisfy heap order.
         * first is root of tree 1, which may not be null.
         * first->nextSibling MUST be null on entry.
         * second is root of tree2, which may be null.
         * first becomes the result of the tree merge.
        */
        void compareAndLink(PairNode*& first, PairNode*& second){
            if(second == nullptr){
                return;
            }
            if(second->element < first->element){
                //Attach first as leftmost child of second
                second->prev = first->prev;
                first->prev = second;
                first->nextSibling = second->leftChild;
                if(first->nextSibling != nullptr){
                    first->nextSibling->prev = first;
                }
                second->leftChild = first;
                first = second;
            }else{
                //Attach second as leftmost child of first
                second->prev = first;
                first->nextSibling = second->nextSibling;
                if(first->nextSibling != nullptr){
                    first->nextSibling->prev = first;
                }
                second->nextSibling = first->leftChild;
                if(second->nextSibling != nullptr){
                    second->nextSibling->prev = second;
                }
                first->leftChild = second;
            }
        }

        /**
         * Internal method that implements two-pass merging
         * firstSibling the root of the conglomerate and is assumed not NULL.
        */
        PairNode* combineSiblings(PairNode* firstSibling){
            if(firstSibling->nextSibling == nullptr){
                return firstSibling;
            }

            //Allocate the arry
            static typename::vector<PairNode*> treeArray(5);

            //Store the subtrees in an array
            int numSibling = 0;
            for( ;firstSibling != nullptr; numSibling++){
                if(numSibling == treeArray.size()){
                    treeArray.resize(numSibling * 2);
                }
                treeArray[numSibling] = firstSibling;
                firstSibling->prev->nextSibling = nullptr;   //break links
                firstSibling = firstSibling->nextSibling;
            }

            if(numSibling == treeArray.size()){
                treeArray.resize(numSibling + 1);
            }
            treeArray[numSibling] == nullptr;

            //Combine subtrees two at a time, going left to right
            int i = 0;
            for( ; i+1 < numSibling; i+=2){
                compareAndLink(treeArray[i], treeArray[i+1]);
            }

            int j = i-2;
            //j has the result of last comparenAndLink
            //if an odd number of trees, get the last one.
            if(j == numSibling - 3){
                compareAndLink(treeArray[j], treeArray[j+2]);
            }

            //Now go right to left, merging last tree with
            //next to last. The result becomes the new last.
            for( ;j>=2; j-=2){
                compareAndLink(treeArray[j-2], treeArray[j]);
            }
            return treeArray[0];
        }   

        PairNode* clone(PairNode* t)const{
            if(t == nullptr){
                return nullptr;
            }
            cout << "t->element: "<< t->element << endl;
            return new PairNode(t->element, clone(t->prev), clone(t->leftChild), clone(t->nextSibling));
        }


};

#endif /* PAIRINGHEAP_H */

