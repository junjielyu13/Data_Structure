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

template <typename Comparable>
class AVLTree{

    private:
        struct AVLNode{
            Comparable element;
            AVLNode *left;
            AVLNode *right;

            AVLNode(const Comparable& theElement, AVLNode *lt, AVLNode *rt):
                element(theElement), left(lt), right(rt){
            }
        };

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
            return findMin(avlRoot)->element;
        }
        const Comparable& findMax() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return findMax(avlRoot)->element;
        }


        bool contains(const Comparable& x) const{
            return contains(x, avlRoot);
        }
        bool isEmpty() const{
            return avlRoot == nullptr;
        }
        int size() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return size(avlRoot);
        }
        int height() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return height(avlRoot);
        }
        int depth() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return depth(avlRoot);
        }


        void printPreorderTree() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printPreorderTree(avlRoot);
        }
        void printInorderTree() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printInorderTree(avlRoot);
        }
        void printPostorderTree() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printPostorderTree(avlRoot);
        }


        void makeEmpty(){
            return makeEmpty(avlRoot);
        }

        void insert( const Comparable& x){
            return insert(x, avlRoot);
        }
        void remove( const Comparable& x){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return remove(x, avlRoot);
        }

    private:
        AVLNode* avlRoot;

        AVLNode* clone(AVLNode *t) const{
            if(t == nullptr){
                return nullptr;
            }
            return new AVLNode(t->element, clone(t->left), clone(t->right));
        }

        void LeftLeftRotation(AVLNode* &t){
            AVLNode* tl = t->left;
            t->left = tl->right;
            tl->right = t; 
            t = tl;
        }
        void RightRightRotation(AVLNode* &t){
            AVLNode* tr = t->right;
            t->right = tr->left;
            tr->left = t; 
            t = tr;
        }
        void LeftRightRotation(AVLNode* &t){
            RightRightRotation(t->left);
            LeftLeftRotation(t);
        }
        void RightLeftRotation(AVLNode* &t){
            LeftLeftRotation(t->right);
            RightRightRotation(t);
        }


        void insert(const Comparable& x, AVLNode*& t){
            if(t == nullptr){
                t = new AVLNode(x, nullptr, nullptr);
            }else if(x < t->element){
                insert(x, t->left);
                if(height(t->left) - height(t->right) == 2){
                    if( x < t->left->element){
                        LeftLeftRotation(t);
                    }else{
                        LeftRightRotation(t);
                    }
                }
            }else if(t->element < x){
                insert(x, t->right);
                if(height(t->right) - height(t->left) == 2){
                    if(t->right->element < x){
                        RightRightRotation(t);
                    }else{
                        RightLeftRotation(t);
                    }
                }
            }else{
                throw std::invalid_argument("Exception: Duplicate valor.");
            }
        }

        void remove(const Comparable& x, AVLNode* &t){
            if(x < t->element){
                remove(x, t->left);
                if(height(t->right) - height(t->left) == 2){
                    if(height(t->right->right) > height(t->right->left)){
                        RightLeftRotation(t);
                    }else{
                        RightRightRotation(t);
                    }
                }
            }else if(t->element < x){
                remove(x, t->right);
                if(height(t->left) - height(t->right) == 2){
                    if( height(t->left->right) > height(t->left->left) ){
                        LeftRightRotation(t);
                    }else{
                        LeftLeftRotation(t);
                    }
                }
            }else{
                if(t->left != nullptr && t->right != nullptr){
                    if(height(t->left) > height(t->right)){
                        // if left is higher than right
                        // find the max node in the left
                        t->element = findMax(t->left)->element;
                        remove(t->element, t->left);
                    }else{
                        // if left is shorter that right
                        // find the min node in the right
                        t->element = findMin(t->right)->element;
                        remove(t->element, t->right);
                    }
                }else{
                    AVLNode *oldNode = t;
                    t = (t->left != nullptr) ? t->left : t->right;
                    delete oldNode;
                }
            }
        }


        /*
            The next part is no different from a binary tree
        */
       
        AVLNode* findMin(AVLNode* t) const{
            if(t == nullptr){
                return nullptr;
            }
            if(t->left == nullptr){
                return t;
            }
            return findMin(t->left);
        }
        AVLNode* findMax(AVLNode* t) const{
            if(t != nullptr){
                while(t->right != nullptr){
                    t = t->right;
                }
            }
            return t;
        }

        bool contains(const Comparable& x, AVLNode* t) const{
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

        void makeEmpty(AVLNode* &t) const{
            if(t != nullptr){
                makeEmpty(t->left);
                makeEmpty(t->right);
                delete t;
            }
            t = nullptr; 
        }

        void printPreorderTree(AVLNode* t) const{
            if(t != nullptr){
                std::cout << t->element << " ";
                printPreorderTree(t->left);
                printPreorderTree(t->right);
            }
        }
        void printInorderTree(AVLNode* t) const{
            if(t != nullptr){
                printInorderTree(t->left);
                std::cout << t->element << " ";
                printInorderTree(t->right);
            }
        }
        void printPostorderTree(AVLNode *t) const{
            if(t != nullptr){
                printPostorderTree(t->left);
                printPostorderTree(t->right);
                std::cout << t->element << " ";
            }
        }

        int size(AVLNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                return size(t->left) + 1 +size(t->right);
            }
        }

        int height(AVLNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                return ( height(t->left) > height(t->right) ? height(t->left) : height(t->right) ) + 1;
            }
        }

        int depth(AVLNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                return ( depth(t->left) > depth(t->right) ? depth(t->left) : depth(t->right) ) + 1;
            }
        }

};

#endif /* AVLTREE_H */

