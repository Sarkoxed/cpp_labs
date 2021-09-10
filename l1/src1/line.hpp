#include <iostream>
#include <vector>
#include <new>

#ifndef LINE_HEADER
#define LINE_HEADER

template <typename T> class line;
template <typename T> class el;

template <typename T>
class el{
    public:
        el(){}
        el(size_t ind_t, T val):_ind(ind_t), _val(val){}
        size_t ind(){ return this->_ind;}
        T val(){ return this->_val;}
    protected:
        size_t _ind;
        T _val;
};


template <typename T>
class line : public el<T>{
    public:
       inline line(size_t len = 0){
           this->_length = 0;
           this->_total_length = len;
           this->_elems = nullptr;
       }
//       line& operator=(const line &eq){
//           return *this;
//       }
       line(const T *cont, size_t len);
       line(const std::vector<T> &cont);
        
       inline size_t length(){ return this->_length;}
       void append(size_t ind, T val);
       //void insert(size_t ind, T val); maybe later
       void del(size_t ind);
       T operator[](size_t ind);
       int get(size_t ind);
       void debug_print();
       void resize(size_t newsize);
       el<T> * begin(){ return this->_elems; }
       el<T> * end(){return this->_elems + this->_length - 1;}
        
       friend std::ostream& operator<<(std::ostream& out, line<T> &x){
            size_t of = 0;
            auto *b = x.begin();
            for(size_t i = 0; i < x.length(); i++){
                for(; of < (*b).ind(); of++){
                    std::cout << 0 << " ";
                }
                std::cout << x._elems[i].val();
                std::cout << " ";
                b++;
                of++;
            }
            for(; of < x._total_length; of++){
                std::cout << 0 << " ";
            }
            return out;
        }

       ~line();
    protected:
        el<T> *_elems;
        size_t _length;
        size_t _total_length;
};

template <typename T>
line<T>::line(const T *cont, size_t len){
    this->_elems = new (std::nothrow) el<T> [len];
    this->_length = len;
    this->_total_length = len;
    size_t tmp = 0;
    for(size_t i = 0; i < len; i++){
       if(cont[i]){
           this->_elems[tmp++] = el<T>(i, cont[i]);
       }
    }
    this->resize(tmp);
}

template <typename T>
line<T>::line(const std::vector<T> &x){
    this->_elems = new (std::nothrow) el<T> [1];
    this->_length = x.size();
    this->_total_length = x.size();
    size_t tmp = 0;
    for(size_t i = 0; i < x.size(); i++){
       if(x[i]){
           this->_elems[tmp++] = el<T>(i, x[i]);
       }
    }
    this->resize(tmp);
}

template <typename T>
void line<T>:: resize(size_t newsize){
    el<T> *tmp = this->_elems;
    if(newsize == 0){
        delete []tmp;
        this->_elems = nullptr;
        this->_length = 0;
        return;
    }
    this->_elems = new (std::nothrow) el<T>[newsize];
    for(size_t i = 0; i < this->_length && i < newsize; i++){
        this->_elems[i] = tmp[i];
    }
    this->_length = newsize;
    delete [] tmp;
}

template <typename T> //something to do
void line<T>:: append(size_t ind, T val){
   resize(this->_length+1);
   el<T> x = el<T>(ind, val);
   this->_elems[this->_length - 1] = x;
}

template <typename T>
int line<T>::get(size_t ind){
    size_t beg = 0, end = this->_length - 1;
    if(ind > this->_total_length-1 || ind < beg){
        throw "out of range";
        return -2;
    }
    while(beg <= end){
        int m = (end + beg) / 2;
        if(m < 0){
            return -1;
        }
        if(this->_elems[m].ind() < ind){
            beg = m + 1;
        }
        else if(this->_elems[m].ind() > ind){
            end = m - 1;
        }
        else{
            return m;
        }
    }
    return -1;
}

template <typename T>
void line<T>:: del(size_t ind){
    int dind = this->get(ind);
    if(dind == -1){
        return;
    }else if(dind == -2){
        return;
    }
    for(size_t i = static_cast<size_t>(dind); i < this->_length - 1; i++){
        this->_elems[i] = this->_elems[i+1];
    }
    resize(this->_length - 1);
}

template <typename T>
T line<T>:: operator[](size_t ind){
    int gind = this->get(ind);
    if(gind == -1){
        return 0;
    }else if(gind == -2){
        return -1;
    }
    return this->_elems[static_cast<size_t>(gind)].val();
}

template <typename T>
void line<T>:: debug_print(){
    for(size_t i = 0; i < this->_length; i++){
        std::cout << "(";
        std::cout << this->_elems[i].ind();
        std::cout << ", ";
        std::cout << this->_elems[i].val();
        std::cout << ")";
    }
}

template <typename T>
line<T>::~line(){
    delete [] this->_elems;
}


#endif
