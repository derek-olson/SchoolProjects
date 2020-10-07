//
//  Functions.hpp
//  DIYvector
//
//  Created by Derek Olson on 9/9/19.
//  Copyright © 2019 Derek Olson. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <iostream>
#include <stdio.h>

// vector template structure
template <typename T>
class Vector{
public:
    Vector();
    Vector(int newCapacity);
    Vector(const Vector& v);
    
    Vector<T>& operator = (Vector<T> v);
    
    int getSize()const;
    int getCapacity()const;
    T get(int index)const;
    void set(int index, T);
    void pushBack(T);
    void popBack();
    void growVector();
    void freeVector();
    void MinIndex();
    
    T operator[](int index)const;
    T& operator[](int index);
    
    bool operator <=(Vector<T> rhs);
    bool operator >=(Vector<T> rhs);
    bool operator ==(Vector<T> rhs);
    bool operator !=(Vector<T> rhs);
    bool operator <(Vector<T> rhs);
    bool operator >(Vector<T> rhs);

    ~Vector();
    
    void Sort();
    
    T* begin();
    T* begin()const;
    T* end();
    T* end()const;
    
private:
    T* a;
    int capacity;
    int size;
};

// constructor
template<typename T>
Vector<T>::Vector(int newCapacity){
    a = new T [newCapacity];
    capacity = newCapacity;
    size = 0;
}

// default constructor
template<typename T>
Vector<T>::Vector(){
    a = 0;
    capacity = 0;
    size = 0;
}

// destructor
template<typename T>
Vector<T>::~Vector(){
    delete[] a;
    //std::cout << "deconstructed \n";
}

// copy constructor
template<typename T>
Vector<T>::Vector(const Vector& v)
:Vector(v.capacity)
{
    for (int i = 0; i < v.size; i++){
        a[i] = v.a[i];
    }
    size = v.size;
}

// overload operator =
template<typename T>
Vector<T>& Vector<T>::operator = (Vector<T> v){
    std::swap(a, v.a);
    std::swap(capacity, v.capacity);
    std::swap(size, v.size);
    
    return *this;  // this.~MyString();
}

// method to get the size
template<typename T>
int Vector<T>::getSize()const{
    return size;
}

// method to get the capacity
template<typename T>
int Vector<T>::getCapacity()const{
    return capacity;
}

// method to get
template<typename T>
T Vector<T>::get(int index)const{
    T* tempPtr = a + index;
    T x = *tempPtr;
    return x;
}

// method to set
template<typename T>
void Vector<T>::set(int index, T value){
    T* tempPtr = a + index;
    *tempPtr = value;
}

// method to push back
template<typename T>
void Vector<T>::pushBack(T value){
    T* tempPtr = a + size;
    *tempPtr = value;
    size++;
}

// method to pop back
template<typename T>
void Vector<T>::popBack(){
    size--;
}

// method to free a vector
template<typename T>
void Vector<T>::freeVector(){
    delete [] a;
    a = nullptr;
}

// method to grow a vector
template<typename T>
void Vector<T>::growVector(){
    int *ptr = new int [capacity*2];
    for (int i = 0; i < size; i++){
        ptr[i] = a[i];
    }
    capacity = (capacity*2);
    delete[] a;
    a = ptr;
}

// overload [] operator
template<typename T>
T Vector<T>::operator [](int index)const{
    return a[index];
};

// overload [] operator
template<typename T>
T& Vector<T>::operator [](int index){
    return a[index];
};

// overload << operator
template<typename T>
std::ostream& operator <<(std::ostream& out, const Vector<T>& v){
    for (int i = 0; i < v.getSize(); i++){
        out << v[i];
    }
    return out;
}

// overload == operator
template<typename T>
bool Vector<T>::operator ==(Vector<T> rhs){
    if (size != rhs.size){
        return false;
    }
    if (size == rhs.size){
        for (int i = 0; i < size; i++){
            if ((*this)[i] != rhs[i]){
                return false;
            }
        }
    }
    return true;
}

// overload != operator
template<typename T>
bool Vector<T>::operator !=(Vector<T> rhs){
    if (size != rhs.size){
        return true;
    }
    if (size == rhs.size){
        for (int i = 0; i < size; i++){
            if ((*this)[i] != rhs[i]){
                return true;
            }
        }
    }
    return false;
}

// overload <= operator
template<typename T>
bool Vector<T>::operator <=(Vector<T> rhs){
    if ((*this)==rhs){
        return true;
    }
    for (int i = 0; i < size-1; i++){
        if ((*this)[i] < rhs[i]){
            return true;
        }
    }
    return false;
}

// overload >= operator
template<typename T>
bool Vector<T>::operator >=(Vector<T> rhs){
    if ((*this)==rhs){
        return true;
    }
    for (int i = 0; i < size; i++){
        if ((*this)[i] > rhs[i]){
            return true;
        }
    }
    return false;
}

// overload > operator
template<typename T>
bool Vector<T>::operator >(Vector<T> rhs){
    for (int i = 0; i < size; i++){
        if ((*this)[i] < rhs[i]){
            return false;
        }
    }
    return true;
}

// overload < operator
template<typename T>
bool Vector<T>::operator <(Vector<T> rhs){
    for (int i = 0; i < size; i++){
        if ((*this)[i] > rhs[i]){
            return false;
        }
    }
    return true;
}

// sort method
template<typename T>
void Vector<T>::Sort(){
    for(int i = 0; i < size-1; i++){
        for (int i = 0; i < size-1; i++){
            if((*this)[i] > (*this)[i+1]){
                std::swap((*this)[i], (*this)[i+1]);
            }
        }
    }
}

template<typename T>
T* Vector<T>::begin(){
    return a;
}

template<typename T>
T* Vector<T>::begin()const{
    return a;
}

template<typename T>
T* Vector<T>::end(){
    return a+size;
}

template<typename T>
T* Vector<T>::end()const{
    return a+size;
}


#endif /* Functions_hpp */
