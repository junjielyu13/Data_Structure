/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTree.h
 * Author: Junjie_Li
 *
 * Created on August 4, 2021, 5:55 PM
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <stdexcept>
#include <iostream>
#include "BinaryTree.h"

template <typename Comparable>

class AVLTree : protected BinaryTree<Comparable>{

    public:
        AVLTree(){
            avlRoot = nullptr;
        }
        AVLTree(const AVLTree& orig){
            avlRoot = nullptr;
            *this = orig;
        }
        virtual ~AVLTree(){
            makeEmpty();
        }
        const AVLTree& operator=(const AVLTree& tree){
            if(this != &tree){
                makeEmpty();
                avlRoot = clone(tree.avlRoot);
            }
            return *this;
        }


        const Comparable& findMin() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return BinaryTree<Comparable>::findMin(avlRoot)->element;
        }
        const Comparable& findMax() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return BinaryTree<Comparable>::findMax(avlRoot)->element;
        }


        bool contains(const Comparable& x) const{
            return BinaryTree<Comparable>::contains(x, avlRoot);
        }
        bool isEmpty() const{
            return avlRoot == nullptr;
        }
        int size() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return BinaryTree<Comparable>::size(avlRoot);
        }
        int height() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return BinaryTree<Comparable>::height(avlRoot);
        }
        int depth() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return BinaryTree<Comparable>::depth(avlRoot);
        }


        void printPreorderTree() const{
            BinaryTree<Comparable>::printPreorderTree(avlRoot);
        }
        void printInorderTree() const{
            BinaryTree<Comparable>::printInorderTree(avlRoot);
        }
        void printPostorderTree() const{
            BinaryTree<Comparable>::printPostorderTree(avlRoot);
        }


        void makeEmpty(){
            BinaryTree<Comparable>::makeEmpty(avlRoot);
        }

        void insert( const Comparable& x){
            insert(x, avlRoot);
        }
        void remove( const Comparable& x){

        }

    private:
        BinaryNode* avlRoot;

        BinaryNode* clone(BinaryNode *t) const{
            return BinaryTree<Comparable>::clone(avlRoot);
        }

        void LeftLeftRotation(BinaryNode* &t){
            BinaryNode* lt = t->left;
            t->left = lt->left;
            lt->right = t; 
            t = tl;
        }
        void RightRightRotation(BinaryNode* &t){
            BinaryNode* rt = t->right;
            t->right = rt->left;
            rt->left = t; 
            t = rt;
        }
        void LeftRightRotation(BinaryNode* &t){
            RightRightRotation(t->left);
            LeftLeftRotation(t);
        }
        void RightLeftRotation(BinaryNode* &t){
            LeftLeftRotation(t->right);
            RightRightRotation(t);
        }

        //return the height of node t or -1 if null;
        int NodeHeight(BinaryNode *t){
            return BinaryTree<Comparable>::height(t);
        }

        void insert(const Comparable& x, BinaryNode *&t){
            if(t == nullptr){
                t = new BinaryNode(x, nullptr, nullptr);
            }else if(x < t->element){
                insert(x, t->left);
                if(NodeHeight(t->left) - NodeHeight(t->right) == 2){
                    if( x < t->left->element){
                        LeftLeftRotation(t);
                    }else{
                        LeftRightRotation(t);
                    }
                }
            }else if(t->element < x){
                insert(x, t->right);
                if(NodeHeight(t->right) - NodeHeight(t->left) == 2){
                    if(t->left->element < x){
                        RightRightRotation(t);
                    }else{
                        RightLeftRotation(t);
                    }
                }
            }else{
                throw std::invalid_argument("Exception: Duplicate valor.");
            }
        }


};

#endif /* AVLTREE_H */

