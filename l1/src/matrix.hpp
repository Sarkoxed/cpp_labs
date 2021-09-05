#include <iostream>
#include <vector>
#include <list>
#include <string>

#ifndef MAIN_MATRIX
#define MAIN_MATRIX

template <typename T>
void get_el(T &x){
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
std::ostream&operator<<(std::ostream& out,const std::vector<T> &x){
    for(auto i: x){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return out;
} 

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

        int size(){ return this->_els.size(); };

        void add(el<T> x){
          this->_els.push_back(x);
        }

        void del(int ind){
          int g = this->get(ind);
          if(g > 0){
              this->_els.erase(this->_els.begin() + g);
          }
        }

        int get(int ind){
          int beg = 0, end = this->size() - 1;
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
        
        std::vector<el<T>> els(){ return this->_els;} 
        
        void debug_print(){
          for(auto i: this->_els){
            std::cout << "(" << i.ind() << ", " << i.val() << ") ";
          }
        }
        friend std::ostream&operator<<(std::ostream&out,const line<T> &x){
            int of = 0;
            for(auto i: x._els){
              for(; of < i.ind(); of++){
                std::cout << 0 << " ";
              }
              std::cout << i.val() << " ";
              of++;
            }
            for(int j = of; j < x.matr_size; j++){
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
        csw(int width = 0, int height = 0){
            this->total_width = width;
            this->total_height = height;
            this->_lines.resize(height);
            for(int i = 0; i < height; i++){
              this->_lines[i] = line<T>(width);
            }
        }

        int size(){ return this->total_height;}
        int width(){ return this->total_width;}

        void add(int ind_x, int ind_y, T v){
            el<T> x = el<T>(ind_y, v);
            this->_lines[ind_x].add(x);
        }
        void del(int ind_x){
          if(ind_x >= 0 && ind_x < total_height){
              auto beg = this->_els[ind_x].begin(), end = this->_els[ind_x].end();
              this->_els[ind_x].erase(beg, end);
          }
        }
        void del(int ind_x, int ind_y){
          if(ind_x >= 0 && ind_x < this->total_height){
              this->_els[ind_x].del(ind_y);
          }
        }

        void debug_print(){
          for(auto i: this->_lines){
            i.debug_print();
            std::cout << std::endl;
          }
        }

        std::vector<line<T>> lines(){return this->_lines;}

        friend std::ostream&operator<<(std::ostream&out,const csw<T> &x){
          for(auto i: x._lines){
              std::cout << i << std::endl;
          }
          return out;
        }

    private:
        std::vector<line<T>> _lines;
        int total_height;
        int total_width;
};


csw<int> init_matr();
std::vector<int> create_vec(csw<int> &matr,bool (*function)(int));
bool crit(int);
#endif
