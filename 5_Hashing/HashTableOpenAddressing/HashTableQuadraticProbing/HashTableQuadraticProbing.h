/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTableQuadraticProbing.h
 * Author: Junjie_Li
 *
 * Created on August 22, 2021, 6:03 PM
 */
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
using namespace std;

#ifndef HASHTABLEQUADRATICPROBING_H
#define HASHTABLEQUADRATICPROBING_H

template <typename HashedObj>
class HashTableQuadraticProbing {

    public:
        explicit HashTableQuadraticProbing(int size = 101): array(nextPrime(size)){
            makeEmpty();
        }
        HashTableQuadraticProbing(const HashTableQuadraticProbing& orig);
        virtual ~HashTableQuadraticProbing();

        bool contains(const HashedObj& x)const{
            return isActive(findPos(x));
        }

        void makeEmpty(){
            currentSize = 0;
            for(int i=0; i<array.size(); i++){
                array[i].info = EMPTY;
            }
        }
        void insert(const HashedObj& x){
            //insert x as active
            int currentPos = findPos(x);
            if(!isActive(currentPos)){
                array[currentPos] = HashEntry(x, ACTIVE);

                if(++currentSize > array.size()/2){
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
            for(int i=0; i<array.size(); i++){
                if(array[i].info == ACTIVE){
                    cout << array[i].element << " ";
                }else if(array[i].info == DELETED){
                    cout << array[i].element << " D ";
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
            int offset = 1;
            int currentPos = myhash(x);

            while(array[currentPos].info != EMPTY && array[currentPos].element != x){
                currentPos += offset;
                offset += 2;
                if(currentPos >= array.size()){
                    currentPos -= array.size();
                }
            }
            return currentPos;
        }
        /**
         * Rehashing for quadratic probing hash table
        */
        void rehash(){
            vector<HashEntry> oldArray = array;

            //create new double-sized, empty table
            array.resize(nextPrime(2 * oldArray.size()));
            for(int i=0; i<array.size(); i++){
                array[i].info = EMPTY;
            }

            //copy table over
            currentSize = 0;
            for(int i=0; i<oldArray.size(); i++){
                if(oldArray[i].info == ACTIVE){
                    insert(oldArray[i].element);
                }
            }
        }
        int myhash(const HashedObj& x)const{
            int hashVal = hash(x);  

            hashVal %= theLists.size();
            if(hashVal < 0){
                hashVal += theLists.size();
            }
            return hashVal;
        }

        /**
         * hash function of int 
        */
        int hash(const int& key) const{
            int hashVal = key;
            hashVal %= theLists.size();
            if(hashVal < 0){
                hashVal += theLists.size();
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

            hashVal %= theLists.size();
            if(hashVal < 0){
                hashVal += theLists.size();
            }
            return hashVal;

        }


        /**
         * genera number prime
        */
        int nextPrime(int size){
            int temp = size;
            if(isPrime(size)){
                temp++;
            }
            while(!isPrime(temp)){
                temp++;
            }
            return temp;
        }
        bool isPrime(int n){
            for(int i=2; i<=sqrt(n); i++){
                if( (n % i) == 0){
                    return false;
                }
            }
            return true;
        }



};

#endif /* HASHTABLEQUADRATICPROBING_H */

