#include <iostream>
#include <stdexcept>
#include <algorithm>

#pragma once

namespace vector{
    template<int N> 
    class vec{
        private:
            int a_arr[N];
            int a_size;
            int total(){ return N; };
        public:
            vec():a_arr{}, a_size(0){}; 

            explicit vec(const int &x);            
            explicit vec(const int &n,const int *arr);
            void append(const int &x);
            
            int operator[](int ind) const;
            vec operator+(const vec &y);
            vec slice(int ind, int len);
            void sort();
            int getmax() const;
            explicit operator bool() const{ return (this->a_size == 0) ? false : true;}
             

            //in dynamic make it stop somehow            
            friend std::istream &operator>>(std::istream &in, vec &y){
                y.a_size = y.total();
                for(int i = 0; i < y.a_size; i++){
                    in >> y.a_arr[i];
                }
                return in;
            }
    
            friend std::ostream &operator<<(std::ostream &out, const vec &y){
                for(int i = 0; i < y.a_size; i++){
                    out << y[i] << " ";
                }
                return out;
            }

           
            };
    
    template<int N>
    vec<N>::vec(const int &x){
        if(N < 1){
            throw std::out_of_range("no more space");
        }
        this->a_arr[0] = x;
        this->a_size = 1;
    }
    
    template<int N>
    vec<N>::vec(const int &n,const int *arr){
        for(int i = 0; i < N && i < n; i++){
            this->a_arr[i] = arr[i];
        }
        this->a_size = (n > N) ? N : n;
    }

    template<int N>
    void vec<N>::append(const int &x){
        if(this->a_size == N){
            throw std::out_of_range("no more space");
        }
        else{
            this->a_arr[this->a_size] = x;
            this->a_size++;
        }
    }

    template<int N>
    int vec<N>::operator[](int ind) const{
         if(ind < 0 || ind > this->a_size){
             throw std::out_of_range("out of range");
         }
         return this->a_arr[ind];
    }

    
    
    template<int N>
    vec<N> vec<N>::operator+(const vec &y){
        vec tmp;
        for(int i = 0; i < this->a_size && y.a_size;i++){
           tmp.append(this->a_arr[i] + y.a_arr[i]); 
        }
        return tmp;
    }

    template<int N>
    vec<N> vec<N>::slice(int ind, int len){
        if(ind + len > this->a_size || ind < 0 || len < 0 || ind > this->a_size || len  > this->a_size){  
            throw std::out_of_range("Quiet, buddy");
        }
        else{
            return vec(len, this->a_arr + ind);
        }
    }

    template<int N>
    void vec<N>::sort(){
        std::make_heap(this->a_arr, this->a_arr + this->a_size);

        std::sort_heap(this->a_arr, this->a_arr + this->a_size);
    }

    template<int N>
    int vec<N>::getmax() const { // check the algo____________________________________________-
    //    if(this->a_size == 0){
    //        throw std::invalid_argument("empty");
    //    }
    //    int tmp = this->a_arr[0];
    //    for(int i = 1; i < this->a_size; i++){
    //        if(tmp < this->a_arr[i]){
    //            tmp = this->a_arr[i];
    //        }
    //    }
    //    return tmp;
          return *std::max_element(this->a_arr, this->a_arr + this->a_size);
    }

}
// todo #include "vect.tpp"
