/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stack.h
 * Author: Junjie_Li
 *
 * Created on July 30, 2021, 10:50 PM
 */

#ifndef STACK_H
#define STACK_H

#include <stdexcept>


template <typename Object>
class Stack {

    public:

        explicit Stack(){
            this->_top = -1;
            this->capacity = 0;
            this->objects = new Object[capacity];
        }


        Stack(const Stack& orig): objects(nullptr){
            this->operator=(orig);
        }


        virtual ~Stack(){
            delete []objects;
        }


        const Stack& operator=(const Stack &stack){
            if(this != &stack){
                delete []objects;
                this->_top = stack._top;
                this->capacity = stack.capacity;

                this->objects = new Object[this->capacity];
                for(int i=0; i<this->size(); i++){
                    objects[i] = stack.objects[i];
                }
            }
        }


        void push(const Object& x){

            Object *oldArray = this->objects;
            
            this->capacity++;
            objects = new Object[capacity];

            for(int i=0; i<this->size(); i++){
                objects[i] = oldArray[i];
            }
            objects[++_top] = x;
            delete []oldArray;

        }
        

        void pop(){
            if(this->empty()){
                throw std::out_of_range("Exception: out_of_range");
            }
            --_top;
        }


        const Object& top() const{
            if(this->empty()){
                throw std::out_of_range("Exception: out_of_range");
            }
            return objects[this->_top];
        }


        int size() const{
            return _top + 1;
        }


        bool empty() const{
            return this->_top < 0;
        }


    private:
        int _top;
        int capacity;
        Object* objects;

};

#endif /* STACK_H */

