#include <iostream>
#include <stdexcept>

#pragma once

template <size_t N>
class vec;

namespace vector{
    template<size_t N>
    class vec{
        public:
            vec():a_arr{}, a_size(0){}; 
            explicit vec(const int &x){
                this->a_arr[0] = x;
                this->a_size = 1;
            }
            
            vec(const size_t &n,const int *arr){
                for(size_t i = 0; i < N && i < n; i++){
                    this->a_arr[i] = arr[i];
                }
                this->a_size = (n > N) ? N : n;
            }
            
            void input(std::istream &in){
                for(size_t i = 0; i < N; i++){
                    in >> this->a_arr[i];
                    this->a_size++;
                }
            }
            
            void append(const int &x){
                if(this->a_size == this->a_total){
                    throw std::out_of_range("no more space");
                }
                else{
                    this->a_arr[this->a_size] = x;
                    this->a_size++;
                }
            }

            void print(){
                for(size_t i = 0; i < this->a_size; i++){
                    std::cout << this->a_arr[i] << " ";
                }
                std::cout << std::endl;
            }

            vec part(size_t ind, size_t len){
                if(ind + len > this->a_size){
                    throw std::out_of_range("too much");
                }
                else{
                    return vec(ind + len, this->a_arr + ind);
                }
            }

            vec add(const vec &y){
                vec tmp;
                for(size_t i = 0; i < this->a_size && y.a_size;i++){
                   tmp.append(this->a_arr[i] + y.a_arr[i]); 
                }
                return tmp;
            }

            void sort(){
               heapsort(this->a_arr, this->a_size); 
            }

            int getmax() const {
                if(this->a_size == 0){
                    throw std::invalid_argument("empty");
                }
                int tmp = this->a_arr[0];
                for(size_t i = 1; i < this->a_size; i++){
                    if(tmp < this->arr[i]){
                        tmp = this->arr[i];
                    }
                }
                return tmp;
            }

            
        private:
            int a_arr[N];
            size_t a_size;
            size_t a_total = N;
    };
}

void heapify(int arr[],  int n, int i);
void heapsort(int z[], size_t n);
