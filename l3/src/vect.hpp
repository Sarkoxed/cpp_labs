#include <iostream>
#include <stdexcept>

#pragma once

void heapify(int arr[],  int n, int i);
void heapsort(int z[], int n);

namespace vector{
    template<int N> // I don't know how to escape negative values
    class vec{
        public:
            vec():a_arr{}, a_size(0){}; 

            explicit vec(const int &x){
                this->a_arr[0] = x;
                this->a_size = 1;
            }
            
            explicit vec(const int &n,const int *arr){
                for(int i = 0; i < N && i < n; i++){
                    this->a_arr[i] = arr[i];
                }
                this->a_size = (n > N) ? N : n;
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

            friend std::istream &operator>>(std::istream &in, vec &y){
                y.a_size = y.a_total;
                for(int i = 0; i < y.a_size; i++){
                    in >> y.a_arr[i];
                }
                return in;
            }
            
            int operator[](int ind) const{
                 if(ind < 0 || ind > this->a_size){
                     throw std::out_of_range("out of range");
                 }
                 return this->a_arr[ind];
            }

            friend std::ostream &operator<<(std::ostream &out, const vec &y){
                for(int i = 0; i < y.a_size; i++){
                    out << y[i] << " ";
                }
                return out;
            }

            vec operator+(const vec &y){
                vec tmp;
                for(int i = 0; i < this->a_size && y.a_size;i++){
                   tmp.append(this->a_arr[i] + y.a_arr[i]); 
                }
                return tmp;
            }

            vec slice(int ind, int len){
                if(ind + len > this->a_size || ind < 0 || len < 0 || ind > this->a_size || len  > this->a_size){  
                    throw std::out_of_range("Quiet, buddy");
                }
                else{
                    return vec(len, this->a_arr + ind);
                }
            }

            void sort(){
               heapsort(this->a_arr, this->a_size); 
            }

            int getmax() const {
                if(this->a_size == 0){
                    throw std::invalid_argument("empty");
                }
                int tmp = this->a_arr[0];
                for(int i = 1; i < this->a_size; i++){
                    if(tmp < this->a_arr[i]){
                        tmp = this->a_arr[i];
                    }
                }
                return tmp;
            }

            
        private:
            int a_arr[N];
            int a_size;
            int a_total = N;
    };
}
