#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "../tools/toolib.hpp"

#pragma once

namespace vector{
    class vec{
        private:
            int *p_arr;
            int a_size;
            int a_total;
            static const short ext = 5;  // extra space in realloc

            void resize(const int n);

        public:
            explicit vec(int size = 0):p_arr(new int [this->ext]), a_size(0), a_total(this->ext){ // default constructor
                if(size < 0){
                    throw std::invalid_argument("negative size");
                }
            }                                             
            explicit vec(const int size,const int *arr);      // from the array
            explicit vec(const int size,const int el);        // like a vector in stl
            vec(const vec &y);                                // copy constructor
            vec(vec &&y);                                     // move constructor
            ~vec();                                           // de....(wait a second..)....structor!!!
            
            const int& operator[](const int ind) const;       // great choice to read comment here
            int& operator[](const int ind); 

            vec& operator+=(const vec &y);

            bool operator==(const vec &y) noexcept;
            bool operator!=(const vec &y) noexcept;
            
            vec& operator=(const vec &y);                     // copy assignment
            vec& operator=(vec &&y);                          // move assignment

            vec operator+(const vec &y);                      // adding two vectors                    

            explicit operator bool() const{ return !(this->a_size == 0);}

            void append(int el);
            vec slice(int ind, int len);

            void sort();
            int getmax() const;

            int* begin() const {return this->p_arr;};
            int* end() const {return this->p_arr + this->a_size;};
            int size() const {return this->a_size;};

            friend std::istream &operator>>(std::istream &in, vec &y);    // rewrites the whole vector according to it's size 
            friend std::ostream &operator<<(std::ostream &out,const vec &y);   
    };

std::istream &operator<<(std::istream &in, vec &y);
std::ostream &operator>>(std::ostream &out, const vec &y);
}


