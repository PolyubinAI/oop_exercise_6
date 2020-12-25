//Полюбин Арсений М8О-206Б-19
//Лабораторная работа №5
//Вариант 22 - пятиугольник, очередь, список

#include <iostream>
#include <algorithm>
#include "pentagon.hpp"
#include "NewQueue.hpp"
#include "NewAllocator.hpp"
#include "NewIterator.hpp"
#include <exception>


int main()
{
    new_queue<Pentagon<int>, newAllocator<Pentagon<int>,20>> queu;


    Pentagon<int> p0;
    Pentagon<int> p1;
    Pentagon<int> p2;

    std::cout<< "Введите абсциссу и ординату вершины и длину основания пятиугольника\n";
    std::cin >> p0.Cord.first >> p0.Cord.second >> p0.Base;
    if(p0.Base == 0 ){
        std::cout << "Такого пятиугольника не существует";
        throw std::exception();
    }
    std::cout << "Введите абсциссу и ординату вершины и длину основания пятиугольника\n";
    std::cin >> p1.Cord.first >> p1.Cord.second >> p1.Base;
    if(p1.Base == 0 ){
        std::cout << "Такого пятиугольника не существует";
        throw std::exception();
    }
    std::cout << "Введите абсциссу и ординату вершины и длину основания пятиугольника\n";
    std::cin >> p2.Cord.first >> p2.Cord.second >> p2.Base;
    if(p2.Base == 0 ){
        std::cout << "Такого пятиугольника не существует";
        throw std::exception();
    }


    queu.push(p0);
    queu.push(p1);
    queu.push(p2);

    std::cout << "\nочередь: \n";
    std::for_each(queu.begin(), queu.end(), [](auto& figure){std::cout << figure;});

    std::cout << "\nКоличество пятиугольников площадью меньше 50: \n" << std::count_if(queu.begin(), queu.end(), [](const Pentagon<int> &pen){ return (double)area(pen) < 50.0; }) << "\n";

    Pentagon<int> del = queu.deletion(1);
    std::cout << "\nочередь: ";
    std::for_each(queu.begin(), queu.end(), [](auto& figure){std::cout << figure;});

    auto iter = queu.begin();
    ++iter;
    std::cout << "\nитератор № 1\n" << *iter;

    queu.insert(iter, p0);
    std::cout << "\nитератор № 2\n" << *iter;

    queu.insert(iter, p1);
    std::cout << "\nитератор № 3\n" << *iter;

    std::cout << "\nочередь:\n";
    std::for_each(queu.begin(), queu.end(), [](auto& figure){std::cout << figure;});

    ++iter;
    std::cout << "\nитератор № 4\n" << *iter;

    auto fig0 = queu.erase(iter);
    std::cout << "\nочередь: ";
    std::for_each(queu.begin(), queu.end(), [](auto& figure){std::cout << figure;});

    std::cout << "\nитератор № 5\n" << *iter;
    auto fig1 = queu.erase(iter);
    
    std::cout << "\nКоличество пятиугольников площадью меньше 20: \n" << std::count_if(queu.begin(), queu.end(), [](const Pentagon<int> &pen){ return (double)area(pen) < 20.0; }) << "\n";

    std::cout << "\nочередь:\n";
    std::for_each(queu.begin(), queu.end(), [](auto& figure){std::cout << figure;});

    std::cout << "\nитератор № 6\n" << *iter;
    auto fig2 = queu.erase(iter);

    std::cout << "\nУдаленные элементы:\n";
    std::cout << fig0 << fig1 << fig2;

    std::cout << "Удаление верхнего элемента очереди\n";
    std::cout << queu.top();

    std::cout << "\nочередь: \n";
    std::for_each(queu.begin(), queu.end(), [](auto& figure){std::cout << figure;});

    return 0;
}
