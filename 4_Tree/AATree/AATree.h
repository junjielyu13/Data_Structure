/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AATree.h
 * Author: Junjie_Li
 *
 * Created on August 18, 2021, 6:01 PM
 */

#ifndef AATREE_H
#define AATREE_H
#include <iostream>

template <typename Comparable>
class AATree {

    struct AANode{
        Comparable element;
        AANode* left;
        AANode* right;
        int level;

        AANode(): left(nullptr), right(nullptr), level(1){
        }

        AANode(const Comparable& e, AANode* lt, AANode *rt, int lv = 1):
            element(e), left(lt), right(rt), level(lv){
        }
    };
    
    

    public:
        AATree(){
            nullnode = new AANode;
            nullnode->left = nullnode->right = nullnode;
            nullnode->level = 0;
            root = nullnode;
        }

        int height() const{
            return root->level;
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



        /**
         * insert:
        */
        void insert(const Comparable& x){
            return insert(x, root);
        }

        /**
         * remove:
        */
        void remove(const Comparable& x){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return remove(x,root);
        }




        /**
         * Everything else is exactly the same as the BST
         * (omitted)
        */
        
    


    private:
        AANode* root;
        AANode* nullnode;

        void insert(const Comparable& x, AANode*& t){
            if(t == nullnode){
                t = new AANode(x, nullnode, nullnode);
            }else if(x < t->element){
                insert(x, t->left);
            }else if(t->element < x){
                insert(x, t->right);
            }else{
                return; //should be exception
            }
            skew(t);
            split(t);
        }


        void remove(const Comparable& x, AANode*& t){
            static AANode* lastNode, *deletedNode = nullnode;

            if(t != nullnode){
                // search down the tree and set lastNode and deletedNode
                lastNode = t;
                if(x < t->element){
                    remove(x, t->left);
                }else{
                    deletedNode = t;
                    remove(x, t->right);
                }
                if(t == lastNode){  //if at the bottom of the tree and x is present, we remove it
                    if(deletedNode == nullnode || x != deletedNode->element){
                        return; //item not found, do nothing; return
                    }
                    deletedNode->element = t->element;
                    deletedNode = nullnode;
                    t = t->right;
                    delete lastNode;
                }else{  //otherwise, we are not at the bottom; rebalance
                    if(t->left->level < t->level -1 || t->right->level < t->level -1){
                        if(t->right->level > --t->level){
                            t->right->level = t->level;
                        }
                        skew(t);
                        skew(t->right);
                        skew(t->right->right);
                        split(t);
                        split(t->right);
                    }
                }
            }
        }

        /**
         * Skew:
         * removes a left horizontal link
        */
        void skew(AANode*& t){
            if(t->left->level == t->level){
                LeftChildRotation(t);
            }
        }


        /**
         * Split:
         * remove a right horizontal link
        */
        void split(AANode*& t){
            if(t->right->right->level == t->level){
                RightChildRotation(t);
                t->level++;
            }
        }


        void LeftChildRotation(AANode* &t){
            AANode* tl = t->left;
            t->left = tl->right;
            tl->right = t; 
            t = tl;
        }
        void RightChildRotation(AANode* &t){
            AANode* tr = t->right;
            t->right = tr->left;
            tr->left = t; 
            t = tr;
        }








        void printPreorderTree(AANode *t) const{
            if(t != nullnode){
                std::cout << t->element << " ";
                printPreorderTree(t->left);
                printPreorderTree(t->right);
            }
        }
        void printInorderTree(AANode *t) const{
            if(t != nullnode){
                printInorderTree(t->left);
                std::cout << t->element << " ";
                printInorderTree(t->right);
            }
        }

};

#endif /* AATREE_H */

