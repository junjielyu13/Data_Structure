/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SimpleLinkedList.h
 * Author: Junjie_Li
 *
 * Created on July 31, 2021, 11:35 PM
 */

#ifndef SIMPLELINKEDLIST_H
#define SIMPLELINKEDLIST_H

#include <stdexcept>

template <typename Object>
class SimpleLinkedList {

    private:
        struct Node{
            Object data;
            Node *next;

            Node(const Object& d = Object(), Node *n = nullptr):
                data(d), next(n){
            }
        };
        
    public:
        SimpleLinkedList();
        SimpleLinkedList(const SimpleLinkedList& orig);
        virtual ~SimpleLinkedList();

        void push(const Object& x)
        void pop();

        Object& front();
        const Object& front() const;
        
        Object& back();
        const Object& back() const;


        int size() const{
            return _size;
        }
        bool empty() const{
            return _head == nullptr;
        }

    private:
        int _size;
        Node* _head;
        

};

#endif /* SIMPLELINKEDLIST_H */

