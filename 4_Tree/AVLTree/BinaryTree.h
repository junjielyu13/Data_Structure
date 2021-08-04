/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinaryTree.h
 * Author: Junjie_Li
 *
 * Created on August 3, 2021, 5:12 PM
 */

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdexcept>
#include <iostream>

template <typename Comparable>
class BinaryTree {

    protected:
        struct BinaryNode{
            Comparable element;
            BinaryNode *left;
            BinaryNode *right;

            BinaryNode(const Comparable& theElement, BinaryNode *lt, BinaryNode *rt):
                element(theElement), left(lt), right(rt){
            }
        };

    public:
        BinaryTree(){
            root = nullptr;
        }
        BinaryTree(const BinaryTree& orig){
            root = nullptr;
            *this = orig;
        }
        virtual ~BinaryTree(){
            makeEmpty();
        }

        //deep copy;
        const BinaryTree& operator=(const BinaryTree& tree){
            if(this != &tree){
                makeEmpty();
                root = clone(tree.root);
            }
            return *this;
        }

        const Comparable& findMin() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return findMin(root)->element;
        }
        const Comparable& findMax() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return findMax(root)->element;
        }
        bool contains(const Comparable& x) const{
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
            return makeEmpty(root);
        }
        void insert( const Comparable& x){
            return insert(x, root);
        }
        void remove( const Comparable& x){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return remove(x, root);
        }


    protected:
        BinaryNode *root;


        void insert(const Comparable& x, BinaryNode* &t) const{
            if(t == nullptr){
                t = new BinaryNode(x, nullptr, nullptr);
            }else if(x < t->element){
                insert(x, t->left);
            }else if(t->element < x){
                insert(x, t->right);
            }else{
                throw std::invalid_argument("Exception: Duplicate valor.") ;
            }
        }

        void remove(const Comparable& x, BinaryNode* &t) const{
            if(t == nullptr){
                return;     //item not found; do nothing
            }
            if(x < t->element){
                remove(x, t->left);
            }else if(t->element < x){
                remove(x, t->right);
            }else if(t->left != nullptr && t->right != nullptr){    //Two children
                t->element = findMin(t->right)->element;
                remove(t->element, t->right);
            }else{
                BinaryNode *oldNode = t;
                t = (t->left != nullptr) ? t->left : t->right;
                delete oldNode;
            }
        }

        BinaryNode* findMin(BinaryNode* t) const{
            if(t == nullptr){
                return nullptr;
            }
            if(t->left == nullptr){
                return t;
            }
            return findMin(t->left);
        }
        BinaryNode* findMax(BinaryNode* t) const{
            if(t != nullptr){
                while(t->right != nullptr){
                    t = t->right;
                }
            }
            return t;
        }

        bool contains(const Comparable& x, BinaryNode* t) const{
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

        void makeEmpty(BinaryNode* &t) const{
            if(t != nullptr){
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
            t = nullptr; 
        }

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

#endif /* BINARYTREE_H */

