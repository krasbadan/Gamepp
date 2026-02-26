#pragma once

#include <cstring>
#include <functional>
#include <stdexcept>
#include <cstring>



class SequenceError: public std::runtime_error {
public:
    SequenceError(const char* msg): std::runtime_error(msg) {}
};



template<typename T>
class Sequence;



template<typename T>
class SequenceIterator {
    friend Sequence<T>;
	
	T* ptr;
    bool* bool_ptr;
	T* end;
    
    SequenceIterator(T* _ptr, bool* _bool_ptr, T* _end):
		ptr(_ptr), bool_ptr(_bool_ptr), end(_end)
	{}
public:
    bool operator==(const SequenceIterator& other) const {
        return ptr == other.ptr;
    }
    bool operator!=(const SequenceIterator& other) const {
        return ptr != other.ptr;
    }
    
    T& operator*() const {
        return *ptr;
    }
    SequenceIterator& operator++() {
        do {
			++ptr;
			++bool_ptr;
		} while (ptr < end && !(*bool_ptr));
		return *this;
    }
};



const int min_arr_size = 4;

template<typename T>
class Sequence {
    int size;
    int arr_size;
    T* arr;
    bool* bool_arr;
    
    void realloc_arr(int new_arr_size) {
        arr_size = new_arr_size;
        arr = static_cast<T*>(realloc(arr, new_arr_size*sizeof(T)));
        if (arr == nullptr)
            throw std::bad_alloc();
        bool_arr = static_cast<bool*>(realloc(bool_arr, new_arr_size*sizeof(bool)));
        if (bool_arr == nullptr)
            throw std::bad_alloc();
    }
public:
    Sequence():
        size(0), arr_size(min_arr_size)
    {
        arr = static_cast<T*>(malloc(min_arr_size*sizeof(T)));
        if (arr == nullptr)
            throw std::bad_alloc();
        bool_arr = static_cast<bool*>(malloc(min_arr_size*sizeof(bool)));
        if (bool_arr == nullptr)
            throw std::bad_alloc();
    }
    Sequence(const Sequence& other):
        size(other.size), arr_size(other.arr_size)
    {
        arr = static_cast<T*>(malloc(arr_size*sizeof(T)));
        if (arr == nullptr)
            throw std::bad_alloc();
        bool_arr = static_cast<bool*>(malloc(arr_size*sizeof(bool)));
        if (bool_arr == nullptr)
            throw std::bad_alloc();
        memcpy(arr, other.arr, size*sizeof(T));
        memcpy(bool_arr, other.bool_arr, size*sizeof(T));
    }
    Sequence(Sequence&&) = default;
    ~Sequence() {
        free(arr);
        free(bool_arr);
    }
    
    SequenceIterator<T> begin() const {
        return SequenceIterator<T>(arr, bool_arr, arr+size);
    }
    SequenceIterator<T> end() const {
        return SequenceIterator<T>(arr+size, nullptr, arr+size);
    }
    
    int get_size() const {
        return size;
    }
    
    void push_back(T item) {
        if (size == arr_size)
            realloc_arr(arr_size*2);
        arr[size] = item;
        bool_arr[size++] = true;
    }
    
    T& operator[](int index) const {
        if (index < 0 || index >= size)
            throw SequenceError("Index must be in range [0, size)");
        return arr[index];
    }
    
    T& pop(int index) {
        if (index < 0 || index >= size)
            throw SequenceError("Index must be in range [0, size)");
        bool_arr[index] = false;
        return arr[index];
    }
    
    // Elements may change order
    void clean() {
        for (int i = size-1; i >= 0; --i) {
            if (!bool_arr[i]) {
                --size;
                if (i != size) {
                    arr[i] = arr[size];
                    bool_arr[i] = true;
                }
            }
        }
    }
    
    void sort(std::function<bool(const T& a, const T&b)> __comp) {
        std::sort(arr, arr+size, __comp);
    }
};