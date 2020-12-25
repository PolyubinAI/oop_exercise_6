//
// Created by Ars Polybin on 20.11.2020.
//


#ifndef LAB5_NEWITERATOR_HPP
#define LAB5_NEWITERATOR_HPP

#include <cstddef>
#include <cstdio>
#include <iterator>

//Структура итерарора для последовательного контейнера
template <typename T>
struct iterator
{//iteraor traits
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using reference = T&;
    using difference_type = int;
    using pointer = T*;

    T* ptr;
    iterator (T* ptr_ = nullptr) : ptr(ptr_) {}
    T& operator*() { return *ptr; }
    T* operator--() { return --ptr; }
    T* operator->() { return ptr; }
    T* operator++() { return ++ptr; }
    bool operator==(iterator const& other) const { return ptr == other.ptr; }
    bool operator!=(iterator const& other) const { return !(*this == other); }
};

template <typename T>
bool operator<(iterator<T> const& lhs, iterator<T> const& rhs) { return lhs.ptr < rhs.ptr; }
template <typename T>
bool operator>(iterator<T> const& lhs, iterator<T> const& rhs) { return rhs.ptr < lhs.ptr; }
template <typename T>
bool operator<=(iterator<T> const& lhs, iterator<T> const& rhs) { return !(rhs.ptr < lhs.ptr); }
template <typename T>
bool operator>=(iterator<T> const& lhs, iterator<T> const& rhs) { return !(lhs.ptr < rhs.ptr); }


#endif //LAB5_NEWITERATOR_HPP
