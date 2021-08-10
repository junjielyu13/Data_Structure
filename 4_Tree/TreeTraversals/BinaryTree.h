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
#include <stack>
#include <queue>

template <typename Comparable>
class BinaryTree {

    private:
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

        bool isEmpty() const{
            return root == nullptr;
        }

        //insert do not use recursion
        void insert(const Comparable& x){
            if(root == nullptr){
                root = new BinaryNode(x, nullptr, nullptr);
                return;
            }
            BinaryNode *temp = root;
            while(temp != nullptr){
                if(x < temp->element){
                    if(temp->left == nullptr){
                        temp->left = new BinaryNode(x, nullptr, nullptr);
                        return;
                    }else{
                        temp = temp->left;
                    }
                }else if(temp->element < x){
                    if(temp->right == nullptr){
                        temp->right = new BinaryNode(x, nullptr, nullptr);
                        return;
                    }else{
                        temp = temp->right;
                    }
                }else{
                    return;  //same value, should be exception
                }
            }
        }



        /**
         * Depth-Frist Traversals:
        */  

        //Use recursion
        void printPreorderTreeRecursion() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printPreorderTreeRecursion(root);
        }
        void printInorderTreeRecursion() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printInorderTreeRecursion(root);
        }
        void printPostorderTreeRecursion() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return printPostorderTreeRecursion(root);
        }

        //Do not user recursion
        void printPreorderTreeNoRecursion(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            std::stack<BinaryNode*> s;
            BinaryNode *p = root;
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

        void printInorderTreeNoRecursion(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            std::stack<BinaryNode*> s;
            BinaryNode *p = root;
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

        void printPostorderTreeNoRecursion(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            std::stack<BinaryNode*> s;
            BinaryNode *p = root;
            BinaryNode *temp = nullptr;
            while(p!= nullptr || !s.empty()){
                if(p != nullptr){
                    s.push(p);
                    p = p->left;
                }else{
                    p = s.top();
                    if(p->right != nullptr && p->right != temp){
                        p = p->right;
                    }else{
                        std::cout << p->element << " ";
                        s.pop();
                        temp = p;
                        p = nullptr;
                    }
                }
            }
        }


        /**
         * Breadth-First Traversals:
        */
        void printBreadthFirstTraversal(){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            std::queue<BinaryNode*> q;
            q.push(root);
            while(!q.empty()){
                BinaryNode *node = q.front();
                std::cout << node->element << " ";
                q.pop();

                if(node->left != nullptr){
                    q.push(node->left);
                }
                if(node->right != nullptr){
                    q.push(node->right);
                }
            }


        }

    private:
        BinaryNode *root;

        void printPreorderTreeRecursion(BinaryNode *t) const{
            if(t != nullptr){
                std::cout << t->element << " ";
                printPreorderTreeRecursion(t->left);
                printPreorderTreeRecursion(t->right);
            }
        }
        void printInorderTreeRecursion(BinaryNode *t) const{
            if(t != nullptr){
                printInorderTreeRecursion(t->left);
                std::cout << t->element << " ";
                printInorderTreeRecursion(t->right);
            }
        }
        void printPostorderTreeRecursion(BinaryNode *t) const{
            if(t != nullptr){
                printPostorderTreeRecursion(t->left);
                printPostorderTreeRecursion(t->right);
                std::cout << t->element << " ";
            }
        }


};

#endif /* BINARYTREE_H */

