/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BTree.h
 * Author: Junjie_Li
 *
 * Created on August 14, 2021, 1:59 AM
 */

/**
 * B-Tree
*/
#ifndef BTREE_H
#define BTREE_H

template <typename Comparable>
class BTree {

    private:
        struct BTreeNode{
            Comparable *keys;   //an array of keys
            int t;              //Degree for number of keys
            BTreeNode **array;  //Array of child pointers.
            int n;              //Number of keys of the current node.
            bool leaf;          //return true if is leaf, otherwise false.
        };
        


    public:
        BTree(int t);
        BTree(const BTree& orig);
        virtual ~BTree();

        void traverse() const;
        BTreeNode* search(const Comparable& key) const; 

        void insert(const Comparable& key);
        void remove(const Comparable& key);

    private:
        BTreeNode* root;
        int t;              //Degree for number of keys

        /**
         * traverse:
        */
        void traverse() const;

        /**
         * search:
        */
        BTreeNode* search(const Comparable& key) const; 


        /**
         * insert:
        */
        void insertNonFull(const Comparable& key);
        void splitChild(int i, BTreeNode *y);

};

#endif /* BTREE_H */

