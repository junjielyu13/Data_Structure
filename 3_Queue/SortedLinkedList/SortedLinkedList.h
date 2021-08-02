/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SortedLinkedList.h
 * Author: Junjie_Li
 *
 * Created on August 2, 2021, 7:16 PM
 */

#ifndef SORTEDLINKEDLIST_H
#define SORTEDLINKEDLIST_H

#include <stdexcept>
#include <iostream>

template <typename Object>
class SortedLinkedList {
  
    private:
        struct Node{
            Object data;
            Node *prev;
            Node *next;

            Node(const Object& d = Object(), Node *p = nullptr, Node *n =nullptr):
                data(d), prev(p), next(n){
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
                const SortedLinkedList<Object> *List;
                Node *current;


                Object& retrieve() const{
                    return this->current->data;
                }

                const_iterator(Node *p): current(p){
                }
                const_iterator(const SortedLinkedList<Object>& list, Node *p):
                    List(&list), current(p){
                }


                friend class SortedLinkedList<Object>;

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

                iterator(const SortedLinkedList<Object>& list, Node *p): const_iterator(list, p){
                }


                friend class SortedLinkedList<Object>;

        };


    public:
        SortedLinkedList(){
            this->init();
        }
        SortedLinkedList(const SortedLinkedList& orig){
            this->init();
            *this = orig;
        }
        virtual ~SortedLinkedList(){
            this->clear();
            delete this->head;
            delete this->tail;
        }

        const SortedLinkedList& operator=(const SortedLinkedList& list){
            if(this == &list){
                return *this;
            }

            this->clear();
            for(const_iterator itr = list.begin(); itr != list.end(); ++itr){
                push_back(*itr);
            }

            return *this;
        }

        void add(const Object& x){
            Node* p;
            if(head == nullptr){
                std::cout << "test1\n";
                p = new Node(x, nullptr, nullptr);
                head = p;
                tail = p;
            }else{
                if( x > head->data){
                    std::cout << "test2\n";
                    Node* aux = head;
                    while(x > aux->data){
                        if(aux == tail){
                            break;
                        }
                        aux = aux->next;
                    }
                    std::cout << "aux data: " << aux->data << std::endl;
                    if(aux == tail){
                        if(x > tail->data){
                            std::cout << "test3\n";
                            p = new Node(x, tail, nullptr);
                            tail->next = p;
                            p->prev = tail;
                            tail = p;
                        }else{
                            std::cout << "test5\n";
                            p = new Node(x, aux->prev, aux);
                            p->prev->next = p;
                            aux->prev = p;
                        }
                    }else{
                        std::cout << "test5\n";
                        p = new Node(x, aux->prev, aux);
                        p->prev->next = p;
                        aux->prev = p;
                    }
                }else{
                    std::cout << "test4\n";
                    p = new Node(x, nullptr, head);
                    head->prev = p;
                    head = p;
                }
            }
            _size++;
        }

        void pop_front(){

            if(empty()){
                throw std::out_of_range("Exception: out of range.");
            }
            if(head == tail){
                delete head;
                head = nullptr;
                delete tail;
                tail = nullptr;
            }else{
                Node *p = head->next;
                p->prev = nullptr;
                head = p;
            }
            _size--;
        }


        void pop_back(){
            if(empty()){
                throw std::out_of_range("Exception: out of range.");
            }
            if(head == tail){
                delete head;
                head = nullptr;
                delete tail;
                tail = nullptr;
            }else{
                Node *p = tail->prev;
                p->next = nullptr;
                tail = p;
            }
            _size--;
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
            return tail->data;
        }
        const Object& back() const{
            return tail->data;
        }


        int size() const{
            return this->_size;
        }
        bool empty() const{
            return this->size() == 0;
        }


        iterator begin(){
            return iterator(head);
        }
        const_iterator begin() const{
            return iterator(head);
        }

        iterator end(){
            return iterator(tail->next);
        }
        const_iterator end() const{
            return const_iterator(tail->next);
        }


        iterator insert(iterator itr, const Object& x){
            
            Node *p = itr.current;
            _size++;
            return iterator(p->prev = p->prev->next = new Node(x, p->prev, p));

        }

        iterator erase(iterator itr){
            Node *p = itr.current;
            iterator retVal(p->next);
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            _size--;
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
            this->head = nullptr;
            this->tail = nullptr;
        }

};

#endif /* SORTEDLINKEDLIST_H */

