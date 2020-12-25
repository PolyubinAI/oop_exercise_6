//
// Created by Ars Polybin on 20.11.2020.
//

#ifndef LAB5_NEWQUEUE_HPP
#define LAB5_NEWQUEUE_HPP

#include "NewIterator.hpp"
#include "NewAllocator.hpp"
#include <exception>


template <class T, class ALLOCATOR>
class new_queue
{
private:
    std::unique_ptr<T> data_;
    size_t size_;
    size_t cap_;
    using allocator_type = typename ALLOCATOR::template rebind<T>::other;
    static allocator_type& get_allocator() {
        static allocator_type allocator;
        return allocator;
    }
public:

    new_queue();
    //Деструктор
    ~new_queue(){}
    void push(T const&);
    T pop();
    T& top() const;
    void insert(iterator<T>&, T&);
    T erase(iterator<T>&);
    T deletion(size_t const&);
    //Итераторы
    iterator<T> begin() { return data_.get(); }
    iterator<T> end() { return data_.get()+size_; }
    iterator<T> const begin() const { return data_.get(); }
    iterator<T> const end() const { return data_.get()+size_; }
    //перегрузка операторов new и delete
    void* operator new(size_t size) { return get_allocator().allocate(); };
    void* operator new[](size_t size) { return get_allocator().allocate(); };
    void operator delete(void* p) { get_allocator().deallocate(p); };
    void operator delete[](void* p) {get_allocator().deallocate(p); };
};


//Конструктор по умолчанию
template <typename T, class ALLOCATOR>
new_queue<T, ALLOCATOR>::new_queue()
{
    size_ = 0;
    cap_ = 1;
    std::unique_ptr<T> data(new T[cap_]);
    data_ = std::move(data);
}

//Добавление в конец очереди
template <typename T, class ALLOCATOR>
void new_queue<T, ALLOCATOR>::push(T const& el)
{
    try
    {
        if(size_ == cap_)
        {
            cap_ *= 2;
            std::unique_ptr<T> data(new T[cap_]);
            for(size_t i = 0; i < size_; ++i) { data.get()[i] = data_.get()[i]; }
            data_ = std::move(data);
        }
        data_.get()[size_] = el;
        ++size_;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        exit(-1);
    }
}

template <typename T, class ALLOCATOR>
T& new_queue<T, ALLOCATOR>::top() const
{
    try
    {
        if(size_ == 0) { throw std::exception(); }
        return data_.get()[0];
    }
    catch(const std::exception& e) { std::cerr << e.what() << "\n"; }
    exit(-1);
}

//Удаление из начала очереди
template <typename T, class ALLOCATOR>
T new_queue<T, ALLOCATOR>::pop()
{
    try
    {
        std::unique_ptr<T> data(new T[cap_]);
        T el;
        if (size_ == 0) { throw std::exception(); }
        for(size_t i = 1; i < size_; ++i) { data.get()[i-1] = data_.get()[i]; }
        el = data_.get()[0];
        data_ = std::move(data);
        --size_;
        return el;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        exit(-1);
    }
}

//Вставка по итератору
template <typename T, class ALLOCATOR>
void new_queue<T, ALLOCATOR>::insert(iterator<T>& iter, T& el)
{
    try
    {
        if(iter >= end() || iter < begin()) { throw std::exception(); }
        iterator<T> prev_iter = iter;
        T prev_el = *prev_iter;
        T cur_el = *prev_iter;
        *prev_iter = el;
        ++prev_iter;
        while(prev_iter != end())
        {
            cur_el = *prev_iter;
            *prev_iter = prev_el;
            prev_el = cur_el;
            ++prev_iter;
        }
        this->push(prev_el);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        exit(-1);
    }
}

//Удаление по итератору
template <typename T, class ALLOCATOR>
T new_queue<T, ALLOCATOR>::erase(iterator<T>& iter)
{
    try
    {
        if(iter >= end() || iter < begin()) { throw std::exception(); }
        if(size_ == 0) { throw std::exception(); }
        T val = *iter;
        size_t count = 1;
        iterator<T> prev_iter = iter;
        ++prev_iter;
        while(prev_iter != end())
        {
            ++count;
            *iter = *prev_iter;
            ++iter;
            ++prev_iter;
        }
        std::unique_ptr<T> data(new T[size_-1]);
        for(size_t i = 0; i < size_ - 1; ++i) { data.get()[i] = data_.get()[i];}
        data_ = std::move(data);
        --size_;
        iter = this->end();
        while(count > 0)
        {
            --count;
            --iter;
        }
        return val;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        exit(-1);
    }
}

//Удаление по индексу
template <typename T, class ALLOCATOR>
T new_queue<T, ALLOCATOR>::deletion(size_t const& ind)
{
    try
    {
        if(size_ == 0 || ind >= size_ || ind < 0) { throw std::exception();}
        T el = data_.get()[ind];
        for(size_t i = ind; i < size_-1; ++i) { data_.get()[ind] = data_.get()[ind+1]; }
        --size_;
        std::unique_ptr<T> data(new T[size_]);
        for(size_t i = 0; i < size_; ++i) {data.get()[i] = data_.get()[i];}
        return el;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        exit(-1);
    }

}



#endif //LAB5_NEWQUEUE_HPP
