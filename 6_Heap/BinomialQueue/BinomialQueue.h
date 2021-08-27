/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinomialQueue.h
 * Author: Junjie_Li
 *
 * Created on August 26, 2021, 7:08 PM
 */

#include <vector>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

#ifndef BINOMIALQUEUE_H
#define BINOMIALQUEUE_H


template<typename Comparable>
class BinomialQueue {

    public:
        BinomialQueue():theTrees(101){
            for(int i=0; i<theTrees.size(); i++){
                theTrees[i] = nullptr;
            }
            currentSize = 0;
        }
        BinomialQueue(const Comparable& item){
            for(int i=0; i<theTrees.size(); i++){
                theTrees[i] = nullptr;
            }
            currentSize = 0;
            insert(item);
        }
        BinomialQueue(const BinomialQueue& orig){
            makeEmpty();
            theTrees.clear();
            *this = orig;
        }
        virtual ~BinomialQueue(){
            makeEmpty();
            theTrees.clear();
        }

        bool isEmpty()const{
            return currentSize == 0;
        }
        const Comparable& findMin()const{
            if(isEmpty()){
                throw invalid_argument("Exception: UnderflowException");
            }
            return theTrees[findMinIndex()]->element;
        }

        void insert(const Comparable& x){
            BinomialQueue<Comparable> item;
            item.theTrees[0] = new BinomialNode(x,nullptr,nullptr);
            item.currentSize = 1;
            merge(item);
        }

        /**
         * Remove the minimum item.
        */
        void deleteMin(){
            if(isEmpty()){
                throw invalid_argument("Exception: UnderflowException");
            }
            int minIndex = findMinIndex();

            BinomialNode* oldRoot = theTrees[minIndex];
            BinomialNode* deletedTree = oldRoot->leftChild;
            delete oldRoot;

            //construct H'
            BinomialQueue<Comparable> deletedQueue;
            deletedQueue.theTrees.resize(minIndex+1);
            deletedQueue.currentSize = (1 << minIndex) - 1;
            for(int j=minIndex-1; j>=0; j--){
                deletedQueue.theTrees[j] = deletedTree;
                deletedTree = deletedTree->nextSibling;
                deletedQueue.theTrees[j]->nextSibling = nullptr;
            }

            //construct H'
            theTrees[minIndex] = nullptr;
            currentSize -= deletedQueue.currentSize + 1;

            merge(deletedQueue);
        }

        /**
         * Remove the minimum item and place it in minItem
        */
        void deleteMin(Comparable& minItem){
            if(isEmpty()){
                throw invalid_argument("Exception: UnderflowException");
            }
            int minIndex = findMinIndex();
            minItem = theTrees[minIndex]->element;
            deleteMin();
        }

        void makeEmpty(){
            for(int i=0; i<theTrees.size(); i++){
                makeEmpty(theTrees[i]);
            }
        }

        /**
         * Merge rhs into the priority queue.
         * rhs becomes empty. rhs must be different from this
        */
        void merge(BinomialQueue<Comparable>& rhs){
            if( this == &rhs){          //avoid aliasing problems
                return;
            }

            currentSize += rhs.currentSize;

            if(currentSize > capacity()){
                int oldNumTrees = theTrees.size();
                int newNumTrees = (theTrees.size() > rhs.theTrees.size() ? theTrees.size() : rhs.theTrees.size())  + 1;
                theTrees.resize(newNumTrees);
                for(int i=oldNumTrees; i<newNumTrees; i++){
                    theTrees[i] = nullptr;
                }
            }

            BinomialNode* carry = nullptr;
            for(int i=0, j=1; j<=currentSize; i++, j*=2){
                BinomialNode* t1 = theTrees[i];
                BinomialNode* t2 = rhs.theTrees[i];

                int whichCase = t1 ==  nullptr ? 0 : 1;
                    whichCase += t2 == nullptr ? 0 : 2;
                    whichCase += carry == nullptr ? 0 : 4;

                switch (whichCase){
                    case 0:         /* No Trees */
                    case 1:         /* Only this*/
                        break;
                    case 2:         /* Only rhs*/
                        theTrees[i] = t2;
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 4:         /* Only carry*/
                        theTrees[i] = carry;
                        carry = nullptr;
                        break;
                    case 3:         /* this and rhs*/
                        carry = combineTrees(t1, t2);
                        theTrees[i] = rhs.theTrees[i] = nullptr;
                        break;
                    case 5:         /* this and carry*/
                        carry = combineTrees(t1, carry);
                        theTrees[i] = nullptr;
                        break;
                    case 6:         /* rhs and carry*/
                        carry = combineTrees(t2,carry);
                        rhs.theTrees[i] = nullptr;
                        break;
                    case 7:         /* All three*/
                        theTrees[i] = carry;
                        carry = combineTrees(t1,t2);
                        rhs.theTrees[i] = nullptr;
                        break;                                                                                                                                           
                }
            }
            
            for(int k=0; k<rhs.theTrees.size(); k++){
                rhs.theTrees[k] = nullptr;
            }
            rhs.currentSize = 0;
        }

        const BinomialQueue& operator=(const BinomialQueue& rhs){
            if(this != &rhs){
                makeEmpty();
                theTrees.resize(rhs.theTrees.size());
                for(int i=0; i<rhs.theTrees.size(); i++){
                    theTrees[i] = clone(rhs.theTrees[i]);
                }
                currentSize = rhs.currentSize;
            }
            return *this;
        }

    private:
        struct BinomialNode{
            Comparable element;
            BinomialNode* leftChild;
            BinomialNode* nextSibling;

            BinomialNode(const Comparable& theElement, BinomialNode* lt, BinomialNode* rt):
                element(theElement), leftChild(lt), nextSibling(rt){
            }
        };

        enum { DEFAULT_TREES = 1};

        int currentSize;                            //Number of items in priority queue
        typename::vector<BinomialNode*> theTrees;   //An array of tree roots

        /**
         * Find index of tree containing the smallest item in the priority queue.
         * The priority queue not be empty
         * Return the index of tree containing the smallest item.
        */
        int findMinIndex()const{
            int i;
            int minIndex;

            for(i=0; theTrees[i] == nullptr; i++){
            }

            //int theTreessize = theTrees.size();
            for(minIndex = i; i<theTrees.size(); i++){
                if(theTrees[i] != nullptr && theTrees[i]->element < theTrees[minIndex]->element){
                    minIndex = i;
                }
            }

            return minIndex;
        }
        int capacity()const{
            return (1 << theTrees.capacity() ) - 1; 
        }

        /**
         * Return the result of merging equal-sized t1 and t2
        */
        BinomialNode* combineTrees(BinomialNode* t1, BinomialNode* t2){ 

            if( t2->element < t1->element ){
                return combineTrees(t2,t1);
            }
            t2->nextSibling = t1->leftChild;
            t1->leftChild = t2;
            return t1;
        }

        void makeEmpty(BinomialNode*& t)const{
            if(t != nullptr){
                makeEmpty(t->leftChild);
                makeEmpty(t->nextSibling);
                delete t;
                t = nullptr;
            }
        }

        BinomialNode* clone(BinomialNode* t)const{
            if(t == nullptr){
                return nullptr;
            }
            return new BinomialNode(t->element, clone(t->leftChild), clone(t->nextSibling));
        }
        
};

#endif /* BINOMIALQUEUE_H */

