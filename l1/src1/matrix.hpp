#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <limits>

#ifndef MAIN_MATRIX
#define MAIN_MATRIX

template <typename T> class el;
template <typename T> class line;
template <typename T> class csw;


template <typename T>
class el{
    public:
        el(int ind = 0, T val = 0):_ind(ind), _val(val){}

        int ind(){ return this->_ind; }

        T val(){ return this->_val;}
    protected:
        int _ind;
        T _val;
};

template <typename T>
class line{
    public:
        line(int total = 0){
            this->_els.resize(0);
            this->matr_size = total;
        }

        inline int size(){ return this->_els.size(); }

        inline void add(el<T> x){ this->_els.push_back(x); }

        void del(int ind);
        size_t get(size_t ind);
        inline std::vector<el<T>> els(){return this->_els; }
        el<T> operator[](int index);

        void debug_print();

        friend std::ostream& operator<<(std::ostream& out, const line<T> &x){
            int of = 0;
            for(auto i: x._els){
                for(; of < i.ind(); of++){
                    std::cout << 0 << " ";
                }
                std::cout << i.val() << " ";
                of++;
            }
            for(; of < x.matr_size; of++){
                std::cout << 0 << " ";
            }
            return out;
        }

    protected:
        std::vector<el<T>> _els;
        int matr_size;
};


template <typename T>
class csw : line<T>{
    public:
        csw():total_height(0), total_width(0){}
        csw(int width, int height);
        csw(const std::vector<std::vector<T>> &x);
        
        inline std::vector<line<T>> lines(){ return this->_lines;}
        inline int length(){ return this->total_height;}
        inline int width(){ return this->total_width;}

        void add(int ind_x, int ind_y, T v) ;
        void del(int ind_x);
        void del(int ind_x, int ind_y);
        void debug_print();
        
        inline line<T> operator[](int index){return this->lines[index];}

        friend std::ostream& operator<<(std::ostream& out,const csw<T> &x){
            for(auto i: x._lines){
                std::cout << i << std::endl;
            }
            return out;
        }


    protected:
        std::vector<line<T>> _lines;
        int total_height;
        int total_width;
};


template <typename T>
el<T> line<T>::operator[](int index){
    return this->get(index);
}

template <typename T>
void line<T>:: del(int ind){
    int g = this->get(ind);
    if(g > 0){
        this->_els.erase(this->_els.begin() + g);
    }
}

template <typename T>
size_t line<T>::get(size_t ind){
    size_t beg = 0, end = this->size() - 1;
    while(beg <= end ){
        int m = (end + beg) / 2;
        if(this->_els[m].ind() < ind){
            beg = m + 1;
        }
        else if(this->_els[m].ind() > ind){
            end = m - 1;
        }
        else{
            return m;
        }
    }
    return -1;
}

template <typename T>
 void line<T>::debug_print(){
     for(auto i: this->_els){
         std::cout << "(" << i.ind() << ", " << i.val() << ") ";
     }
 }


template <typename T>
csw<T>::csw(int width, int height){
    this->total_width = width;
    this->total_height = height;
    this->_lines.resize(height);
    for(int i = 0; i < height; i++){
        this->_lines[i] = line<T>(width);
    }
}

template <typename T>
csw<T>::csw(const std::vector<std::vector<T>> &x){
    csw(x.length(), x[0].length());
    for(int i = 0; i < x.length(); i++){
        for(int j = 0; j < x[0].length(); j++){
            if(x[i][j] != 0){
                this->add(i, j, x[i][j]);
            }
        }
    }

}

template <typename T>
void csw<T>::add(int ind_x, int ind_y, T v){
    el<T> x = el<T>(ind_y, v);
    this->_lines[ind_x].add(x);
}

template <typename T>
void csw<T>::del(int ind_x){
    if(ind_x >= 0 && ind_x < total_height){
        auto beg = this->_els[ind_x].begin(), end = this->_els[ind_x].end();
        this->_els[ind_x].erase(beg, end);
    }
}

template <typename T>
void csw<T>::del(int ind_x, int ind_y){
    if(ind_x >= 0 && ind_x < this->total_height){
        this->_els[ind_x].del(ind_y);
    }
}


template <typename T>
void csw<T>::debug_print(){
    for(auto i: this->_lines){
        i.debug_print();
        std::cout << std::endl;
    }
}


csw<int> init_matr();

std::vector<int> create_vec(csw<int> &matr,bool (*function)(int));

bool crit(int);
bool crit1(int);

template <typename T>
void get_el(T &x){
    bool valid;
    do{
        try{
            valid = true;
            std::cin >> x;
            if(std::cin.fail()){
                throw false;
            }
        }
        catch(bool e){
            valid = e;
            std::cerr << "Wrong input, retry" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(!valid);
}

template <typename T>
std::ostream&operator<<(std::ostream& out,const std::vector<T> &x){
    for(auto i: x){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return out;
}

#endif
