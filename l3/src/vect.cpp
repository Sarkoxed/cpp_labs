#include "vect.hpp"

using namespace vector;

// ---------------------- constructors 
vec::vec(){
    this->a_size = 0;
    this->a_total = 5;
    this->p_arr = new int [5];
}

vec::vec(const int size){
    if(size < 0){
        throw std::invalid_argument("negative size");
    }
    this->a_total = size + ext;
    this->a_size = 0;
    this->p_arr = new int [size+ext];
}

vec::vec(const int size, const int el){
    if(size < 0){
        throw std::invalid_argument("negative size");
    }

    this->a_total = size + ext;
    this->a_size = size;
    this->p_arr = new int [size + ext];
    for(int i = 0; i < size; i++){
       this->p_arr[i] = el; 
    }
}


vec::vec(const int size, const int *arr){
    if(size < 0){
        throw std::invalid_argument("negative size");
    }

    this->a_total = size + ext;
    this->a_size = size;
    this->p_arr = new int [size + ext];
    for(int i = 0; i < size; i++){
        this->p_arr[i] = arr[i];
    }
}

//vec::vec(const vec& right){
//    this->a_size = right.size();
//    this->a_total = right.size() + ext;
//    this->p_arr = new int [this->a_total];
//    std::copy(right.begin(), right.end(), this->p_arr);
//}

//----------------------  overloading
int vec::operator[](int ind) const{
     if(ind < 0 || ind >= this->a_size){
         throw std::out_of_range("out of range");
     }
     return this->p_arr[ind];
}


vec vec::operator+(const vec &y){
    vec tmp;
    for(int i = 0; i < this->a_size && y.a_size;i++){
       tmp.append(this->p_arr[i] + y.p_arr[i]); 
    }
    return tmp;
}

vec& vec::operator+=(const vec& right) {
    for(int i = 0; i < right.size() && i < this->a_size; i++){
        this->p_arr[i] += right[i];
    }
    if(right.size() > this->a_size){
        for(int i = this->a_size; i < right.size(); i++){
            this->append(right[i]);
        }
    }
    return *this;
}

vec& vec::operator=(const vec& right){
    if(*this != right){
        delete [] this->p_arr;
        this->a_size = right.size();
        this->a_total = right.size() + ext;
        this->p_arr = new int [this->a_total];
        std::copy(right.begin(), right.end(), this->p_arr);
    }
    return *this;
}


bool vec::operator==(const vec &y){
    if(this->a_size != y.size()){
        return false;
    }
    for(int i = 0; i < this->a_size; i++){
        if(this->p_arr[i] != y[i]){
            return false;
        }
    }
    return true;
}

bool vec::operator!=(const vec &y){ //how
    if(this->a_size != y.size()){
        return true;
    }
    for(int i = 0; i < this->a_size; i++){
        if(this->p_arr[i] != y[i]){
            return true;
        }
    }
    return false;
}

//----------------- extra methods
void vec::append(const int x){
    if(this->a_total == this->a_size){
        this->resize(this->a_size);    
    }
    this->p_arr[this->a_size] = x;
    this->a_size++;
}


void vec::resize(const int n){
    int *tmp = new int [n + ext];
    std::copy(this->p_arr, this->p_arr + n, tmp);
    delete[] this->p_arr;
    this->p_arr = tmp;
    this->a_total = n + ext;
    this->a_size = n;
}

vec vec::slice(int ind, int len){
    if(ind + len > this->a_size || ind > this->a_size || len  > this->a_size){  
        throw std::out_of_range("Quiet, buddy");
    }
    else if(ind < 0 || len < 0){
        throw std::invalid_argument("negative values not allowed");
    }

    return vec(len, this->p_arr + ind);
}


void vec::sort(){
    std::make_heap(this->p_arr, this->p_arr + this->a_size);
    std::sort_heap(this->p_arr, this->p_arr + this->a_size);
}


int vec::getmax() const {
//    if(this->a_size == 0){
//        throw std::invalid_argument("empty");
//    }
//    int tmp = this->p_arr[0];
//    for(int i = 1; i < this->a_size; i++){
//        if(tmp < this->p_arr[i]){
//            tmp = this->p_arr[i];
//        }
//    }
//    return tmp;
      if(this->a_size == 0){
          throw std::out_of_range("no elements");
      }
      return *std::max_element(this->p_arr, this->p_arr + this->a_size);
}

//---------------------- destructor!
vec::~vec(){
    delete[] this->p_arr;
}



