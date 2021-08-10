/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   RedBlackTree.h
 * Author: Junjie_Li
 *
 * Created on August 9, 2021, 10:13 PM
 */

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <stdexcept>

template <typename Comparable>
class RedBlackTree {

    private:
        struct RedBlackNode{
            Comparable    element;
            RedBlackNode  *left;
            RedBlackNode  *right;
            RedBlackNode  *parent;
            int           color;

            RedBlackNode(): element(0), left(nullptr), right(nullptr), parent(nullptr), color(RED){
            }

            RedBlackNode* grandparent(){
                if(parent == nullptr){
                    return nullptr;
                }
                return parent->parent;
            }

            RedBlackNode* uncle(){
                if(grandparent() == nullptr){
                    return nullptr;
                }
                if(parent == grandparent()->right){
                    return grandparent()->left;
                }else{
                    return grandparent()->right;
                }
            }

            RedBlackNode* sibling(){
                if(parent->left == this){
                    return parent->right;
                }else{
                    return parent->left;
                }
            }
        };
        

    public:
        RedBlackTree(){
            leaf = new RedBlackNode();
            leaf->color = BLACK;
            root = nullptr;
        }
        RedBlackTree(const RedBlackTree& orig){
            root = nullptr;
            *this = orig;
        }
        virtual ~RedBlackTree(){
            makeEmpty();
            root = nullptr;
        }
        const RedBlackTree& operator=(const RedBlackTree& orig){
            if(this != &orig){
                makeEmpty();
                root = clone(orig.root);
            }
            return *this;
        }

        const Comparable& findMin() const;
        const Comparable& findMax() const;
        bool contains(const Comparable& x) const;

        bool isEmpty() const{
            return root == nullptr;
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
        
        void makeEmpty(){
            return reclaimMemory(root);
        }
        void insert(const Comparable& x){
            return insert(root, x);
        }
        void remove(const Comparable& x);

    private:
        RedBlackNode *root;
        RedBlackNode *leaf;

        enum { RED = 0, BLACK = 1 };

        void reclaimMemory(RedBlackNode *t){
            if(t != nullptr){
                reclaimMemory(t->left);
                reclaimMemory(t->right);
                delete t;
            }
            t = nullptr; 
        }
        void printPreorderTree(RedBlackNode *t) const{
            if(t != nullptr && t != leaf){
                std::cout << t->element << " ";
                printPreorderTree(t->left);
                printPreorderTree(t->right);
            }
        }
        void printInorderTree(RedBlackNode *t) const{
            if(t != nullptr && t != leaf){
                printInorderTree(t->left);
                std::cout << t->element << " ";
                printInorderTree(t->right);
            }
        }

        
        RedBlackNode* clone(RedBlackNode *t) const{
            if(t == nullptr){
                return nullptr;
            }
            return new RedBlackNode(t->element, clone(t->left), clone(t->right));
        }


        void insert(RedBlackNode* t, Comparable x){
            if(root == nullptr){
                root = new RedBlackNode();
                root->color = BLACK;
                root->left = root->right = leaf;
                root->element = x;
            }else{
                if(x < t->element){
                    if(t->left != leaf){
                        insert(t->left, x);
                    }else{
                        RedBlackNode *temp = new RedBlackNode();
                        temp->element = x;
                        temp->left = temp->right = leaf;
                        temp->parent = t;
                        t->left = temp;
                        insert_case(temp);
                    }
                }else if(t->element < x){
                    if(t->right != leaf){
                        insert(t->right, x);
                    }else{
                        RedBlackNode *temp = new RedBlackNode();
                        temp->element = x;
                        temp->left = temp->right = leaf;
                        temp->parent = t;
                        t->right = temp;
                        insert_case(temp);
                    }
                }else{
                    return;
                }
            }
        }

        void insert_case(RedBlackNode* t){
            if(t->parent == nullptr){
                root = t;
                t->color = BLACK;
                return;
            }

            if(t->parent->color == RED){
                if(t->uncle()->color == RED){
                    t->parent->color = t->uncle()->color = BLACK;
                    t->grandparent()->color = RED;
                    insert_case(t->grandparent());
                }else{
                    if(t->parent->right == t && t->grandparent()->left == t->parent){
                        LeftRotation(t);
                        t->color = BLACK;
                        t->parent->color = RED;
                        RightRotation(t);
                    }else if(t->parent->left == t && t->grandparent()->right == t->parent){
                        RightRotation(t);
                        t->color = BLACK;
                        t->parent->color = RED;
                        LeftRotation(t);
                    }else if(t->parent->left == t && t->grandparent()->left == t->parent){
                        t->parent->color = BLACK;
                        t->grandparent()->color = RED;
                        RightRotation(t->parent);
                    }else if(t->parent->right == t && t->grandparent()->right == t->parent){
                        t->parent->color = BLACK;
                        t->grandparent()->color = RED;
                        LeftRotation(t->parent);
                    }
                }
            }
        }



        void LeftRotation(RedBlackNode* &t){
            if(t->parent == nullptr){
                root = t;
                return;
            }
            RedBlackNode *grandparent = t->grandparent(); 
            RedBlackNode *father = t->parent;  
            RedBlackNode *sibling = t->left;

            father->right = sibling;
            if(sibling != leaf){
                sibling->parent = father;
            }
            t->left = father;
            father->parent = t;

            if(root == father){
                root = t;
            } 
            t->parent = grandparent;

            if(grandparent != nullptr){
                if(grandparent->left == father){
                    grandparent->left = t;
                }else{
                    grandparent->right = t;
                }
            }


        }
        void RightRotation(RedBlackNode* &t){
            if(t->parent == nullptr){
                root = t;
                return;
            }

            RedBlackNode *grandparent = t->grandparent(); 
            RedBlackNode *father = t->parent;  
            RedBlackNode *sibling = t->right;

            father->left = sibling;
            if(sibling != leaf){
                sibling->parent = father; 
            }
            t->right = father;
            father->parent = t;

            if(root == father){
                root = t;
            }
            t->parent = grandparent;

            if(grandparent != nullptr){
                if(grandparent->left == father){
                    grandparent->left = t;
                }else{
                    grandparent->right = t;
                }
            }

        }


};

#endif /* REDBLACKTREE_H */

