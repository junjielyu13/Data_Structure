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

template <typename Object>
class DoublyLinkedList {
    
    private:
        struct Node{
            Object data;
            Node *prev;
            Node *next;
        };

    public:
        class const_iterator{

            public:
                const_iterator(): current(nullptr){}
                const Object& operator*()const;
                const_iterator& operator++();
                const_iterator operator++(int);
                bool operator==(const const_iterator& iterator) const;
                bool operator!=(const const_iterator& iterator) const;

            protected:
                Node *current;
                Object& retrieve() const;
                const_iterator(Node *p) : current(p){}
                friend class DoublyLinkedList<Object>;

        }
        
        class iterator: public const_iterator{

            public:
                iterator();
                Object& operator*();
                const Object& operator*() const;
                iterator& operator++();
                iterator operator++();

            protected:
                iterator(Node* p): const_iterator(p){}
                friend class DoublyLinkedList<Object>;
        }
        

    public:
        DoublyLinkedList();
        DoublyLinkedList(const DoublyLinkedList& orig);
        virtual ~DoublyLinkedList();

        const DoublyLinkedList& operator=(const DoublyLinkedList& list);

        void push_front(const Object& x);
        void push_back(const Object& x);
        void pop_front();
        void pop_back();
        void resize();
        void clear();

        Object& front();
        const Object& front();
        Object& back();
        const Object& back();

        int size() const;
        bool empty() const;

        iterator begin();
        const_iterator begin();
        iterator end();
        const_iterator end();

        iterator insert(iterator itr, const Object& x);
        iterator erase(iterator itr);
        iterator erase(iterator start, iterator end);
        



    private:
        int _size;
        Node *head:
        Node *tail;

        void init();

};

#endif /* DOUBLYLINKEDLIST_H */

