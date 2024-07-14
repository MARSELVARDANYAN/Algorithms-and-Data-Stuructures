#ifndef __LINK_LIST__
#define __LINK_LIST__

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <algorithm>

template <typename T>
class LinkedList
{
  private:
      struct Node
      {
          T data;
          Node* next;
          Node(const T& val) : data(val), next(nullptr) {}// Parameterised constructor with default argument
          Node(T val, Node *tempNext): data(val),next(tempNext){}// Parameterise constructor
      };
      
      Node* head;

  public:
      using value_type = T;
      using size_type = size_t;
      using referance = T&;
      using const_referance = const value_type&;
      using pointer = value_type*;
      using const_pointer = const value_type*;

  public:
      LinkedList();
      LinkedList(const LinkedList<T>&);
      LinkedList(std::initializer_list<T> initlist);
      ~LinkedList();

  public:
      class const_iterator;
      class iterator;

  public:
      referance front();
      const_referance front() const;
      void print_list();
      void push_front(const_referance);
      void pop_front();
      iterator insert_after( const_iterator pos, const_referance val);
      iterator erase_after( const_iterator pos );
      void reverse() noexcept;
      void merge( LinkedList& other );
      bool empty() const noexcept;      
      void unique();
      void sort();
      void clear() noexcept;

  public:
      iterator begin();
      const_iterator cbegin() const;
    
      iterator end();
      const_iterator cend() const;
      
    
};

//CONST ITERATOR+++++
template <typename T>
class LinkedList<T>::const_iterator
{
    friend class LinkedList<T>;
protected:
    const Node* ptr;

private:
    const_iterator(const Node* ptr);

public:
    const_iterator() = default;
    const_iterator(const const_iterator&) = default;
    const_iterator(const_iterator&&) = default;

    const_iterator& operator=(const_iterator&) = default;      
    const_iterator& operator=(const_iterator&&) = default;

    const_iterator& operator++();
    const_iterator operator++(int);
    const T& operator*() const;

};

//ITERATOR+++++++++++
template <typename T>
class LinkedList<T>::iterator : public LinkedList<T>::const_iterator
{
    friend class LinkedList<T>;

private:
    Node* ptr;

private:
    iterator(Node* ptr);

public:
    iterator() = default;
    iterator(const iterator&) = default;      
    iterator(iterator&&) = default;

    iterator& operator=(iterator&) = default;      
    iterator& operator=(iterator&&) = default;

    iterator& operator++();
    iterator operator++(int);
    T& operator*();
};

#include "../Headers/Forward_List.hpp"
#endif // 