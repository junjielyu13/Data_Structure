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

#include <iostream>

template <typename Comparable>
class BTree {

    private:
        struct BTreeNode{
            Comparable *keys;   //an array of keys
            int key_count;      //Minmum degree(number of keys)

            BTreeNode **childs;  //Array of child pointers.

            bool leaf;          //return true if is leaf, otherwise false.

            BTreeNode(const int& _t, bool _leaf){
                key_count = _t;
                leaf = _leaf;

                keys = new Comparable[2*key_count-1];   //Allocate memory for array of keys.
                childs = new BTreeNode* [2*key_count];  //Allocate memory for array of child pointers.

                for(int i = 0; i < 2*key_count; i++){
                    keys[i] = 0;
                    childs[i] = nullptr;
                }
                childs[2 * key_count] = nullptr;
            }
        };
        


    public:
        BTree(const int& _t){
            root = nullptr;
            t = _t;
        }
        // BTree(const BTree& orig);
        // virtual ~BTree();

        void traverse(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return traverse(root);
        }
        BTreeNode* search(const Comparable& key) const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return search(key, root);
        }

        bool isEmpty() const{
            return root == nullptr;
        }

        void insert(const Comparable& key){
            if(root == nullptr){
                root = new BTreeNode(0, true);
            }else{
                if(root->key_count == 2*t-1){       //if root is full, then tree grows in height
                    BTreeNode* y = new BTreeNode(0, false);
                    y->childs[1] = root;
                    splitChild(0, root, y);
                    insertNonFull(key, y);
                }else{                              //if root is not full, call insertNonFul for root
                    insertNonFull(key, root);
                }
            }
        }


        void remove(const Comparable& key);

    private:
        BTreeNode* root;
        int t;              //Minmum degree(number of keys)

        /**
         * traverse:
        */
        void traverse(BTreeNode* p){
            int i;
            for(i = 0; i < p->key_count; i++){
                if(p->leaf == false){
                   return traverse(p->childs[i]);
                }
                if(p != nullptr){
                    std::cout << p->keys[i] << " ";
                }
            }

            if(p->leaf == false){
                return traverse(p->childs[i]);
            }
        }

        /**
         * search:
        */
        BTreeNode* search(Comparable key, BTreeNode* p) const{
            int i = 0;
            while(i < p->n && key > p->keys[i]){
                i++;
            }
            if(p->keys[i] == key){
                return p;
            }else if(p->leaf == true){
                return nullptr;
            }else{
                return search(key, p->childs[i]);
            }
        }


        /**
         * insert:
        */
        void splitChild(int index, BTreeNode* parent, BTreeNode* child){
            //Create a new node which is going to store(t-1) keys
            BTreeNode* anotherChild = new BTreeNode(parent->key_count - 1, child->leaf);
            
            //Copy the last (t-1) keys of y to z;
            for(int j = 1; j < t; j++){
                anotherChild->keys[j] = child->keys[j+t];
            }

            //Copy the last t children of y to z;
            if(child->leaf == false){
                for(int j = 1; j <= t; j++){
                    anotherChild->childs[j] = anotherChild->childs[j+t];
                }
            }
            

            //reduce the number of keys in y;
            child->key_count = t - 1;

            //since this node is going to have a new child, create space of new child
            for(int j = parent->key_count; j > index; j--){
                parent->childs[j+1] = parent->childs[j];
            }

            //link the new child to this node
            parent->childs[index+1] = anotherChild;

            //a key of y will move to this node. find the location of new key and move all greater eky one space ahead
            for(int j = parent->key_count; j >= index; j--){
                parent->keys[j+1] = parent->keys[j];
            }

            //copy the middle key of y to this node
            parent->keys[index] = child->keys[t-1];

            //increment count of keys in this node
            parent->key_count++;
        }

        void insertNonFull(const Comparable& key, BTreeNode* p){

            int i = p->key_count;
    
            if(p->leaf == true){    //if p is a leaf node
                //-find the location of new key to be inserted
                //-moves all greater keys to one place ahead
                while( i >= 1 && p->keys[i] > key){
                    p->keys[i+1] = p->keys[i];        
                    i--;
                }
                //insert the new key at found location
                p->keys[i+1] = key;
                p->key_count++;
            }else{
                //find the child which is going to have the new key
                while( i >= 1 && p->keys[i] > key){
                    i--;
                }
                i++;
                if(p->childs[i]->key_count == 2*t-1){      //if the found child is full
                    //if the child is full, then split it
                    splitChild(i, p, p->childs[i]);
                    
                    //after split, the middle key of array[i] goes up and array[i] is 
                    //splitted into two, see which of the tow is going to have the new key
                    if(p->keys[i+1] < key){
                        i++;
                    }
                }
                insertNonFull(key, p->childs[i+1]);
            }
        }


        /**
         * remove:
        */

};

#endif /* BTREE_H */

