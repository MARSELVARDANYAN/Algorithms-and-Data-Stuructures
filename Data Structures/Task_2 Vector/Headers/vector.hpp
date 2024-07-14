#include "vector.h"


//Constructors
template <typename T, typename Allocator>
Vector<T, Allocator>::Vector()
    : v_size(0)
    , v_capacity(0)
    , arr(nullptr)
{} //default constructor

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& rhv)
{
    this->v_size = rhv.v_size;
    this->v_capacity = rhv.v_capacity;
    alloc.allocate(arr, rhv.v_capacity);
    for(size_type i = 0; i < v_size; ++i) {
        alloc.construct(arr + i, rhv.arr_[i]);
    }
    
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector && rhv)
{   
    v_size = std::move(rhv.v_size);
    v_capacity = std::move(rhv.v_capacity);
    arr = rhv.arr;
    rhv.arr = {nullptr};
    
}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> init)
    : Vector()
{
    for (const T &val : init) {
        push_back(val);
    }

}

template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_type size, const_reference val)
    : v_size{size}
    , v_capacity{size} 
    , arr{alloc.allocate(v_capacity)}
{
    for(size_type i = 0; i < size; ++i) {
        alloc.construct(arr + i, val);
    }
}

template <typename T, typename Allocator>
template <typename InputIt>
Vector<T, Allocator>::Vector(InputIt first, InputIt last)
    : v_size{std::distance(first, last)}, 
      v_capacity{std::distance(first, last)}, 
      arr{alloc.allocate(v_capacity)}
{
    size_type i = 0;
    try {
        for (; first != last; ++first, ++i) {
            alloc.construct(arr + i, *first);
        }
    } catch (...) {
        for (size_type j = 0; j < i; ++j) {
            alloc.destroy(arr + j);
        }
        alloc.deallocate(arr, v_capacity);
        throw;
    }
}


//Destructor
template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector()
{
    clear();
}

template <typename T, typename Allocator>
const Vector<T, Allocator>& 
Vector<T, Allocator>::operator=(const Vector& rhv)
{
    if (this != &rhv) {
        clear();
        this->v_size = rhv.v_size;
        this->v_capacity = rhv.v_capacity;
        // this->arr = new value_type[rhv.v_capacity];
        alloc.clallocate(arr, rhv.v_capacity);
        for(size_t i = 0; i < v_size; ++i){
            alloc.construct(arr + i, rhv.arr[i]);
        }
    }
    return *this;
}


