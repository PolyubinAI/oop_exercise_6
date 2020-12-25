//
// Created by Ars Polybin on 19.11.2020.
//

#ifndef LAB5_PENTAGON_HPP
#define LAB5_PENTAGON_HPP

#include <iostream>
#include<cmath>
const double Pi = 3.141592653589;

template<class T>
struct Pentagon{
    std::pair<T, T> Cord;
    T Base;
    Pentagon(){};
    Pentagon(const std::pair<T, T> & cord, T base) : Cord(cord), Base(base){};

};

template<class T>
T area(const Pentagon<T> & pentagon){
    T S = pentagon.Base*pentagon.Base*5/4*tan(Pi/5);
    return S;
}

template<class T>
std::ostream & operator << (std::ostream & out, const Pentagon<T> & pentagon) {
    T X1, Y1;
    std::pair<T, T> second_pair(X1, Y1);
    second_pair.first = pentagon.Cord.first - pentagon.Base * cos(72 * Pi / 180);
    second_pair.second = pentagon.Cord.second + pentagon.Base * sin(72 * Pi / 180);
    out << "Координаты вершин пятиугольника: [";
    out << pentagon.Cord.first << ", ";
    out << pentagon.Cord.second<< ", ";
    out << second_pair.first << ", ";
    out << second_pair.second << ", ";
    second_pair.first += pentagon.Base * cos(36 * Pi / 180);
    second_pair.second += pentagon.Base * sin(36 * Pi / 180);
    out << second_pair.first << ", ";
    out << second_pair.second << ", ";
    second_pair.first += pentagon.Base * cos(36 * Pi / 180);
    second_pair.second -= pentagon.Base * sin(36 * Pi / 180);
    out << second_pair.first << ", ";
    out << second_pair.second << ", ";
    second_pair.first = pentagon.Cord.second;
    second_pair.second = pentagon.Cord.first + pentagon.Base;
    out << second_pair.first << ", ";
    out << second_pair.second << "] \n";
    return out;
}



#endif //LAB5_PENTAGON_HPP
