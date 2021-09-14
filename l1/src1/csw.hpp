#include "line.hpp"

template <class T> class csw;

template <class T>
class csw : public line<T>{
    public:
        csw():_height(0), _width(0), _lines(nullptr){}
        
        csw<T>& operator=(const csw<T> &cp){
            if(!(*this == cp)){
                delete [] this->_lines;
                this->_heigth = cp.height();
                this->_width = cp.width();
                this->_lines = new line<T>[this->_height];
                std::copy(cp.begin(), cp.end()-1, this->_lines);
            }
            return *this;
        }

        csw(const csw<T> &cp){
            this->_heigth = cp.height();
            this->_width = cp.width();
            this->_lines = new line<T>[this->_height];
            std::copy(cp.begin(), cp.end()-1, this->_lines);
        }

        csw(size_t h, size_t w){
          this->_width = w;
          this->_height = h;
          this->_lines = new line<T>[h];
          for(size_t i = 0; i < h; i++){
            line<T> tmp(w);
            this->_lines[i] = tmp;
          }
        }
        ~csw(){ delete []this->_lines;}

        explicit csw(const T** cont, size_t len);
        explicit csw(std::vector<std::vector<T>> cont);

        void add(size_t ind_y, size_t ind_x, T val){ this->_lines[ind_y].append(ind_x, val); }

        line<T> operator[](size_t ind){
          if(ind < this->_height){
              return this->_lines[ind];
          }
          
          throw std::out_of_range("operator []");
        }
        size_t height(){ return this->_height;};
        size_t width(){ return this->_width;};

        line<T>* begin(){ return this->_lines; };
        line<T>* end(){ return this->_lines + this->_height; }

        friend std::ostream& operator<<(std::ostream& out, csw<T> &x){
            for(auto i = x.begin(); i != x.end(); ++i){
              std::cout << *i << std::endl;
            }
            return out;
        }

    private:
        size_t _height;
        size_t _width;
        line<T> *_lines;
};
