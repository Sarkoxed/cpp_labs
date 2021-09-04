#include <iostream>
#include <vector>
#include <list>

#ifndef MAIN_MATRIX
#define MAIN_MATRIX

template <typename T>
void get_el(int &T){
    try{
        T n;
        std::cin >> n;
        x = n;
    }
    catch(std::exception&e){
        std::cerr << e.what();
    }
}


template <typename T>
class el{
    public:
        el(int ind = 0, T val = 0):ind(ind), val(val){}
        int ind(){ return _ind; }
        T val(){ return _val;}
    protected:
        int _ind;
        T _val;
};


class line : el{
    public:
        line(int total = 0){
            this->am = 0;
            std::vector<el> this->els;
            this->matr_size = total;
        }
        
        void size(){ return els.length() };
        void add(el::el &x);
        void del(int ind);
        int get(int ind);
        friend std::ostream&operator<<(std::ostream&out,const line &x);    
    protected:
        std::vector<el> els;
        int matr_size;
};


void line::add(el::el &x){
    this->els.resize(this->size()+1); 
    this->els.push_back(x);
}

void line::del(int ind){
    int g = this->get(ind);
    if(g > 0){
        this->els.erase(this->els.begin() + g);
    }
}

int line::get(int ind){
    int beg = 0, end = this->size() - 1;
    while(beg <= end ){
        int m = (end + beg) / 2;
        if(this->els[m].ind() < ind){
            beg = m + 1;
        }
        else if(this->els[m].ind() > ind){
            end = m - 1;
        }
        else{
            return m;
        }
    }
    return -1;
}

std::ostream&operator<<(std::ostream&out, const line::line &x){
    auto p this->els.begin();
    for(int i = 0; i < this->matr_size; i++){
        if(*p.ind() == i){
            std::cout << *(p++).val() << " ";
        }
        else{
            std::cout << 0 << " ";
        }
    } 
}


template <typename T>
class csw : line{
    public:
        csw(int am = 0){
            std::vector<line> this->lines(am); 
        }
        int size(){ return lines.length();}
        void add(int ind_x, int ind_y, T v){
            el::el x = el(ind_y, v);
            
        } 
        void del(int ind_x);
        void del(int ind_x, int ind_y);
        friend std::ostream&operator<<(std::ostream&out,const csw &x);    

    private:
        std::vector<line> lines;
};

#endif
