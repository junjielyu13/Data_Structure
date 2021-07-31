/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DoublyLinkedList.h
 * Author: Junjie_Li
 *
 * Created on July 31, 2021, 12:58 AM
 */

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdexcept>

template <typename Object>
class DoublyLinkedList {
    
    private:
        struct Node{
            Object data;
            Node *prev;
            Node *next;

            Node(const Object& d = Object(), Node *prev = nullptr, Node *next =nullptr):
                data(d), prev(prev), next(next){
            }
        };

    public:
        class const_iterator{

            public:
                const_iterator(): current(nullptr){
                }


                const Object& operator*()const{
                    return this->retrieve();
                }
                const_iterator& operator++(){
                    this->current = this->current->next;
                    return *this;
                }
                const_iterator operator++(int){
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }
                const_iterator& operator--(){
                    this->current = this->current->prev;
                    return *this;
                }
                const_iterator operator--(int){
                    const_iterator old = *this;
                    --(*this);
                    return old;
                }
                bool operator==(const const_iterator& iterator) const{
                    return this->current == iterator.current;
                }
                bool operator!=(const const_iterator& iterator) const{
                    return !(*this == iterator);
                }
            

            protected:
                const DoublyLinkedList<Object> *List;
                Node *current;


                Object& retrieve() const{
                    return this->current->data;
                }

                const_iterator(Node *p): current(p){
                }
                const_iterator(const DoublyLinkedList<Object>& list, Node *p):
                    List(&list), current(p){
                }

                // void assertIsValid() const{
                //     if(this->List == nullptr || this->current == nullptr || this->current == this->List->head){
                //         throw std::out_of_range("Exception: Iterator out of bounds.");
                //     }
                // }

                friend class DoublyLinkedList<Object>;

        };
        
        class iterator: public const_iterator{

            public:
                iterator(){
                }

                Object& operator*(){
                    return this->retrieve();
                }
                const Object& operator*() const{
                    return const_iterator::operator*();
                }
                iterator& operator++(){
                    this->current = this->current->next;
                    return *this;
                }
                iterator operator++(int){
                    iterator old = *this;
                    ++(*this);
                    return old;
                }
                iterator& operator--(){
                    this->current = this->current->prev;
                    return *this;
                }
                iterator operator--(int){
                    iterator old = *this;
                    --(*this);
                    return old;
                }


            protected:
                iterator(Node* p): const_iterator(p){
                }

                iterator(const DoublyLinkedList<Object>& list, Node *p): const_iterator(list, p){
                }


                friend class DoublyLinkedList<Object>;

        };
        

    public:
        DoublyLinkedList(){
            this->init();
        }

        DoublyLinkedList(const DoublyLinkedList& orig){
            this->init();
            *this = orig;
        }

        virtual ~DoublyLinkedList(){
            this->clear();
            delete this->head;
            delete this->tail;
        }

        const DoublyLinkedList& operator=(const DoublyLinkedList& list){
            if(this == &list){
                return *this;
            }

            this->clear();
            for(const_iterator itr = list.begin(); itr != list.end(); ++itr){
                push_back(*itr);
            }

            return *this;
        }


        void push_front(const Object& x){
            this->insert(this->begin(), x);
        }
        void push_back(const Object& x){
            this->insert(this->end(), x);
        }


        void pop_front(){
            this->erase(this->begin());
        }
        void pop_back(){
            this->erase(this->end());
        }


        void resize(int newsize){
            if(newsize >= size && newsize < 0){
                return;
            }

            this->_size = newsize;
            iterator aux;
            while(newsize > 0){
                aux = *begin()++;
                --newsize;
            }

            this->erase(aux, this->end());

        }


        void clear(){
            while (!this->empty()){
                this->pop_front();
            }
        }


        Object& front(){
            return *this->begin();
        }
        const Object& front() const{
            return *begin();
        }

        Object& back(){
            return *--end();
        }
        const Object& back() const{
            return *--end();
        }


        int size() const{
            return this->_size;
        }
        bool empty() const{
            return this->size() == 0;
        }


        iterator begin(){
            return iterator(head->next);
        }
        const_iterator begin() const{
            return iterator(head->next);
        }

        iterator end(){
            return iterator(tail);
        }
        const_iterator end() const{
            return const_iterator(tail);
        }


        iterator insert(iterator itr, const Object& x){

            // itr.assertIsValid();
            // if(itr.List != this){
            //     throw std::invalid_argument("Exception: Iterator mismatch.");
            // }


            Node *p = itr.current;
            this->_size++;
            
            if(itr == this->begin()){
                if(this->head == nullptr){
                    std::cout << "test test1\n";
                    return iterator(this->head = this->tail = new Node(x, nullptr, nullptr));
                }else{
                    std::cout << "test test2\n";
                    std::cout << "test test head current:  "<< this->head->data<< std::endl;
                    return iterator(this->head = new Node(x, nullptr, p));
                }
            }else if(itr == this->end()){
                if(this->tail == nullptr){
                    std::cout << "test test3\n";
                    return iterator(this->head = this->tail = new Node(x, nullptr, nullptr));
                }else{
                    std::cout << "test test4\n";
                    return iterator(this->head = new Node(x, p, nullptr));
                }
        
            }
            std::cout << "test test5\n";
            return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));
            

        }

        iterator erase(iterator itr){

            Node *p = itr.current;
            iterator retVal(p->next);

            if(itr == this->begin()){
                this->head = p->next;
                p->prev = nullptr;
            }else if(itr == this->end()){
                this->tail = p->prev;
                p->next = nullptr;
            }else{
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }
            delete p;

            this->_size--;

            return retVal;
        }

        iterator erase(iterator start, iterator end){
            for(iterator itr = start; itr != end; ){
                itr = this->erase(itr);
            }
            return end;
        }
        


    private:
        int _size;
        Node *head;
        Node *tail;

        void init(){
            this->_size = 0;
            this->head = new Node;
            this->tail = new Node;
            this->head->next = this->tail;
            this->tail->prev = this->head;
        }


};

#endif /* DOUBLYLINKEDLIST_H */

