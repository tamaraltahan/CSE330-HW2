// Vector ADT according to M.A. Weiss textbook
// Data Structures and Algorithm Analysis in C++
// (DSAAC++)

#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>
#include <cassert>   // change KV
//#include <stdexcept>
//#include "dsexceptions.h"

template <typename T>
class Vector
{
public:
    Vector(int initsize = 0)
        : theSize(initsize), theCapacity(initsize + SPARE_CAPACITY)
    {
        objects = new T[theCapacity];
    }

    Vector(const Vector& rhs)
        : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(0)
    {
        objects = new T[theCapacity];
        for (int k = 0; k < theSize; ++k)
            objects[k] = rhs.objects[k];
    }

    Vector& operator= (const Vector& rhs)
    {
        Vector copy(rhs);     // a1ternative; KV
        std::swap(*this, copy);
        return *this;
    }

    ~Vector()
    {
        delete[] objects;
    }

    bool empty() const
    {
        return size() == 0;
    }

    int size() const
    {
        return theSize;
    }

    int capacity() const
    {
        return theCapacity;
    }

    T& operator[](int index)
    {
        assert(index >= 0 && index < theSize);
        return objects[index];
    }

    const T& operator[](int index) const
    {
        assert(index >= 0 && index < theSize);
        return objects[index];
    }

    void resize(int newSize)
    {
        if (newSize > theCapacity)
            reserve(newSize * 2);
        theSize = newSize;
    }

    void reserve(int newCapacity)
    {
        if (newCapacity < theSize)
            return;

        T* newArray = new T[newCapacity];
        for (int k = 0; k < theSize; ++k)
            newArray[k] = objects[k]; //std::move( objects[ k ] );

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;
    }


    void push_back(const T& x)
    {
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void pop_back()
    {
        assert(!empty());
        --theSize;
    }

    const T& back() const
    {
        assert(!empty());
        return objects[theSize - 1];
    }

    const T& front() const
    {
        assert(!empty());
        return objects[0];
    }

    typedef T* iterator;
    typedef const T* const_iterator;

    iterator begin()
    {
        return &objects[0];
    }
    const_iterator begin() const
    {
        return &objects[0];
    }
    iterator end()
    {
        return &objects[size()];
    }
    const_iterator end() const
    {
        return &objects[size()];
    }

    static const int SPARE_CAPACITY = 2;


    //**************** LAB3/HW2 start **************************************

    void erase(int k) {
        if (k == theSize - 1) {
            pop_back();
        }
        else {
            for (int i = k; k < theSize - 1; ++i) {
                objects[i] = objects[i + 1];
            }
        }

    }

    void insert(int k, T x) {
        if (k == theSize + 1) {
            push_back(x);
        }
        else {
            for (int i = theSize; k >= k; --i) {
                objects[i] = objects[i - 1];
            }
            objects[k] = x;
        }
    }
   
    void erase(iterator itr)
    {
        //given a pointer to an element in the array
        //how do i access members of the array in an element by element way without indices?
        if (itr == &objects[theSize - 1]) {
            pop_back();
        }
        else {
            for (iterator i = itr; i != end(); ++i) {
                ++i;
            }

        }

    }

    void insert(iterator itr, T x) 
    {
        if (itr == &objects[theSize - 1]) {
            push_back(x);
        }
        else{
            for (iterator i = &objects[theSize]; i != itr; --i) {
                --i;
            }
        }

    }
    //**************** LAB3/HW2 end ***************************************

private:
    int theSize;
    int theCapacity;
    T* objects;
};

#endif