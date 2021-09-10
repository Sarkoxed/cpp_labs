#include "line.hpp"


#ifndef CSW_HEADER
#define CSW_HEADER

template <typename T>
class row : public line<T>{
    public:
        row(){}
        row(size_t ind_h, line<T> line):_ind(ind_h), _line(line){}
        size_t ind(){ return this->_ind; }
        line<T> val(){ return this->_line;}
    protected:
        ::line<T> _line;
        size_t _ind;
};


template <typename T>
class csw : public row<T>{
    public:
        csw(size_t length = 0, size_t height = 0){
            this->_total_length = length;
            this->_total_height = height;
            this->_lines = nullptr;
            this->_height = 0;
        }
        
        csw(const T**cont, size_t hei, size_t len);
        csw(const std::vector<std::vector<T>> &cont);

        inline size_t height(){ return this->_height;};
        void insert(size_t ind_y, size_t ind_x, T val);

        void del(size_t ind_y);
        void del(size_t ind_y, size_t ind_x);
        int get(size_t ind_y);
        line<T> operator[](size_t ind_y);
        
        void debug_print();
        
        line<T> * begin(){ return this->_lines;}
        line<T> * end(){ return this->_lines  +this->height-1;}

        friend std::ostream& operator<<(std::ostream& out, csw<T> &x){
           size_t of = 0;
           auto *b = x.begin();
           for(size_t i = 0; i < x.height(); i++){
               for(;of < (*b).ind(); of++){
                   std::cout << line<T>(x._total_length) << std::endl;
               }
               std::cout << x._lines[i].val() << std::endl;              
               b++;
               of++;
           }
           return out;
        }

        void resize(size_t newsize);
       ~csw();

    private:
        size_t _total_width;
        size_t _total_height;
        size_t _height;
        row<T> *_lines;

};

template <typename T>
csw<T>::csw(const T** x, size_t hei, size_t len){
    this->_height = hei;
    this->_total_height = hei;
    this->total_length = len;
    size_t tmp = 0;
    this->_lines = new (std::nothrow) line<T>[hei];
    for(size_t i = 0; i < hei; i++){
       line<T> tmp = line<T>(x[i], len);
       if(tmp.begin() != nullptr){
           this->_lines[tmp++] = row<T>(i, tmp);
       }
    }
    this->resize(tmp);
}

template <typename T>
csw<T>::csw(const std::vector<std::vector<T>> &x){
    this->_height = x.size();
    this->_total_height = x.size();
    this->total_length = x[0].size();
    size_t tmp = 0;
    this->_lines = new (std::nothrow) line<T>[this->_total_height];
    for(size_t i = 0; i < this->_total_height; i++){
       line<T> tmp = line<T>(x[i], this->_total_height);
       if(tmp.begin() != nullptr){
           this->_lines[tmp++] = row<T>(i, tmp);
       }
    }
    this->resize(tmp);
}

template <typename T>
void csw<T>::resize(size_t newsize){
    row<T> *tmp = this->_lines;
    if(newsize == 0){
       delete []tmp;
       this->_lines = nullptr;
       this->_height = 0;
       return;
    }
    this->_lines = new (std::nothrow) row<T>[newsize];
    for(size_t i = 0; i < this->_height && i < newsize; i++){
        this->_lines[i] = tmp[i];
    }
    this->_height = newsize;
    delete []tmp;
}

template <typename T>
void csw<T>::insert(size_t ind_y, size_t ind_x, T val){
    int ind_h = this->get(ind_y);
    if(this->_height == 0 || ind_h > 0){
        this->_lines[ind_h].append(ind_x, val);
    }
    else{
        ///todo
    }
}

template <typename T>
void csw<T>::del(size_t ind_y){
   int dind = this->get(ind_y);
   if(dind == -1){
       return;
   }
   else if(dind == -2){
       return;
   }
   for(size_t i = static_cast<size_t>(dind); i < this->_height; i++){
       this->_lines[i] = this->_lines[i+1];
   }
   resize(this->_height-1);
}

template <typename T>
void csw<T>::del(size_t ind_y, size_t ind_x){
    int dind = this->get(ind_y);
    if(dind == -1 || dind == -2){
        return;
    }
    this->_lines[dind].del(ind_x);
}

template <typename T>
int csw<T>::get(size_t ind_y){
    size_t beg = 0, end = this->_length - 1;
    if(ind_y > this->_total_length-1 || ind_y < beg){
        throw "out of range";
        return -2;
    }
    while(beg <= end){
        int m = (end + beg) / 2;
        if(m < 0){
            return -1;
        }
        if(this->_lines[m].ind() < ind_y){
            beg = m + 1;
        }
        else if(this->_lines[m].ind() > ind_y){
            end = m - 1;
        }
        else{
            return m;
        }
    }
    return -1;
}

template <typename T>
line<T> csw<T>::operator[](size_t ind_y){
    int gind = this->get(ind_y);
    if(gind == -1){
        return 0;
    }
    else if(gind == -2){
        return -1;
    }
    return this->_lines[static_cast<size_t>(gind)].val();
}

template <typename T>
void csw<T>:: debug_print(){
    for(size_t i = 0; i < this->_length; i++){
        std::cout << "(";
        std::cout << this->_lines[i].ind();
        std::cout << ", ";
        std::cout << this->_lines[i].val();
        std::cout << ")";
    }
}
        
template <typename T>
csw<T>::~csw(){
    delete this->_lines;
}
#endif
