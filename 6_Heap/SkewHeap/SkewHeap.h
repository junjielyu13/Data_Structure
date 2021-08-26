/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SkewHeap.h
 * Author: Junjie_Li
 *
 * Created on August 26, 2021, 6:20 PM
 */
#include <stdexcept>
#include <iostream>
#include <stack>

using namespace std;

#ifndef SKEWHEAP_H
#define SKEWHEAP_H

template <typename Comparable>
class SkewHeap {

    public:
        SkewHeap(){
            root = nullptr;
        }
        SkewHeap(const SkewHeap& orig){
            root = nullptr;
            *this = orig;
        }
        virtual ~SkewHeap(){
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
            root = merge(new SkewtNode(x), root);
        }
        /**
         * Remove the minimum item.
        */
        void deleteMin(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Underflow");
            }
            SkewtNode* oldRoot = root;
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
        void merge(SkewHeap& rhs){
            if(this == &rhs){
                return;
            }
            root = merge(root, rhs.root);
            rhs.root = nullptr;
        }

        const SkewHeap& operator=(const SkewHeap& rhs){
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
            std::stack<SkewtNode*> s;
            SkewtNode *p = root;
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
            std::stack<SkewtNode*> s;
            SkewtNode *p = root;
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
        struct SkewtNode{
            Comparable   element;
            SkewtNode* left;
            SkewtNode* right;

            SkewtNode(const Comparable& theElement, SkewtNode* lt = nullptr, SkewtNode* rt = nullptr):
                element(theElement), left(lt), right(rt){
            }
        };


        SkewtNode* root;


        /**
         * Internal method to merge two roots.
         * Deals with deviant cases and calls recursive mergel
        */
        SkewtNode* merge(SkewtNode* h1, SkewtNode* h2){
            if(h1 == nullptr){
                return h2;
            }
            if(h2 == nullptr){
                return h1;
            }
            if(h1->element > h2->element){
                swap(h1,h2);
            }
            swap(h1->left, h1->right);
            h1->left = merge(h2,h1->left);
            return h1;
        }

        void swap(SkewtNode*& h1, SkewtNode*& h2){
            SkewtNode* temp = h1;
            h1 = h2;
            h2 = temp;
        }

        void reclaiMemory(){
            while (!isEmpty()){
                deleteMin();
            }
        }
        SkewtNode* clone(SkewtNode* t)const{
            if(t == nullptr){
                return nullptr;
            }
            return new SkewtNode(t->element, clone(t->left), clone(t->right));
        }


};

#endif /* SKEWHEAP_H */

