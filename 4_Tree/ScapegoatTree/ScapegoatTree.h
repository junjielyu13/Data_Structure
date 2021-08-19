/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ScapegoatTree.h
 * Author: Junjie_Li
 *
 * Created on August 19, 2021, 12:56 AM
 */

#ifndef SCAPEGOATTREE_H
#define SCAPEGOATTREE_H
#include <iostream>
#include <vector>

template <typename Comparable>
class ScapegoatTree {

    private:
        struct ScapegoatNode{
            Comparable element;
            ScapegoatNode* left;
            ScapegoatNode* right;
            bool exist;

            ScapegoatNode(const Comparable& e, ScapegoatNode* lt = nullptr, ScapegoatNode *rt = nullptr, bool exi = true):
                element(e), left(lt), right(rt), exist(exi){
            }

        };
        

    public:
        ScapegoatTree(){
            root = nullptr;
        }

        bool isEmpty() const{
            return root == nullptr;
        }

        int size() const{
            if(isEmpty()){
                throw std::out_of_range("Exception: Empty Tree.");
            }
            return MarkSize(root);
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

    private:
        ScapegoatNode* root;
        const double alpha = 0.5;  //Impact factor at insert: must be [0.5, 1], 0.5 == AVL, 1 = BST
        const double beta = 0.3;    //Impact factor at remove: must be (0, 1)
        std::vector<Comparable> v;

        void printPreorderTree(ScapegoatNode *t) const{
            if(t != nullptr){
                std::cout << t->element << " ";
                printPreorderTree(t->left);
                printPreorderTree(t->right);
            }
        }
        void printInorderTree(ScapegoatNode *t) const{
            if(t != nullptr){
                printInorderTree(t->left);
                std::cout << t->element << " ";
                printInorderTree(t->right);
            }
        }



        /**
         * Real size:
        */
        int RealSize(ScapegoatNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                return RealSize(t->left) + 1 + RealSize(t->right);
            }
        }
        /**
         * Mark size:
        */
        int MarkSize(ScapegoatNode *t) const{
            if(t == nullptr){
                return 0;
            }else{
                if(t->exist == true){
                    return MarkSize(t->left) + 1 + MarkSize(t->right);
                }else{
                    return MarkSize(t->left) + MarkSize(t->right);
                }
            }
        }


        /**
         * insert:
        */ 
        void insert(const Comparable& x, ScapegoatNode*& t){
            if(t == nullptr){
                t = new ScapegoatNode(x, nullptr, nullptr);
                check(root, t);
                return;
            }else if(x < t->element){
                insert(x, t->left);
            }else if(t->element < x){
                insert(x, t->right);
            }else{
                return; //should be exception
            }
            
        }


        /**
         * remove:
        */
        void remove(const Comparable& x, ScapegoatNode*& t){
            if(t->exist && t->element == x ){
                t->exist = false;
                check(root, t);
                return;
            }else if(x < t->element){
                remove(x, t->left);
            }else{
                remove(x, t->right);
            }
        }



        //check if the tree metts the conditions
        void check(ScapegoatNode*& r, ScapegoatNode*& t){
            if(r == t){
                return;
            }
            if(imbalance(r)){
                rebuild(r);
                return;
            }
            if(t->element < r->element){
                check(r->left, t);
            }else{
                check(r->right, t);
            }

        }

        //The condition that needs to be reconstructed is: 
        //insert:
        //the size of the left or right subtree of the current node is greater
        //than the size of the current node multiplied by a balance factor alpha 
        //remove:
        //or the number of deleted nodes in the subtree rooted at the 
        //current node is greater than 30% of the tree size
        bool imbalance(ScapegoatNode*& t){
            int maxsize = RealSize(t->left) > RealSize(t->right) ? RealSize(t->left) : RealSize(t->right);
            std::cout << "\nt element= "<< t->element << std::endl;
            std::cout << "maxsize = "<< maxsize << std::endl;
            std::cout << "RealSize(t) = "<< RealSize(t) << std::endl;
            std::cout << "RealSize(t)*alpha = "<< RealSize(t)*alpha << std::endl;
            if(maxsize > RealSize(t)*alpha || RealSize(t)-MarkSize(t) > RealSize(t)*beta){
                std::cout << "imbalance"<<std::endl;
                return true;
            }
            return false;
        }

        void rebuild(ScapegoatNode*& t){
            v.clear();
            InorderTree(t);
            for(int i = 0; i<v.size(); i++){
                std::cout << " " << v[i] ; 
            }
            if(v.empty()){
                t = root;
                return;
            }
            RebuildSubtree(0, v.size()-1, t);
        }

        //Get elements from small to large
        void InorderTree(ScapegoatNode* t){
            if(t != nullptr){
                InorderTree(t->left);
                if(t->exist){
                    v.push_back(t->element);
                }
                InorderTree(t->right);
            }
        }

        //Rebuild the subtree with element in vector 
        void RebuildSubtree(int left, int right, ScapegoatNode* t){
            
            std::cout << "rebuildsubtree"<<std::endl;
            if(left == right){ //left node
            std::cout << "left node"<<std::endl;
                t = new ScapegoatNode(v[left]);
                std::cout << "left node"<<std::endl;
                return;
            }
             std::cout << "mid"<<std::endl;
            int mid = (left + right) >> 1;
            std::cout << "mid2"<<std::endl;
            while(left < mid && v[mid] == v[mid-1]){
                mid--;
            }
            std::cout << "mid3"<<std::endl;
            std::cout << "mid v[mid] "<< v[mid] <<std::endl;
            if(t == nullptr){
                t = new ScapegoatNode(v[mid]);
            }
            std::cout << "mid4"<<std::endl;
            if(left < mid){
                 std::cout << "rebuildsubtree left"<<std::endl;
                RebuildSubtree(left, mid-1, t->left);
            }else{
                std::cout << "rebuildsubtree root"<<std::endl;
                t->left = root;
            }
             std::cout << "rebuildsubtree rgiht"<<std::endl;
            RebuildSubtree(mid+1, right, t->right);
             std::cout << "rebuildsubtree finish"<<std::endl;
        }

};

#endif /* SCAPEGOATTREE_H */

