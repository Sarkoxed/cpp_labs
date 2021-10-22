#include <iostream>
#include <stdexcept>
#include <algorithm>

#pragma once

namespace vector{
    const int ext = 5;

    class vec{
        private:
            int *p_arr;
            int a_size;
            int a_total;
            
            void resize(const int n);
        public:
            vec();                                             // default constructor
            explicit vec(const int size);                      // constructor of an empty vector determined size
            explicit vec(const int size, const int el);        // like a vector in stl
           // explicit vec(const vec &y);
            explicit vec(const int size, const int *arr);      // from the array
            void append(const int el);
            ~vec();
            
            int operator[](int ind) const;                     // great choice to read comment here
            vec& operator+=(const vec &y);
            bool operator==(const vec &y);
            bool operator!=(const vec &y);
            vec& operator=(const vec &y);
            vec operator+(const vec &y);                       // adding two vectors                    

            vec slice(int ind, int len);

            void sort();
            int getmax() const;

            explicit operator bool() const{ return (this->a_size == 0) ? false : true;}

            int* begin() const {return this->p_arr;};
            int* end() const {return this->p_arr + this->a_size;};
            int size() const {return this->a_size;};

            //in dynamic make it stop somehow            
            friend std::istream &operator>>(std::istream &in, vec &y){
                for(int i = 0; i < y.a_size; i++){
                    in >> y.p_arr[i];
                }
                return in;
            }
            
            friend std::ostream &operator<<(std::ostream &out, const vec &y){
                for(int i = 0; i < y.a_size; i++){
                    out << y[i] << " ";
                }
                return out;
            }            };
}
// todo #include "vect.tpp"
