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
        void remove(const Comparable& x){
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            if(!contains()){
                throw std::invalid_argument("Exception: can't find value.");
            }
            return remove(root, x);
        }

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
        

        /**
         * Insert:
        */
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

        

        /**
         *  Remove: 
         */
        void remove(RedBlackNode* t, Comparable x){
            if(x < t->element){
                return remove(t->left, x);
            }else if(t->element < x){
                return remove(t->right, x);
            }else{
                if(p->right == leaf){
                    removechild(t);
                    return;
                }
                RedBlackNode *min = findMin(p->right);
                swap(t->element, min->element);
                removechild(min);
                return;
            }
            return;
        }

        void swap(Comparable &a, Comparable &b){
            Comparable temp = a;
            a = b;
            b = temp;
        }

        void removechild(RedBlackNode* t){
            RedBlackNode* child = t->left == leaf ? t->right : t->left;
            if(t->parent == nullptr && t->left == leaf && t->right == leaf){
                t = nullptr;
                root = t;
                return;
            }

            if(t->parent == nullptr){
                delete t;
                child->parent = nullptr;
                root = child;
                root->color = BLACK;
                return;
            }

            if(t->parent->left == t){
                t->parent->left = child;
            }else{
                t->parent->right = child;
            }
            child->parent = t->parent;

            if(p->color == BLACK){
                if(child->color == RED){
                    child->color = BLACK;
                }else{
                    remove_case(child);
                }
            }
            delete t;
        }

        void remove_case(RedBlackNode* t){
            if(t->parent == nullptr){
                t->color = BLACK;
                return;
            }

            if(t->sibling()->color == RED){
                t->parent->color = RED;
                t->sibling()->color = BLACK;
                if(t == t->parent->left){
                    LeftRotation(t->parent);
                }else{
                    RightRotation(t->parent);
                }
            }

            if(t->parent->color == BLACK && t->sibling()->color == BLACK && t->sibling()->left->color == BLACK && t->sibling()->right->color == BLACK){
                t->sibling()->color = RED;
                remove_case(t->parent);
            }else if(t->parent->color == RED && t->sibling()->color == BLACK && t->sibling()->left->color == BLACK && t->sibling()->right->color == BLACK){
                t->sibling()->color = RED;
                t->parent->color = BLACK;
            }else{
                if(t->sibling()->color == BLACK){
                    if(t == t->parent->left && t->sibling()->left->color == RED && t->sibling()->right->color == BLACK){
                        t->sibling()->color = RED;
                        t->sibling()->left->color = BLACK;
                        RightRotation(t->sibling()->left);
                    }else if(t == t->parent->right && t->sibling()->left->color == BLACK && t->sibling()->right->color == RED){
                        t->sibling()->color = RED;
                        t->sibling()->right->color = BLACK;
                        RightRotation(t->sibling()->right);                        
                    }
                }

                t->sibling()->color = t->parent->color;
                t->parent->color = BLACK;
                if(t == t->parent->left){
                    t->sibling()->right->color = BLACK;
                    LeftRotation(t->sibling());
                }else{
                    t->sibling()->left->color = BLACK;
                    RightRotation(t->sibling());
                }

            }

        }

};

#endif /* REDBLACKTREE_H */

