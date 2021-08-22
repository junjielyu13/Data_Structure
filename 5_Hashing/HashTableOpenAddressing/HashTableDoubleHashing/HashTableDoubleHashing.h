/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTableDoubleHashing.h
 * Author: Junjie_Li
 *
 * Created on August 22, 2021, 11:40 PM
 */

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
using namespace std;

#ifndef HASHTABLEDOUBLEHASHING_H
#define HASHTABLEDOUBLEHASHING_H

template <typename HashedObj>
class HashTableDoubleHashing {

    public:
        explicit HashTableDoubleHashing(int size = 101): array(nextPrime(size)){
            makeEmpty();
        }
        HashTableDoubleHashing(const HashTableDoubleHashing& orig){
            makeEmpty();
            int origarraysize = orig.array.size();
            array.resize(origarraysize);
            for(int i=0; i<origarraysize; i++){
                array[i] = orig.array[i];
            }
        }
        virtual ~HashTableDoubleHashing(){
            makeEmpty();
        }

        bool contains(const HashedObj& x)const{
            return isActive(findPos(x));
        }

        void makeEmpty(){
            currentSize = 0;
            int arraysize = array.size();
            for(int i=0; i<arraysize; i++){
                array[i].info = EMPTY;
            }
        }
        void insert(const HashedObj& x){
            //insert x as active
            int currentPos = findPos(x);
            if(!isActive(currentPos)){
                array[currentPos] = HashEntry(x, ACTIVE);

                int arraysize = array.size();
                if(++currentSize > arraysize/2){
                    rehash();
                }
            }
        }

        void remove(const HashedObj& x){
            int currentPos = findPos(x);
            if(isActive(currentPos)){
                array[currentPos].info = DELETED;
            }
        }

        void printArray(){
            int arraysize = array.size();
            for(int i=0; i<arraysize; i++){
                if(array[i].info == ACTIVE){
                    cout << array[i].element << " ";
                }else if(array[i].info == DELETED){
                    cout << array[i].element << "D ";
                }else if(array[i].info == EMPTY){
                    cout << " E ";
                }
            }
        }

        enum EntryType { ACTIVE, EMPTY, DELETED };
            
    private:

        struct HashEntry{
            HashedObj element;
            EntryType info;

            HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY):
                element(e), info(i){
            }
        };

        vector<HashEntry> array;
        int currentSize;


        bool isActive(int currentPos)const{
            return array[currentPos].info == ACTIVE;
        }
        int findPos(const HashedObj& x)const{
            int currentPos = myhash(x);
            int offset = 1;
            /**
             *  Double Hashing:
             *  h(i) = h1(i) + i * h2(i) mod size
            */
            while(array[currentPos].info != EMPTY && array[currentPos].element != x ){     
                currentPos = (currentPos + offset * seghash(x));
                int arraysize = array.size();
                if(currentPos >= arraysize){
                    currentPos -= arraysize;
                }
            }
            cout <<  x <<" = currentpos = " << currentPos << endl;
            return currentPos;
        }
        /**
         * Rehashing for quadratic probing hash table
        */
        void rehash(){
            vector<HashEntry> oldArray = array;

            //create new double-sized, empty table
            int oldarraysize = oldArray.size();
            array.resize(nextPrime(2 * oldarraysize));
            int arraysize = array.size();
            for(int i=0; i<arraysize; i++){
                array[i].info = EMPTY;
            }

            //copy table over
            currentSize = 0;
            for(int i=0; i<oldarraysize; i++){
                if(oldArray[i].info == ACTIVE){
                    insert(oldArray[i].element);
                }
            }
        }
        int myhash(const HashedObj& x)const{
            int hashVal = hash(x);  

            hashVal %= array.size();
            if(hashVal < 0){
                hashVal += array.size();
            }
            return hashVal;
        }

        /**
         * hash function of int 
        */
        int hash(const int& key) const{
            int hashVal = key;
            hashVal %= array.size();
            if(hashVal < 0){
                hashVal += array.size();
            }
            return hashVal;
        }


        /**
         * hash function of string
        */
        int hash(const string& key) const {
            int hashVal = 0;
            for(int i=0; i<key.length(); i++){
                hashVal = 37 * hashVal + key[i];
            }

            hashVal %= array.size();
            if(hashVal < 0){
                hashVal += array.size();
            }
            return hashVal;

        }

        /***
         *  The second hashing function
         *  h(k) = prime(size/2) - k mod size
         */
        int seghash(const int& key) const {
            int arraysize = array.size();
            int mod = nextPrime(arraysize / 2);
            int hashVal = mod - key;
            hashVal %= array.size();
            if(hashVal < 0){
                hashVal += array.size();
            }
            return hashVal;
        }


        /**
         * genera number prime
        */
        int nextPrime(int size) const {
            int temp = size;
            if(isPrime(size)){
                temp++;
            }
            while(!isPrime(temp)){
                temp++;
            }
            return temp;
        }
        bool isPrime(int n) const {
            for(int i=2; i<=sqrt(n); i++){
                if( (n % i) == 0){
                    return false;
                }
            }
            return true;
        }

};

#endif /* HASHTABLEDOUBLEHASHING_H */

