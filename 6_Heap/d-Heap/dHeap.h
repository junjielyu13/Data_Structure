/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   dHeap.h
 * Author: Junjie_Li
 *
 * Created on August 24, 2021, 9:43 PM
 */

#include <vector>
#include <stdexcept>
#include <iostream>
#include <math.h>

using namespace std;

#ifndef DHEAP_H
#define DHEAP_H

template<typename Comparable>
class dHeap {

    public:
        /**
         * d = 2 --> binaryHeap;
         * d = 3 --> 3-Heap;
         * d = 4 --> 4-Heap;
         * ...
        */
        explicit dHeap(int dimension = 2, int capacity = 100){      
            d_ary = dimension;
            array.resize(capacity);
            currentSize = 0;
        }
        explicit dHeap(const vector<Comparable>& items, int dimension = 2): array(items.size()+10), currentSize(items.size()){
            d_ary = dimension;
            for(int i=0; i<items.size(); i++){
                array[i] = items[i];
            }
            buidHeap();
        }
        dHeap(const dHeap& orig){
            d_ary = orig.d_ary;
            array.resize(orig.array.size());
            currentSize = orig.currentSize;

            for(int i=0; i<orig.array.size(); i++){
                array[i] = orig.array[i];
            }

        }
        virtual ~dHeap(){
            makeEmpty();
        }

        bool isEmpty()const{
            return currentSize == 0;
        }

        const Comparable& findMin()const{
            return array[0];
        }

        /**
         * Insert item x, allowing duplicates;
        */
        void insert(const Comparable& x){
            if(currentSize == array.size()-1){
                array.resize(array.size() * d_ary);
            }
            
            //Percolate up
            int hole = currentSize;
            currentSize++;
            array[hole] = x;

            Comparable temp = array[hole];
            for( ; hole>0 && temp<array[(hole - 1)/d_ary]; hole = ((hole - 1)/d_ary)){ 
                array[hole] = array[((hole - 1)/d_ary)];  
            }
            array[hole] = temp;
        }

        /**
         * Remove the minimum item
        */
        void deleteMin(){
            if(isEmpty()){
                throw out_of_range("Exception: Underflow.");
            }
            array[0] = array[currentSize-1];
            currentSize--;
            percolateDown(0);
        }

        /**
         * Remove the minimum item and place it in minItem
        */
        void deleteMin(Comparable& minItem){
            if(isEmpty()){
                throw out_of_range("Exception: Underflow.");
            }
            minItem = array[0];
            array[0] = array[currentSize--];
            percolateDown(0);
        }

        void makeEmpty(){
            while(!array.empty()){
                array.pop_back();
            }
        }

        void print(){
            for(int i = 0; i<currentSize; i++){
                cout << array[i] << " ";
            }
        }

    private:
        int   d_ary;          //d children
        int   currentSize;   
        typename::vector<Comparable> array;       //The heap array; 

        /**
         * Establish heap order property from an arbitrary
         * arrangement of items. Runs in linear time.
        */
        void buidHeap(){
            for(int i=currentSize/d_ary; i>=0; i--){
                percolateDown(i);
            }
        }
        
        /**
         * Iternal method to percolate down in the heap.
         * hole is the index at which the percolate begins
        */
        void percolateDown(int hole){
            int child = 0;
            Comparable temp =array[hole];

            for( ; hole*d_ary+1 < currentSize; hole = child){
                
                child = smallestChild(hole);

                if(array[child] < temp){
                    array[hole] = array[child];
                }else{
                    break;
                }
            }
            array[hole] = temp;
        }

        /**
         * Function to get smallest child from all valid indices 
         */
        int smallestChild(int hole){
            int PosChild = hole*d_ary+1;
            int i = 2;
            int ChooseChild = hole*d_ary+i;
            while( (i <= d_ary) && (ChooseChild < currentSize)){
                if(array[ChooseChild] < array[PosChild]){
                    PosChild = ChooseChild;
                }
                i++;
                ChooseChild = hole*d_ary+i;
            }
            return PosChild;
        }

};

#endif /* DHEAP_H */

