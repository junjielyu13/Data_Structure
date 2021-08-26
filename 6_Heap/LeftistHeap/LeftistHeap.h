/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LeftistHeap.h
 * Author: Junjie_Li
 *
 * Created on August 25, 2021, 10:11 PM
 */

#include <stdexcept>
#include <iostream>
#include <stack>

using namespace std;

#ifndef LEFTISTHEAP_H
#define LEFTISTHEAP_H

template <typename Comparable>
class LeftistHeap {

    public:
        LeftistHeap(){
            root = nullptr;
        }
        LeftistHeap(const LeftistHeap& orig){
            root = nullptr;
            *this = orig;
        }
        virtual ~LeftistHeap(){
            makeEmpty();
            root = nullptr;
        }

        bool isEmpty()const{
            return root == nullptr;
        }
        const Comparable& findMin()const{
            return root->element;
        }

        void insert(const Comparable& x){
            root = merge(new LeftistNode(x), root);
        }
        /**
         * Remove the minimum item.
        */
        void deleteMin(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Underflow");
            }
            LeftistNode* oldRoot = root;
            root = merge(root->left, root->right);
            delete oldRoot;
        }
        /**
         * Remove the minimum item and place it in minItem
        */
        void deleteMin(Comparable& minItem){
            minItem = findMin();
            deleteMin();
        }
        void makeEmpty(){
            reclaiMemory();
        }

        /**
         * Merge rhs into the priority queue
         * rhs becomes empty. rhs must be different from this.
        */
        void merge(LeftistHeap& rhs){
            if(this == &rhs){
                return;
            }
            root = merge(root, rhs.root);
            rhs.root = nullptr;
        }

        const LeftistHeap& operator=(const LeftistHeap& rhs){
            if(this != &rhs){
                makeEmpty();
                root = clone(rhs.root);
            }
            return *this;
        }


        void printPreorderTree(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            std::stack<LeftistNode*> s;
            LeftistNode *p = root;
            while(p!= nullptr || !s.empty()){
                if(p != nullptr){
                    std::cout << p->element << " ";
                    s.push(p);
                    p = p->left;
                }else{
                    p = s.top();
                    s.pop();
                    p = p->right;
                }
            }
        }

        void printInorderTree(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            std::stack<LeftistNode*> s;
            LeftistNode *p = root;
            while(p!= nullptr || !s.empty()){
                if(p != nullptr){
                    s.push(p);
                    p = p->left;
                }else{
                    p = s.top();
                    std::cout << p->element << " ";
                    s.pop();
                    p = p->right;
                }
            }
        }

    
    private:
        struct LeftistNode{
            Comparable   element;
            LeftistNode* left;
            LeftistNode* right;
            int          npl;        //null path length

            LeftistNode(const Comparable& theElement, LeftistNode* lt = nullptr, LeftistNode* rt = nullptr, int np = 0):
                element(theElement), left(lt), right(rt), npl(np){
            }
        };


        LeftistNode* root;

        /**
         * Internal method to merge two roots.
         * Deals with deviant cases and calls recursive mergel
        */
        LeftistNode* merge(LeftistNode* h1, LeftistNode* h2){
            if(h1 == nullptr){
                return h2;
            }
            if(h2 == nullptr){
                return h1;
            }
            if(h1->element < h2->element){
                return merge1(h1,h2);
            }else{
                return merge1(h2,h1);
            }
        }
        /**
         * Internal method to merge two roots.
         * Assumes trees are not empty, and h1's root contains smallest item.
        */
        LeftistNode* merge1(LeftistNode* h1, LeftistNode* h2){
            if(h1->left == nullptr){    //single node
                h1->left = h2;          //Other fields in h1 already accurate
            }else{
                h1->right = merge(h1->right, h2);
                if(h1->left->npl < h1->right->npl){
                    swapChildren(h1);
                }
                h1->npl = h1->right->npl+1;
            }
            return h1;
        }

        /**
         * Swaps t's two children.
        */
        void swapChildren(LeftistNode* t){
            LeftistNode* temp = t->left;
            t->left = t->right;
            t->right = temp;
        }

        void reclaiMemory(){
            while (!isEmpty()){
                deleteMin();
            }
        }
        LeftistNode* clone(LeftistNode* t)const{
            if(t == nullptr){
                return nullptr;
            }
            return new LeftistNode(t->element, clone(t->left), clone(t->right));
        }
        
};

#endif /* LEFTISTHEAP_H */

