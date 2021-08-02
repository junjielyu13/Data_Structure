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
        SimpleLinkedList(){
            _size = 0;
            _head = nullptr;
            _tail = nullptr;
        }


        SimpleLinkedList(const SimpleLinkedList& orig){
            _size = 0;
            _head = nullptr;
            _tail = nullptr;
            *this = orig;
        }


        virtual ~SimpleLinkedList(){
            while(!empty()){
                pop();
            }
            delete _head;
        }

        
        const SimpleLinkedList& operator=(const SimpleLinkedList& list){
            if (this == &list){
                return *this;
            }

            Object aux[list._size];
            int pos = 0;
            Node *p = list._head;
            while(p != nullptr){
                aux[pos] = p->data;
                p = p->next;
                pos++;
            }
            for(int i=pos; i>0; i--){
                this->push(aux[i]);
            }
            delete p;
            return *this;     
        }


        void push(const Object& x){
            if(_head == nullptr){
                Node *p = new Node(x, nullptr);
                _head = p;
                _tail = p;
            }else{
                Node *p = new Node(x, _head);
                _head = p;
            }
            _size++;

        }


        void pop(){
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }
            Node *p = _head;
            if(_head == _tail){
                delete _tail;
                _tail = nullptr;
                _head = nullptr;
            }else{
                while(p->next != _tail){
                    p = p->next;
                }
                delete _tail;
                _tail = p;  
            }
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
            return _tail->data;
        }
        const Object& back() const{
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }
            return _tail->data;
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
        Node* _tail;
        

};

#endif /* SIMPLELINKEDLIST_H */

