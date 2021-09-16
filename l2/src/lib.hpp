#include <iostream>
#include <cmath>

template <typename T>
class point{
    public:
        point():_first(0.0), _second(0.0){}
        point(T f, T s):_first(f), _second(s){}
        T x(){return this->_first;}
        T y(){return this->_second;}
    private: 
        T _first;
        T _second;
};

class hypcy : point<double>{
    public:
        hypcy():_r(0.0), _k(1.0){}
        hypcy(double r, double k):_r(r), _k(k){}
        
        double get_x(double phi){ return this->_r * (this->_k - 1) * cos(phi) + this->_r * cos((this->_k - 1) * phi);}
        double get_y(double phi){ return this->_r * (this->_k - 1) * sin(phi) - this->_r * sin((this->_k - 1) * phi);}


        point<double> get_point(double phi){
            return point<double>(get_x(phi), get_y(phi));
        }
        
        point<double> get_rs(){ return point<double>(this->_r, this->_r * this->_k);}
            
       
        
    private:
        double _r;
        double _k;
};