template <typename T, typename Allocator>
const Vector<T, Allocator>& 
Vector<T, Allocator>::operator=(Vector&& rhv)
{
    if (this != &rhv) {
        clear();
        v_size = std::move(rhv.v_size);
        v_capacity = std::move(rhv.v_capacity);
        arr = rhv.arr;
        rhv.arr = nullptr;
    }
    
    return *this;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::allocator_type 
Vector<T, Allocator>::get_allocator()
{
    return alloc;
}

template <typename T, typename Allocator> 
typename Vector<T, Allocator>::reference 
Vector<T, Allocator>::at(size_type pos)
{
    if (pos >= v_size) {
        throw;
    }
    return arr[pos];
}
    
template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::at(size_type pos) const
{
    if (pos >= v_size) {
        throw;
    }
    return arr[pos];
    
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference 
Vector<T, Allocator>::operator[](size_type  pos)
{
    return arr[pos];
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::operator[](size_type ind) const
{
    return arr[ind];
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::front()
{   
    if(v_size == 0) {
        throw 1;
    }
    return this->arr[0];
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::front() const
{   
    if (v_size == 0) {
        throw 1;
    }
    return this->arr[0];
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::back()
{
    if (v_size == 0) {
        throw 1;
    }
    return arr[v_size-1];
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::back() const
{
    if (v_size == 0) {
        throw 1;
    }
    return arr[v_size-1];
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::begin()
{
    return iterator(arr);
}
    
template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator 
Vector<T, Allocator>::begin() const
{
    return const_iterator(arr);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator 
Vector<T, Allocator>::cbegin() const
{
    const_iterator it = arr;
    return it;
}
    
template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::end()
{
    return iterator(arr + v_size);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator 
Vector<T, Allocator>::end() const
{
    return const_iterator(arr + v_size);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::cend() const
{
    return const_iterator(arr + v_size);
}
    
template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator 
Vector<T, Allocator>::rbegin()
{
    return reverse_iterator(arr + v_size - 1);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator 
Vector<T, Allocator>::rbegin() const
{
    return const_reverse_iterator(arr + v_size - 1);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator 
Vector<T, Allocator>::crbegin() const
{
    return const_reverse_iterator(arr + v_size - 1);
}
    
template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator 
Vector<T, Allocator>::rend()
{
    return reverse_iterator(arr - 1);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator 
Vector<T, Allocator>::rend() const
{
    return const_reverse_iterator(arr - 1);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator 
Vector<T, Allocator>::crend() const
{
    return const_reverse_iterator(arr - 1);
}

template <typename T, typename Allocator>
bool 
Vector<T, Allocator>::empty() const
{
    if (v_size == 0) {
        return true;
    }
        return false;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::Size() const
{
    return this->v_size;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type 
Vector<T, Allocator>::capacity() const
{
    return this->v_capacity;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::reserve(size_type new_cap)
{
    if (new_cap > v_capacity) {
        pointer new_arr = alloc.allocate(new_cap);

        for (size_type i = 0; i < v_size; ++i) {
            alloc.construct(new_arr + i, std::move(arr[i]));
            alloc.destroy(arr + i);
        }
        
        alloc.deallocate(arr, v_capacity);
        arr = new_arr;
        v_capacity = new_cap;
    }
}

template <typename T, typename Allocator>
void 
Vector<T, Allocator>::clear() noexcept
{
    for(size_type i = 0; i < v_size; ++i) {
        alloc.destroy(arr + i);
    }
    alloc.deallocate(arr, v_capacity);
    arr = nullptr;
    v_size = 0;
    v_capacity = 0;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::insert(const_iterator pos, const_reference val) {
        size_type index = pos.ptr - arr;

    if (v_size + 1 > v_capacity) {
        reserve(v_capacity == 0 ? 1 : v_capacity * 2);
    }

    if (index < v_size) {
        for (size_type i = v_size; i > index; --i) {
            alloc.construct(arr + i, std::move(arr[i - 1]));
            alloc.destroy(arr + i - 1);
        }
    }

    alloc.construct(arr + index, val);
    ++v_size;

    return begin() + index;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::insert(const_iterator pos, size_type count, const_reference val) {
    size_type index = pos.ptr - arr;
   // size_type index = std::distance(pos, begin());

    if (count == 0) {
        return cbegin() + index;
    }
    
    if (v_size + count > v_capacity) {
        size_type new_capacity = std::max(v_capacity * 2, v_size + count);
        pointer new_arr = alloc.allocate(new_capacity);

        for (size_type i = 0; i < index; ++i) {
            alloc.construct(new_arr + i, std::move(arr[i]));
            alloc.destroy(arr + i);
        }

        for (size_type i = 0; i < count; ++i) {
            alloc.construct(new_arr + index + i, val);
        }

        for (size_type i = index; i < v_size; ++i) {
            alloc.construct(new_arr + count + i, std::move(arr[i]));
            alloc.destroy(arr + i);
        }

        alloc.deallocate(arr, v_capacity);
        arr = new_arr;
        v_capacity = new_capacity;
    } else {

        for (size_type i = v_size; i > index; --i) {
            alloc.construct(arr + i + count - 1, std::move(arr[i - 1]));
            alloc.destroy(arr + i - 1);
        }

        for (size_type i = 0; i < count; ++i) {
            alloc.construct(arr + index + i, val);
        }
    }

    v_size += count;
    return begin() + index;
}


template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<value_type> init) {
    size_type index = pos.ptr - arr;
    size_type new_elements = init.size();

    if (v_size + new_elements > v_capacity) {
        reserve((v_size + new_elements) * 2);
    }

    for (size_type i = v_size; i > index; --i) {
        alloc.construct(arr + i + new_elements - 1, std::move(arr[i - 1]));
        alloc.destroy(arr + i - 1);
    }

    size_type i = index;
    for (const auto& element : init) {
        alloc.construct(arr + i, element);
        ++i;
    }

    v_size += new_elements;
    return begin() + index;
}


template <typename T, typename Allocator>
template <typename InputIt>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
    size_type index = pos.ptr - arr;
    
    size_type count = 0;
    for (InputIt it = first; it != last; ++it) {
        ++count;
    }

    if (v_size + count > v_capacity) {
         reserve((v_size + count) * 2);
    }

    for (size_type i = v_size; i > index; --i) {
        alloc.construct(arr + i + count - 1, std::move(arr[i - 1]));
        alloc.destroy(arr + i - 1);
    }

    size_type i = index;
    for (InputIt it = first; it != last; ++it, ++i) {
        alloc.construct(arr + i, std::move(it));
    }

    v_size += count;
    return begin() + index;
}




template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::erase(const_iterator pos)
{
    size_type index = pos.ptr - arr;
    
    if (index < v_size) {
        alloc.destroy(arr + index);

        for (size_type i = index; i < v_size - 1; ++i) {
            alloc.construct(arr + i, std::move(arr[i + 1]));
            alloc.destroy(arr + i + 1);
        }

        --v_size;
    }

    return arr + index;
}   

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
    size_type index_first = first.ptr - arr;
    size_type index_last = last.ptr - arr;
    size_type count = index_last - index_first;

    for (size_type i = index_first; i < index_last; ++i) {
        alloc.destroy(arr + i);
    }

    for (size_type i = index_last; i < v_size; ++i) {
        alloc.construct(arr + i - count, std::move(arr[i]));
        alloc.destroy(arr + i);
    }

    v_size -= count;

    return arr + index_first;
}


template <typename T, typename Allocator>
void Vector<T, Allocator>::push_back(const_reference val)
{
    if (v_size == v_capacity) {
        reserve(v_capacity == 0 ? 1 : v_capacity * 2); 
    }
    arr[v_size++] = val;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::pop_back()
{
    if (v_size == 0) {
        throw 1;
    }
    
    alloc.destroy(arr + v_size - 1);
    this->v_size--;
}

template <typename T, typename Allocator>
void Vector<T, Allocator>::resize(size_type new_size, const_reference val)
{
    if (new_size >= v_capacity) {
        reserve(new_size);
    }
            
    for (size_t i = v_size; i < new_size; ++i) {
        alloc.construct(arr[i], val);
    }
    this->v_size = new_size;
       
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator==(const Vector& other) const
{
    return compare(other) == 0;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator!=(const Vector& other) const
{
    return compare(other) != 0;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator<(const Vector& other) const
{
    return compare(other) < 0;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator<=(const Vector& other) const
{
    return compare(other) <= 0;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator>(const Vector& other) const
{
    return compare(other) > 0;
}
    
template <typename T, typename Allocator>
bool Vector<T, Allocator>::operator>=(const Vector& other) const
{
    return compare(other) >= 0;
}

template <typename T, typename Allocator>
int Vector<T, Allocator>::compare(const Vector& other) const
{
    if (arr.Size() < other.arr.Size()) return -1;
    if (arr.Size() > other.arr.Size()) return 1;

    return 0;
}

//++++++++++++++++++++++++++++++++++++++++
template <typename T, typename Allocator>
Vector<T, Allocator>::const_iterator::const_iterator(pointer ptr)
    : ptr{ptr}
{}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator 
Vector<T, Allocator>::const_iterator::operator+(size_type n) const
{
    return const_iterator(ptr + n);
}   

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator 
Vector<T, Allocator>::const_iterator::operator-(size_type n) const
{
    return const_iterator(ptr - n);
} 

template <typename T, typename Allocator>
int Vector<T, Allocator>::iterator::operator-(const_iterator& other) const
{
    return this->ptr - other.ptr;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator&
Vector<T, Allocator>::const_iterator::operator++()
{   
    ++ptr;
    return *this;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator 
Vector<T, Allocator>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    ++ptr;
    return temp;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator&
Vector<T, Allocator>::const_iterator::operator--()
{
    --ptr;
    return *this;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_iterator
Vector<T, Allocator>::const_iterator::operator--(int)
{
    const_iterator temp = *this;
    --ptr;
    return temp;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::const_iterator::operator*() const
{
    return *ptr;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_pointer
Vector<T, Allocator>::const_iterator::operator->() const
{
    return ptr;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference 
Vector<T, Allocator>::const_iterator::operator[](size_type pos) const
{
    return ptr[pos];
} 

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator==(const const_iterator& other) const
{
    return ptr == other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator!=(const const_iterator& other) const
{
    return ptr != other.ptr;
}     

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator<(const const_iterator& other) const
{
    return ptr < other.ptr;
}     

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator<=(const const_iterator& other) const
{
    return ptr <= other.ptr;
}  

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator>(const const_iterator& other) const
{
    return ptr > other.ptr;
}    

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_iterator::operator>=(const const_iterator& other) const
{
    return ptr >= other.ptr;
}

//+++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++
template <typename T, typename Allocator>
Vector<T, Allocator>::iterator::iterator(pointer ptr)
{
    this->ptr = ptr;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::iterator::operator+(size_type n) const
{
    return iterator(this->ptr + n);
}    
    
template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::iterator::operator-(size_type n) const
{
    return iterator(this->ptr - n);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator&
Vector<T, Allocator>::iterator::operator++()
{
    ++this->ptr;
    return *this;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::iterator::operator++(int)
{
    iterator temp = *this;
    ++this->ptr;
    return temp;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator&
Vector<T, Allocator>::iterator::operator--() 
{
    --this->ptr;
    return *this;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::iterator 
Vector<T, Allocator>::iterator::operator--(int)
{
    iterator temp = *this;
    --this->ptr;
    return temp;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference 
Vector<T, Allocator>::iterator::operator*()
{
    return *this->ptr;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::pointer
Vector<T, Allocator>::iterator::operator->() 
{
    return this->ptr;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::iterator::operator[](size_type pos) const
{
    return this->ptr[pos];
}

//++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++
template <typename T, typename Allocator>
Vector<T, Allocator>::const_reverse_iterator::const_reverse_iterator(pointer ptr)
    : ptr{ptr}
{}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::const_reverse_iterator::operator+(size_type n) const
{
    return const_reverse_iterator(ptr - n);
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator 
Vector<T, Allocator>::const_reverse_iterator::operator-(size_type n) const
{
    return const_reverse_iterator(ptr + n);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator&
Vector<T, Allocator>::const_reverse_iterator::operator++()
{
    --ptr;
    return *this;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp = *this;
    --this->ptr;
    return temp;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator&
Vector<T, Allocator>::const_reverse_iterator::operator--()
{
    ++ptr;
    return *this;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reverse_iterator
Vector<T, Allocator>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp = *this;
    ++this->ptr;
    return temp;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
 Vector<T, Allocator>::const_reverse_iterator::operator*()const
{
    return *ptr;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_pointer
Vector<T, Allocator>::const_reverse_iterator::operator->()const
{
    return ptr;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference 
Vector<T, Allocator>::const_reverse_iterator::operator[](size_type pos)const
{
    return ptr[pos];
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator==(const const_reverse_iterator& other) const
{
    return ptr == other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator!=(const const_reverse_iterator& other) const
{
    return ptr != other.ptr;
}
    
template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator<=(const const_reverse_iterator& other) const
{
    return ptr <= other.ptr;
}
     
template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator<(const const_reverse_iterator& other) const
{
    return ptr < other.ptr;
}
    
template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator>(const const_reverse_iterator& other) const
{
    return ptr > other.ptr;
}

template <typename T, typename Allocator>
bool Vector<T, Allocator>::const_reverse_iterator::operator>=(const const_reverse_iterator& other) const
{
    return ptr >= other.ptr;
}
     
//+++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++
template <typename T, typename Allocator>
Vector<T, Allocator>::reverse_iterator::reverse_iterator(pointer ptr)
{
    this->ptr(ptr);
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::reverse_iterator::operator+(size_type n) const
{
    return reverse_iterator(this->ptr - n);
}     

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::reverse_iterator::operator-(size_type n) const
{
    return reverse_iterator(this->ptr + n);
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator&
Vector<T, Allocator>::reverse_iterator::operator++()
{
    --this->ptr;
    return *this;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::reverse_iterator::operator++(int)
{
    reverse_iterator temp = *this;
    --this->ptr;
    return temp;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator&
Vector<T, Allocator>::reverse_iterator::operator--()
{
    ++this->ptr;
    return *this;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::reverse_iterator::operator--(int)
{
    reverse_iterator temp = *this;
    ++this->ptr;
    return temp;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::reverse_iterator::operator*()
{
    return *this->ptr;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::pointer 
Vector<T, Allocator>::reverse_iterator::operator->()
{
    return this->ptr;
} 

template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference 
Vector<T, Allocator>::reverse_iterator::operator[](size_type pos) const
{
    return this->ptr[pos];
} 


// template <typename T, typename Allocator>
// void 
// Vector<T, Allocator>::print()
// {
//     for (size_t i = 0; i < v_size; i++)
//     {
//         std::cout << this->arr[i] << " ";
//     }
    
// }

// template <typename T, typename Allocator>
// std::ostream& operator<<(std::ostream& out, Vector<T, Allocator>& ob)
// {      
    
//     for (size_t i = 0; i < ob.size(); i++) {
        
//         out << ob[i] << ' ';
//     }
    
//     return out;
// }


