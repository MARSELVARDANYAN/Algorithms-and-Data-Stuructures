#ifndef __LINK_LIST__
#define __LINK_LIST__

#include <iostream>
#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <stdexcept>

template <typename T>
class List
{
  public:
      struct Node
      {
          T data{};
          Node* next;
          Node* prew;
          Node(const T& val) : data(val), next(nullptr), prew(nullptr) {}// Parameterised constructor with default argument
          Node(T val, Node *tempNext, Node* tempPrew): data(val),next(tempNext), prew(tempPrew){}// Parameterise constructor
      };
      
      size_t count{};
      Node* head;
      Node* tail;

  public:
      using value_type = T;
      using size_type = size_t;
      using referance = T&;
      using const_referance = const value_type&;
      using pointer = value_type*;
      using const_pointer = const value_type*;

  public:
      List();
      List(const List<T>&);
      List(std::initializer_list<T> initlist);
      ~List();

  public:
      class const_iterator;
      class iterator;
      class reverse_iterator;
      class const_reverse_iterator;
  private:
      size_t get_size();
  public:
      referance front();
      const_referance front() const;
      referance back();
      const_referance back() const;
      void print_list();
      void push_front(const_referance);
      void pop_front();
      void push_back(const_referance);
      void pop_back();
      iterator insert_after( iterator pos, const_referance val);
      iterator erase_after( iterator pos );
      void reverse() noexcept;
      void merge( List& other );
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
class List<T>::const_iterator
{
    friend class List<T>;
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
    const_iterator& operator--() ;
    const_iterator operator--(int);
    const T& operator*() const;

};

//ITERATOR+++++++++++
template <typename T>
class List<T>::iterator : public List<T>::const_iterator
{
    friend class List<T>;

private:
    Node* ptr;

public:
    iterator(Node* ptr);

public:
    iterator() = default;
    iterator(const iterator&) = default;      
    iterator(iterator&&) = default;

    iterator& operator=(iterator&) = default;      
    iterator& operator=(iterator&&) = default;

    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    T& operator*();
};

#include "../Headers/List.hpp"
#endif // 