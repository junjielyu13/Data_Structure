/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArrayQueue.h
 * Author: Junjie_Li
 *
 * Created on July 31, 2021, 10:08 PM
 */

#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include <stdexcept>

template <typename Object>
class ArrayQueue {

    public:

        explicit ArrayQueue(){
            _size = 0;
            objects = new Object[_size + 1];
        }


        ArrayQueue(const ArrayQueue& orig): objects(nullptr){
            if(this != &orig){
                delete []objects;
                this->_size = orig._size;
                
                this->objects = new Object[_size + 1];
                for(int i=0; i<_size+1; i++){
                    objects[i] = orig.objects[i];
                }
            }
        }


        virtual ~ArrayQueue(){
            delete []objects;
        }

        void push(const Object& x){
            Object *oldArray = this->objects;
            objects = new Object[_size + 1];

            for(int i=0; i<_size + 1; i++){
                objects[i + 1] = oldArray[i];
            }
            objects[0] = x;
            _size++;
            delete []oldArray;

        }


        void pop(){
            if(this->empty()){
                throw std::out_of_range("Exception: out_of_range");
            }
            --_size;
        }


        Object& front(){
            return objects[0];
        }
        const Object& front() const{
            return objects[0];
        }
        Object& back(){
            return objects[_size - 1];
        }
        const Object& back() const{
            return objects[_size - 1];
        }


        int size() const{
            return _size;
        }
        bool empty() const{
            return _size < 1;
        }

    private:
        int _size;
        Object *objects;

};

#endif /* ARRAYQUEUE_H */

