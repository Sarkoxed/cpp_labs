#include <iostream>
#include <cmath>

#pragma once
const double pi = 3.14159265358979323846264338328;

namespace curve{
    enum class hypotypes : short{normal, extended, shortened}; 
    

    template <typename T, typename H>
    class pair{
        public:
            pair():_first(0.0), _second(0.0){}
            pair(T f, H s):_first(f), _second(s){}
            T x() const {return this->_first;}
            H y() const {return this->_second;}
            
            pair<T, H>& operator=(const pair<T, H> &e){
                this->_first = e._first;
                this->_second = e._second;
                return *this;
            }
            pair(const pair<T,H> &x){
                this->_first = x._first;
                this->_second = x._second;
            }

            friend std::ostream& operator<<(std::ostream &out, const pair<T, H> &x){
                std::cout << "(" << x._first << ", " << x._second << ") " << std::endl;
                return out;
            }

            friend std::fstream& operator<<(std::fstream &out, const pair<T,H> &x){
                std::cout << "(" << x._first << ", " << x._second << ") " << std::endl;
                return out;

            }


        private: 
            T _first;
            H _second;
    };
    




    class hypocycloid{
        public:
            hypocycloid():_r(1.0), _k(1.0), _d(1.0){}

            hypocycloid(double r, double k):_r(r), _k(k), _d(r){
                if(r <= 0.0 || k <= 0.0){
                    throw "no z-negative allowed";
                }
            }
            hypocycloid(double r, double k, double d):_r(r), _k(k), _d(d){
                if(r <= 0.0 || k <= 0.0 || d <= 0.0){
                    throw "no z-negative allowed";
                }
            }

            hypocycloid(const hypocycloid &x):_r(x._r), _k(x._k), _d(x._d){}

            hypocycloid& operator=(const hypocycloid &x);                        
            void set_r(double r);
            void set_k(double k);
            void set_d(double d);            

            double get_r() const {return this->_r;}
            double get_k() const {return this->_k;}
            double get_d() const {return this->_d;}
    
            hypotypes get_type() const;

            pair<double, double> get_point(double phi);    
            double sectorial_area() const; 
            double curvative_radius(double phi) const;
            
            pair<double, double> get_rs();
        private:

            double get_x(double phi);
            double get_y(double phi);

            double _r;
            double _k;
            double _d;
    };

}

    std::ostream& operator<<(std::ostream &out, curve::hypotypes x);
