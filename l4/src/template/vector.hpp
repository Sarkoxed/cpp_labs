#include "iostream"
#include <iterator>


template<typename T>
class Vec{
    private:
        T* p_array;
        unsigned int a_size;
    public:
        class vec_iterator{
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;
            using reference         = T&;
            
            private:
                pointer p_ptr;
            public:
                explicit vec_iterator(pointer p):p_ptr(p){}
                T& operator*() const { return *p_ptr; }
                T* operator->() { return p_ptr; }

                vec_iterator& operator++(){p_ptr++; return *this;}
                vec_iterator operator++(int) { vec_iterator tmp = *this; ++(*this); return tmp;}

                friend bool operator==(const vec_iterator& a, const vec_iterator& b) { return a.p_ptr == b.p_ptr; }
                friend bool operator!=(const vec_iterator& a, const vec_iterator& b) { return a.p_ptr != b.p_ptr; }
        };


        explicit Vec(unsigned int n = 0) : p_array(new T [n]), a_size(n){}
        Vec(const Vec& copy);
        Vec(Vec&& move);
        explicit Vec(const T* vals, int n);
        ~Vec(){delete[] p_array;}

        friend bool operator==(const Vec& a, const Vec&b) {return a==b;};
        friend bool operator!=(const Vec& a, const Vec&b) {return a!=b;}
        bool operator==(const Vec& r);
        bool operator!=(const Vec& r);

        Vec& operator=(const Vec& cp);
        Vec& operator=(Vec&& mv);
        
        const int size()const{return a_size;}

        const T& operator[](int num) const;
        T& operator[](int num);

        void pushBack(const T& x);
        
        vec_iterator begin() { return vec_iterator(p_array);}
        vec_iterator end() { return vec_iterator(p_array + a_size);}

};


template<typename T>
Vec<T>::Vec(const Vec<T>& copy):a_size(copy.a_size){
    p_array = new T [a_size];
    std::copy(copy.p_array, copy.p_array+a_size, p_array);
}


template<typename T>
Vec<T>::Vec(Vec<T>&& move):a_size(move.a_size){
    p_array = move.p_array;
    move.p_array = nullptr;
}

template<typename T>
Vec<T>::Vec(const T* vals, int n){
    if(n < 0){
        throw std::invalid_argument("bad size");
    }
    a_size = n;
    p_array = new T [a_size];
    std::copy(vals, vals+n, p_array);
}

template<typename T>
bool Vec<T>::operator==(const Vec<T>& r){
    if(this == &r){
        return true;
    }
    if(a_size != r.a_size){
        return false;
    }
    for(int i = 0; i < a_size; i++){
        if(p_array[i] != r.p_array[i]){
            return false;
        }
    }
    return true;
}

template<typename T>
bool Vec<T>::operator!=(const Vec<T>& r){
    if(this == &r){
        return false;
    }
    if(a_size != r.a_size){
        return true;
    }
    for(int i = 0; i < a_size; i++){
        if(p_array[i] != r.p_array[i]){
            return true;
        }
    }
    return false;
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec<T>& cp){
    if(this != &cp){
        a_size = cp.a_size;
        delete[] p_array;
        std::copy(cp.p_array, cp.p_array + a_size, p_array);
    }
    return *this;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec<T>&& mv){
    if(this != &mv){
        a_size = mv.a_size;
        delete[] p_array;
        p_array = mv.p_array;
        mv.p_array = nullptr;
    }
    return *this;
}

template<typename T>
const T& Vec<T>::operator[](int num) const{
    if(num < 0 || num >= a_size){
        throw std::out_of_range("out of range");
    }
    return p_array[num];
}

template<typename T>
T& Vec<T>::operator[](int num){
    if(num < 0 || num >= a_size){
        throw std::out_of_range("out of range");
    }
    return p_array[num];
}


template<typename T>
void Vec<T>::pushBack(const T& x){
    T* tmp = new T [a_size+1];
    std::copy(p_array, p_array+a_size, tmp);
    delete[] p_array;
    p_array = tmp;
    a_size++;
    p_array[a_size-1] = x;
}
