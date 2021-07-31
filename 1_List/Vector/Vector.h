

/* 
 * File:   Vector.h
 * Author: Junjie_Li
 *
 * Created on July 30, 2021, 5:57 PM
 */

#ifndef VECTOR_H
#define VECTOR_H

template <typename Object>
class Vector {

    public:

        explicit Vector(int initSize = 0): _size(initSize), _capacity(initSize + SPARE_CAPACITY){
            this->objects = new Object[_capacity];
        }


        Vector(const Vector& orig): objects(nullptr){
            this->operator=(orig);
        }


        virtual ~Vector(){
            delete []objects;
        }


        const Vector& operator=(const Vector &vector){
            if(this != &vector){
                delete []objects;
                this->_size = vector.size();
                this->_capacity = vector.capacity();
                
                this->objects = new Object[this->capacity()];
                for(int i=0; i<this->size(); i++){
                    objects[i] = vector.objects[i];
                }
            }

            return *this;
        }


        Object& operator[](int index){
            return objects[index];
        }


        const Object& operator[](int index) const{
            return objects[index];
        }


        Object& at(int index){
            return objects[index];
        }


        const Object& at(int index) const{
            return objects[index];
        }


        void push_back(const Object& x){
            if(this->_size == this->_capacity){
                this->reserve(2 * this->_capacity + 1);
            }
            objects[this->_size++] = x;
        }


        void pop_back(){
            if(this->empty()){
                throw std::out_of_range("Exception: out_of_range");
            }
            this->_size--;
        }

        
        void clear(){
            this->_size = 0;
        }


        const Object& back() const{
            return objects[this->_size - 1];
        }


        int size() const{
            return this->_size;
        }


        int capacity() const{
            return this->_capacity;
        }


        bool empty() const{
            return this->size() == 0;
        }


        void resize(int newSize){
            if(newSize > this->_capacity){
                reserve(newSize * 2 + 1);
            }
            this->_size = newSize;
        }


        void reserve(int newCapacity){
            if(newCapacity < this->_size){
                return;
            }    

            Object *oldArray = objects;
            objects = new Object[newCapacity];

            for(int i=0; i<this->_size; i++){
                objects[i] = oldArray[i];
            }

            this->_capacity = newCapacity;
            delete []oldArray;
        }


        enum {SPARE_CAPACITY = 16};

        typedef Object *iterator;
        typedef const Object *const_iterator;

        iterator begin(){
            return &objects[0];
        }


        const_iterator begin() const{
            return &objects[0];
        }


        iterator end(){
            return &objects[this->size()];
        }


        const_iterator end() const{
            return &objects[this->size()];
        }



    private:
        int _size;
        int _capacity;
        Object *objects;

};


#endif /* VECTOR_H */

