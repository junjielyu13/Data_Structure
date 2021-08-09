/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SplayTree.h
 * Author: Junjie_Li
 *
 * Created on August 5, 2021, 6:46 PM
 */

#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <stdexcept>
#include <iostream>

template <typename Comparable>
class SplayTree {

    private:
        struct BinaryNode{
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode(const Comparable& theElement = 0, BinaryNode *lt = nullptr, BinaryNode *rt = nullptr):
                element(theElement), left(lt), right(rt){
            }
        };
    
    public:
        SplayTree(){
            root = nullptr;
        }
        SplayTree(const SplayTree& orig){
            root = nullptr;
            *this = orig;
        }
        virtual ~SplayTree(){
            makeEmpty();
            delete root;
        }

        //deep copy;
        const SplayTree& operator=(const SplayTree& tree){
            if(this != &tree){
                makeEmpty();
                root = clone(tree.root);
            }
            return *this;
        }

        const Comparable& findMin(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            const Comparable& min = findMin(root)->element;
            splay(min, root);
            return root->element;
        }
        const Comparable& findMax(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            const Comparable& max = findMax(root)->element;
            splay(max, root);
            return root->element;
        }
        bool contains(const Comparable& x){
            splay(x, root);
            return contains(x, root);
        }
        bool isEmpty() const{
            return root == nullptr;
        }
        int size() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return size(root);
        }
        int height() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return height(root);
        }
        int depth() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return depth(root);
        }

        void printPreorderTree() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printPreorderTree(root);
        }
        void printInorderTree() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printInorderTree(root);
        }
        void printPostorderTree() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printPostorderTree(root);
        }

        void makeEmpty(){
            while(!isEmpty()){
                findMax();
                remove(root->element);
            }
        }

        void insert( const Comparable& x){
            static BinaryNode *newNode = nullptr;

            if(newNode == nullptr){
                newNode = new BinaryNode(x);
            }
            newNode->element = x; 


            if(root == nullptr){
                root = newNode;
                newNode = nullptr;
                return;
            }else{
                splay(x, root);
                if(x < root->element){
                    newNode->left = root->left;
                    newNode->right = root;
                    root->left = nullptr;
                    root = newNode;
                }else if(root->element < x){
                    newNode->right = root->right;
                    newNode->left = root;
                    root->right = nullptr;
                    root = newNode;
                }else{
                   return;
                }  
            }
            newNode = nullptr;  //next insert will call new 
        }
        void remove( const Comparable& x){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            if(!contains(x)){
                throw std::invalid_argument("Exception: can't find.");
            }
            
            BinaryNode *newTree;

            splay(x, root);
            if(root->element != x){
                return;
            }

            if(root->left == nullptr){
                newTree = root->right;
            }else{
                newTree = root->left;
                splay(x, newTree);
                newTree->right = root->right;
            }
            delete root;
            root = newTree;
        }
        BinaryNode *search(const Comparable& x){
            splay(root, x);
            return root;
        }



    private:
        BinaryNode *root;

        void LeftLeftRotation(BinaryNode* &t){
            BinaryNode* tl = t->left;
            t->left = tl->right;
            tl->right = t; 
            t = tl;
        }
        void RightRightRotation(BinaryNode* &t){
            BinaryNode* tr = t->right;
            t->right = tr->left;
            tr->left = t; 
            t = tr;
        }

        /**
         * The last accessed node becomes the new root.
         */
        void splay(const Comparable& x, BinaryNode*& t){

            static BinaryNode header;
            header.left = header.right = nullptr;
            BinaryNode *leftTreeMax, *rightTreeMin;
            leftTreeMax = rightTreeMin = &header;
    
            while(true){
                if(x < t->element){
                    if(t->left == nullptr){
                        break;
                    }
                    if(x < t->left->element){
                        LeftLeftRotation(t);
                    }
                    if(t->left == nullptr){
                        break;
                    }
                    rightTreeMin->left = t;
                    rightTreeMin = rightTreeMin->left;
                    t = t->left;
                    rightTreeMin->left = nullptr;
                }else if(t->element < x){
                    if(t->right == nullptr){
                        break;
                    }
                    if(t->right->element < x){
                        RightRightRotation(t);
                    }
                    if(t->right == nullptr){
                        break;
                    }
                    leftTreeMax->right = t;
                    leftTreeMax = leftTreeMax->right;
                    t = t->right;
                    leftTreeMax->right = nullptr;
                }else{
                    break;
                }
            }

            leftTreeMax->right = t->left;
            rightTreeMin->left = t->right;
            t->left = header.right;
            t->right = header.left;
        }        

        BinaryNode* findMin(BinaryNode* t){
            if(t == nullptr){
                return nullptr;
            }
            if(t->left == nullptr){
                return t;
            }
            return findMin(t->left);
        }
        BinaryNode* findMax(BinaryNode* t){
            if(t != nullptr){
                while(t->right != nullptr){
                    t = t->right;
                }
            }
            return t;
        }

        bool contains(const Comparable& x, BinaryNode* t){
            if(t == nullptr){
                return false;
            }else if(x < t->element){
                return contains(x, t->left);
            }else if(t->element < x){
                return contains(x, t->right);
            }else{
                return true;
            }
        }


        /*
            The next part is no different from a binary tree
        */
        void printPreorderTree(BinaryNode *t) const{
            if(t != nullptr){
                std::cout << t->element << " ";
                printPreorderTree(t->left);
                printPreorderTree(t->right);
            }
        }
        void printInorderTree(BinaryNode *t) const{
            if(t != nullptr){
                printInorderTree(t->left);
                std::cout << t->element << " ";
                printInorderTree(t->right);
            }
        }
        void printPostorderTree(BinaryNode *t) const{
            if(t != nullptr){
                printPostorderTree(t->left);
                printPostorderTree(t->right);
                std::cout << t->element << " ";
            }
        }
        int size(BinaryNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                return size(t->left) + 1 +size(t->right);
            }
        }
        int height(BinaryNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                return ( height(t->left) > height(t->right) ? height(t->left) : height(t->right) ) + 1;
            }
        }
        int depth(BinaryNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                return ( depth(t->left) > depth(t->right) ? depth(t->left) : depth(t->right) ) + 1;
            }
        }
        BinaryNode* clone(BinaryNode *t) const{
            if(t == nullptr){
                return nullptr;
            }
            return new BinaryNode(t->element, clone(t->left), clone(t->right));
        }

};

#endif /* SPLAYTREE_H */

