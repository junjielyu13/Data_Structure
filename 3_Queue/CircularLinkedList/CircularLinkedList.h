/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CircularLinkedList.h
 * Author: Junjie_Li
 *
 * Created on August 1, 2021, 5:51 PM
 */

#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <stdexcept>
#include <iostream>

template <typename Object>
class CircularLinkedList {

    private:
        struct Node{
            Object data;
            Node *next;

            Node(const Object& d = Object(), Node *n = nullptr):
                data(d), next(n){
            }
        };
        

    public:
        CircularLinkedList(){
            _size = 0;
            _head = nullptr;
        }


        CircularLinkedList(const CircularLinkedList& orig){
            _size = 0;
            _head = nullptr;
            *this = orig;
        }


        virtual ~CircularLinkedList(){
            while(!empty()){
                pop();
            }
            delete _head;
        }


        const CircularLinkedList& operator=(const CircularLinkedList& list){
            if (this == &list){
                return *this;
            }

            Node *p = list._head;
            while(p != nullptr){
                this->push(p->data);
                p = p->next;
            }
            delete p;
            return *this;            
        }


        void push(const Object& x){

            Node *p = new Node(x, _head);
            _head = p;
            _size++;

        }

        void pop(){
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }
            Node *p = _head;
            while(p->next->next!=nullptr){
                p = p->next;
            }
            delete p->next;
            p->next = nullptr;
            p->next = _head;   
            _size--;      
        }


        Object& front(){
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }
            return _head->data;
        }
        const Object& front() const{
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }
            return _head->data;
        }


        Object& back(){
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }
            Node *p = _head;
            int i = 0;
            while(p->next != _head && i == (this->_size - 1)){
                p = p->next;
                i++;
            }
            return p->data;
        }

        const Object& back() const{
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }
            Node *p = _head;
            while(p->next != _head){
                p = p->next;
            }
            return p->data;

        }

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

#endif /* CIRCULARLINKEDLIST_H */

