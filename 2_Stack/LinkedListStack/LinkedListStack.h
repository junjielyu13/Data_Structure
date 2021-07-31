/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LinkedListStack.h
 * Author: Junjie_Li
 *
 * Created on July 31, 2021, 10:43 PM
 */

#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H

#include <stdexcept>

template <typename Object>
class LinkedListStack {

    private:
        struct Node{
            Object data;
            Node *next;

            Node(const Object& d = Object(), Node *n = nullptr):
                data(d), next(n){
            }
        };
        

    public:
        LinkedListStack(){
            _size = 0;
            _top = nullptr;
        }


        LinkedListStack(const LinkedListStack& orig){
            *this = orig;
        }


        virtual ~LinkedListStack(){
            while(empty()){
                pop();
            }
        }


        void push(const Object& x){
            Node* p = new Node(x, _top);
            _top = p;
            _size++;
        }


        void pop(){
            if(empty()){
                throw std::invalid_argument("Exception: out_of_range.");
            }   
            
            Node *p = _top;
            _top = p->next;
            delete p;
            _size--;
        }


        Object& top(){
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }   
            return _top->data;
        }
        const Object& top() const{
            if(empty()){
                throw std::out_of_range("Exception: out_of_range.");
            }   
            return _top->data;
        }


        int size() const{
            return _size;
        }
        bool empty() const{
            return _top == nullptr;
        }

    private:
        int _size;
        Node *_top;

};

#endif /* LINKEDLISTSTACK_H */

