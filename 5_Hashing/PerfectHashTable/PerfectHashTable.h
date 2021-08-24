/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PerfectHashTable.h
 * Author: Junjie_Li
 *
 * Created on August 23, 2021, 1:08 AM
 */
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <math.h>

using namespace std;

#ifndef PERFECTHASHTABLE_H
#define PERFECTHASHTABLE_H

template <typename HashedObj>
class PerfectHashTable {

    public:
        explicit PerfectHashTable(int size = 101): array(nextPrime(size)){
            makeEmpty();
            int arraysize = array.size();
            for(int i=0; i<arraysize; i++){
                array[i].resize(pow(i+1,2));
            }
        }
        PerfectHashTable(const PerfectHashTable& orig){
            makeEmpty();
            int origarraysize = orig.array.size();
            array.resize(origarraysize);
            for(int i=0; i<origarraysize; i++){
                int segarraysize = orig.array[i].size();
                for(int j=0; j<segarraysize; j++){
                    array[i].resize(segarraysize);
                    array[i][j] = orig.array[i][j];
                }
            }
        }
        virtual ~PerfectHashTable(){
            makeEmpty();
        }

        bool contains(const HashedObj& x)const{
            int pos1 = hash(x);
            int pos2 = findPos(x);
            return isActive( pos1,pos2      · );
        }

        void makeEmpty(){
            currentSize = 0;
            int arraysize = array.size();
            for(int i=0; i<arraysize; i++){
                int segarraysize = array[i].size();
                for(int j=0; j<segarraysize; j++){
                    array[i][j].info = EMPTY;
                }
            }
        }

        void insert(const HashedObj& x){
            //insert x as active

            /**
             *  Perfect Hash function
             *  h(i) =  array[h1(i)][h2(i)]
            */

            int pos1 = hash(x);
            int pos2 = findPos(x);

            if(!isActive(pos1,pos2)){
                array[pos1][pos2] = HashEntry(x, ACTIVE);
                int arraysize = array.size();
                if(++currentSize > arraysize/2){
                    rehash();
                }
            }
        }

        void remove(const HashedObj& x){
            int pos1 = hash(x);
            int pos2 = findPos(x);
            if(isActive(pos1,pos2)){
                array[pos1][pos2].info = DELETED;
            }
        }

        void printArray(){
            int arraysize = array.size();
            for(int i=0; i<arraysize; i++){ 
                int segarraysize = array[i].size();
                for(int j=0; j<segarraysize; j++){
                    if(array[i][j].info == ACTIVE){
                        cout << array[i][j].element << " ";
                    }else if(array[i][j].info == DELETED){
                        cout << array[i][j].element << "D ";
                    }else if(array[i][j].info == EMPTY){
                        cout << " E ";
                    }
                }
                cout <<"\n ---------------------------------------------------- \n";
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

        vector<vector<HashEntry>> array;
        int currentSize;


        bool isActive(int pos1, int pos2)const{
            return array[pos1][pos2].info == ACTIVE;
        }

        int findPos(const HashedObj& x)const{
            int pos1 = hash(x);
            int pos2 = seghash(x);

            /**
             *  Perfect Hash function
             *  h(i) = h1(i) + i * h2(i) mod size
            */
            while(array[pos1][pos2].info != EMPTY && array[pos1][pos2].element != x ){     
                pos2++;
                int segarraysize = array[pos1].size();
                if(pos2 >= segarraysize){
                    pos2 -= segarraysize;
                }

            }
            return pos2;
        }
        /**
         * Rehashing for quadratic probing hash table
        */
        void rehash(){
            vector< vector<HashEntry> > oldArray = array;

            //create new double-sized, empty table
            int oldarraysize = oldArray.size();
            array.resize(nextPrime(2 * oldarraysize));
            int arraysize = array.size();
            for(int i=0; i<arraysize; i++){
                //Corresponding extended array space
                array[i].resize(pow(i+1,2));
                int segarraysize = array[i].size();
                for(int j=0; j<segarraysize; j++){
                    array[i][j].info = EMPTY;
                }
            }


            //copy table over
            currentSize = 0;
            for(int i=0; i<oldarraysize; i++){
                int segoldarraysize = oldArray[i].size();
                for(int j=0; j<segoldarraysize; j++){
                    if(oldArray[i][j].info == ACTIVE){
                        insert(oldArray[i][j].element);
                    }
                }

            }
        }



        /**
         * hash function of int 
         * h(k) = ((ak + b) mod p ) mod size;
        */
        int hash(const int& key) const{
            int a = 3;
            int b = 42;
            int p = 101;
            int hashVal = (a * key + b) % p % array.size();
            
            if(hashVal < 0){
                hashVal += array.size();
            }

            return hashVal;
        }


        /**
         * hash function of string
         * h(k) = ((ak + b) mod p ) mod size;
        */
        int hash(const string& key) const {
            int hashVal = 0;
            for(int i=0; i<key.length(); i++){
                hashVal = 37 * hashVal + key[i];
            }

            int a = 3;
            int b = 42;
            int p = 101;
            hashVal = ( (a * hashVal + b) % p) % array.size();

            if(hashVal < 0){
                hashVal += array.size();
            }
            return hashVal;

        }

        /***
         *  The second hashing function
         *  h(k) = ((ajk + bj) mod p ) mod sizej;
         */
        int seghash(const int& key) const {
            int aj = 42;
            int bj = 3; 
            int p = 101;
            
            int hashVal = ( (aj * key + bj) % p) % array[hash(key)].size();

            if(hashVal < 0){
                hashVal += array.size();
            }
            return hashVal;
        }

        /***
         *  The second hashing function of string
         *  h(k) = ((ajk + bj) mod p ) mod sizej;
         */
        int seghash(const string& key) const {
            int hashVal = 0;
            for(int i=0; i<key.length(); i++){
                hashVal = 37 * hashVal + key[i];
            }

            int aj = 42;
            int bj = 3; 
            int p = 101;
            hashVal = ( (aj * hashVal + bj) % p) % array[hash(key)].size();

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

#endif /* PERFECTHASHTABLE_H */

