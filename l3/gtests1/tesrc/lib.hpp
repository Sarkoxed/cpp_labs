#include <iostream>
#include <stdexcept>

#pragma once

void heapify(int arr[],  int n, int i);
void heapsort(int z[], int n);


namespace vector{
    template<int N>
    class vec{
       private:
            int a_arr[N];
            int a_size;
       public:
            vec():a_arr{}, a_size(0){}; 

            explicit vec( int x){
                if(N < 1){
                    throw std::out_of_range("no more place");
                }
                this->a_arr[0] = x;
                this->a_size = 1;
            }
            
            vec(const int &n,const int *arr){
                for(int i = 0; i < N && i < n; i++){
                    this->a_arr[i] = arr[i];
                }
                this->a_size = (n > N) ? N : n;
            }
            
            void input(std::istream &in){
                this->a_size = N;
                for(int i = 0; i < this->a_size; i++){
                    in >> this->a_arr[i];
                }
            }
            
            void append(const int &x){
                if(this->a_size == N){
                    throw std::out_of_range("no more space");
                }
                else{
                    this->a_arr[this->a_size] = x;
                    this->a_size++;
                }
            }

            void print(){
                for(int i = 0; i < this->a_size; i++){
                    std::cout << this->a_arr[i] << " ";
                }
                std::cout << std::endl;
            }

            vec slice(int ind, int len){
                if(ind + len > this->a_size){  
                    throw std::out_of_range("too much");
                }
                else{
                    return vec(len, this->a_arr + ind);
                }
            }

            vec add(const vec &y){
                vec tmp;
                for(int i = 0; i < this->a_size && y.a_size;i++){
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
                for(int i = 1; i < this->a_size; i++){
                    if(tmp < this->a_arr[i]){
                        tmp = this->a_arr[i];
                    }
                }
                return tmp;
            }

            bool equal(vec x){
                for(int i = 0; i < this->a_size; i++){
                    if(this->a_arr[i] != x.a_arr[i]){
                        return false;
                    }
                }
                return true;
            }

            
    };
}
