//
// Created by Ars Polybin on 07.12.2020.
//

#ifndef LAB5_NEWALLOCATOR_HPP
#define LAB5_NEWALLOCATOR_HPP

#include <iostream>
#include <memory>
#include <functional>
#include <list>

template <class T, std::size_t size>
class newAllocator
{
private:
    T* buf;
    std::list<T*> list;
public:
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using size_type = std::size_t;

    newAllocator() noexcept: list(), buf(){
        static_assert(size > 0);
    }

    newAllocator(const newAllocator<T, size> &other): newAllocator(){
        buf = new T[size];
        for (std::size_t i = 0; i < size; ++i) {
            buf[i] = other.buf[i];
            list.push_back(&buf[i]);
        }
    }

    template <typename U, typename... Args>
    void construct(U* p, Args &&... args) {
        new (p) U(std::forward<Args>(args)...);
    }

    T* allocate(std::size_t size0){
        if (buf == nullptr){
            buf = new T[size];
            for (int i = 0; i < size; ++i) {
                list.push_back(&buf[i]);
            }
        }
        if (size0 > list.size()){
            throw (std::bad_alloc());
        } else {
            T* ticket = list.front();
            for (int i = 0; i < size0; ++i){
                list.pop_front();
            }
            return ticket;
        }
    }

    void deallocate(pointer, size_t) {}

    template <class U>
    struct rebind {
        using other = newAllocator<U, size>;
    };

    ~newAllocator(){
        delete[] buf;
    }
};

#endif //LAB5_NEWALLOCATOR_HPP
