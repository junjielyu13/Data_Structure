/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DisjointSet.h
 * Author: Junjie_Li
 *
 * Created on October 10, 2021, 10:30 PM
 */

#ifndef DISJOINTSET_H
#define DISJOINTSET_H

#include <vector>
using namespace std;

class DisjointSet {

    public:
        /**
         * Construct the disjoint sets object.
         * numElements is the initial number of disjoint sets
        */
        explicit DisjointSet(int numElements): s(numElements){
            for(int i=0; i<s.size(); i++){
                s[i] = -1;
            }
        }

        DisjointSet(const DisjointSet& orig){
            s.resize(orig.s.size());
            for(int i=0; i<s.size(); i++){
                s[i] = orig.s[i];
            }
        }


        /**
         * Perform a find
         * Error checks omitted again for simplicity
         * Return the set containing x
        */
        int find(int x) const{
            if(s[x] < 0){
                return x;
            }else{
                return find(s[x]);
            }
        }


        /**
         * Perform a find
         * Error checks omitted again for simplicity
         * Return the set containing x
        */
        int find(int x){
            if(s[x] < 0){
                return x;
            }else{
                return find(s[x]);
            }
        }

        /**
         * Union two disjoint sets.
         * For simplicity, we assume root1 and root2 are distinct
         * and represent set names.
         * root1 is the root of set1.
         * root2 is the root of set2.
        */
        void unioSets(int root1, int root2){
            s[root2] = root1;
        }

    private:
        vector<int> s;
        
};

#endif /* DISJOINTSET_H */

