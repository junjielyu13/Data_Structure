/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Treap.h
 * Author: Junjie_Li
 *
 * Created on August 19, 2021, 10:23 PM
 */

#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <stdlib.h>
#include <time.h> 

template <typename Comparable>
class Treap {

    struct TreapNode{
        Comparable element;
        TreapNode* left;
        TreapNode* right;
        int priority;

        TreapNode(): left(nullptr), right(nullptr), priority(INT_MAX){
        }

        TreapNode(const Comparable& e, TreapNode* lt, TreapNode* rt, int pr):
            element(e), left(lt), right(rt), priority(pr){
        }
    };
    

    public:
        Treap(){
            nullnode = new TreapNode();
            nullnode->left = nullnode->right = nullnode;
            nullnode->priority = INT_MAX;
            root = nullnode;
        }
        bool isEmpty() const{
            return root == nullnode;
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


        void insert(const Comparable& x){
            return insert(x, root);
        }

        void remove(const Comparable& x){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return remove(x, root);
        }

        /**
         * Everything else is exactly the same as the BST
         * (omitted)
        */
    
    private:
        TreapNode* root;
        TreapNode* nullnode;


        /**
         * insert:
        */
        void insert(const Comparable& x, TreapNode*& t){
            if(t == nullnode){
                int numrand = rand();
                t = new TreapNode(x, nullnode, nullnode, numrand);
                std::cout << "  num rand = "<< numrand << std::endl;
            }else if(x < t->element){
                insert(x, t->left);
                if(t->left->priority < t->priority){
                    LeftChildRotation(t);
                }
            }else if(t->element < x){
                insert(x, t->right);
                if(t->right->priority < t->priority){
                    RightChildRotation(t);
                }
            }else{
                std::cout << "Test duplicat"<<std::endl;
                return;
            }
        }


        /**
         * remove:
        */
        void remove(const Comparable& x, TreapNode*& t){
            if(t != nullnode){
                if(x < t->element){
                    remove(x, t->left);
                }else if(t->element < x){
                    remove(x, t->right);
                }else{
                    if(t->left->priority < t->right->priority){
                        LeftChildRotation(t);
                    }else{
                        RightChildRotation(t);
                    }

                    if(t != nullnode){
                        remove(x, t);
                    }else{
                        delete t->left;
                        t->left = nullnode;
                    }
                }
            }
        }


        void LeftChildRotation(TreapNode* &t){
            TreapNode* tl = t->left;
            t->left = tl->right;
            tl->right = t; 
            t = tl;
        }
        void RightChildRotation(TreapNode* &t){
            TreapNode* tr = t->right;
            t->right = tr->left;
            tr->left = t; 
            t = tr;
        }


        void printPreorderTree(TreapNode *t) const{
            if(t != nullnode){
                std::cout << t->element << " ";
                printPreorderTree(t->left);
                printPreorderTree(t->right);
            }
        }
        void printInorderTree(TreapNode *t) const{
            if(t != nullnode){
                printInorderTree(t->left);
                std::cout << t->element << " ";
                printInorderTree(t->right);
            }
        }


        

};

#endif /* TREAP_H */

