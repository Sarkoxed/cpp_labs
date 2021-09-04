#include<iostream>
#include<vector>

#ifndef MAIN_MATRIX
#define MAIN_MATRIX

template <typename T>
void get_el(T &x);

template <typename T>
std::ostream&operator<<(std::ostream&out, const std::vector<std::vector<T>> &x);

template <typename T>
void init_matr(std::vector<std::vector<T>> &x);


#endif
