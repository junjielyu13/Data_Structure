/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HashTableSeparateChaining.h
 * Author: Junjie_Li
 *
 * Created on August 22, 2021, 3:32 PM
 */
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <math.h>
using namespace std;

#ifndef HASHTABLESEPARATECHAINING_H
#define HASHTABLESEPARATECHAINING_H

template <typename HashedObj>
class HashTableSeparateChaining {
    public:
        explicit HashTableSeparateChaining(int size = 101){
            theLists.resize(size);
        }
        HashTableSeparateChaining(const HashTableSeparateChaining& orig){
            int origlistsize = orig.theLists.size();
            theLists.resize(origlistsize);

            for(int i=0; i<origlistsize; i++){
                typename list<HashedObj>::const_iterator itr = orig.theLists[i].begin();
                while(itr != orig.theLists[i].end()){
                    insert(*itr++);
                }
            }
        }
        virtual ~HashTableSeparateChaining(){
            makeEmpty();
        }

        bool contains(const HashedObj& x) const{
            const list<HashedObj>& list = theLists[myhash(x)];
            for(HashedObj obj: list){
                if(obj == x){
                    return true;
                }
            }
            return false;
        }

        void makeEmpty(){
            int listsize = theLists.size();
            for(int i=0; i<listsize; i++){
                theLists[i].clear();
            }
        }
        void insert(const HashedObj& x){
            list<HashedObj>& list = theLists[myhash(x)];
            if(!contains(x)){
                list.push_back(x);
                int listssize = theLists.size();
                if(++currentSize > listssize){
                    rehash();
                }
            }
        }
        void remove(const HashedObj& x){
            list<HashedObj>& list = theLists[myhash(x)];
            if(contains(x)){
                list.remove(x);
                --currentSize;
            }
        }
        
    private:
        vector< list<HashedObj> > theLists;         //the array of lists
        int currentSize;

        void rehash(){
            vector< list<HashedObj> > oldLists = theLists;

            //create new double-sized, empty table;
            theLists.resize(nextPrime(2 * theLists.size()));
            int listssize = theLists.size();
            for(int i=0; i<listssize; i++){
                theLists[i].clear();
            }

            //copy table over;
            currentSize = 0;
            int oldlistssize = oldLists.size();
            for(int i = 0; i < oldlistssize; i++){
                typename list<HashedObj>::iterator itr = oldLists[i].begin();
                while(itr != oldLists[i].end()){
                    insert(*itr++);
                }
                // for(HashedObj obj : oldLists[i]){
                //     cout << "insert = "<<  obj <<endl;
                //     insert(obj);
                // }
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

#endif /* HASHTABLESEPARATECHAINING_H */

