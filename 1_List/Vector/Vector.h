

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

        explicit Vector(int initSize = 0): Size(initSize), Capacity(initSize + SPARE_CAPACITY){
            this->objects = new Object[Capacity];
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
                this->Size = vector.size();
                this->Capacity = vector.capacity();
                
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


        void push_back(const Object& x){
            if(this->Size == this->Capacity){
                this->reserve(2 * this->Capacity + 1);
            }
            objects[this->Size++] = x;
        }


        void pop_back(){
            this->Size--;
        }

        
        void clear(){
            this->Size = 0;
        }


        const Object& back() const{
            return objects[this->Size - 1];
        }


        int size() const{
            return this->Size;
        }


        int capacity() const{
            return this->Capacity;
        }


        bool empty() const{
            return this->size() == 0;
        }


        void resize(int newSize){
            if(newSize > this->Capacity){
                reserve(newSize * 2 + 1);
            }
            this->Size = newSize;
        }


        void reserve(int newCapacity){
            if(newCapacity < this->Size){
                return;
            }    

            Object *oldArray = objects;
            objects = new Object[newCapacity];

            for(int i=0; i<this->Size; i++){
                objects[i] = oldArray[i];
            }

            this->Capacity = newCapacity;
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
        int Size;
        int Capacity;
        Object *objects;

};


#endif /* VECTOR_H */

