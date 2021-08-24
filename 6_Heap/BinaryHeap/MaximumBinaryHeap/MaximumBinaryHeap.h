/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MaximumBinaryHeap.h
 * Author: Junjie_Li
 *
 * Created on August 24, 2021, 9:27 PM
 */
#include <vector>
#include <stdexcept>

using namespace std;

#ifndef MAXIMUMBINARYHEAP_H
#define MAXIMUMBINARYHEAP_H

template<typename Comparable>
class MaximumBinaryHeap {

    public:
        explicit MaximumBinaryHeap(int capacity = 100){
            array.resize(capacity);
            currentSize = 0;
        }
        explicit MaximumBinaryHeap(const vector<Comparable>& items): array(items.size()+10), currentSize(items.size()){
            for(int i=0; i<items.size(); i++){
                array[i+1] = items[i];
            }
            buidHeap();
        }
        MaximumBinaryHeap(const MaximumBinaryHeap& orig){
            array.resize(orig.array.size());
            currentSize = orig.currentSize;

            for(int i=0; i<orig.array.size(); i++){
                array[i] = orig.array[i];
            }
        }

        virtual ~MaximumBinaryHeap(){
            makeEmpty();
        }

        bool isEmpty()const{
            return currentSize == 0;
        }

        const Comparable& findMax()const{
            return array[1];
        }


        /**
         * Insert item x, allowing duplicates;
        */
        void insert(const Comparable& x){
            if(currentSize == array.size()-1){
                array.resize(array.size() * 2);
            }

            //Percolate up
            int hole = ++currentSize;
            for( ; hole>1 && x>array[hole/2]; hole/=2){
                array[hole] = array[hole/2];
            }
            array[hole] = x;

        }

        /**
         * Remove the maximum item
        */
        void deleteMax(){
            if(isEmpty()){
                throw out_of_range("Exception: Underflow.");
            }
            array[1] = array[currentSize--];
            percolateDown(1);
        }
        /**
         * Remove the maximum item and place it in minItem
        */
        void deleteMax(Comparable& minItem){
            if(isEmpty()){
                throw out_of_range("Exception: Underflow.");
            }
            minItem = array[1];
            array[1] = array[currentSize--];
            percolateDown(1);
        }


        void makeEmpty(){
            while(!array.empty()){
                array.pop_back();
            }
        }

    private:
        int   currentSize;    
        typename::vector<Comparable> array;       //The heap array;

        /**
         * Establish heap order property from an arbitrary
         * arrangement of items. Runs in linear time.
        */
        void buidHeap(){
            for(int i=currentSize/2; i>0; i--){
                percolateDown(i);
            }
        }

        /**
         * Iternal method to percolate down in the heap.
         * hole is the index at which the percolate begins
        */
        void percolateDown(int hole){
            int child;
            Comparable temp =array[hole];

            for( ; hole*2 <= currentSize; hole = child){
                child = hole * 2;
                if(child != currentSize && array[child+1] > array[child]){
                    child++;
                }
                if(array[child] > temp){
                    array[hole] = array[child];
                }else{
                    break;
                }
            }

            array[hole] = temp;
        }

};

#endif /* MAXIMUMBINARYHEAP_H */

