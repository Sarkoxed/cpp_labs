#include <iostream>
#include <cmath>

#ifndef LIM_CYCLE
#define LIM_CYCLE
namespace hypo{
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

            hypocycloid& operator=(const hypocycloid &x){
                this->_r = x._r;
                this->_k = x._k;
                this->_d = x._d;
                return *this;
            }
                        
            void set_r(double r){ 
                if(r <= 0.0){
                    throw "no z-negative allowed";
                }
                this->_r = r;
            }
            void set_k(double k){ 
                if(k <= 0.0){
                    throw "no z-negative allowed";
                }
                this->_k = k;
            }
            void set_d(double d){ 
                if(d <= 0.0){
                    throw "no z-negative allowed";
                }
                this->_d = d;
            }
    
            

            double get_r() const {return this->_r;}
            double get_k() const {return this->_k;}
            double get_d() const {return this->_d;}
    
            hypotypes get_type() const;
            pair<double, double> get_point(double phi){
                return pair<double, double>(get_x(phi), get_y(phi));
            }
    
            double sectorial_area() const; 
            
            double curvative_radius(double phi) const;
            
            pair<double, double> get_rs(){ return pair<double, double>(this->_r, this->_r * this->_k);}
    
        private:
            double get_x(double phi){ return this->_r * (this->_k - 1) * cos(phi) + this->_d * cos((this->_k - 1) * phi);}
            double get_y(double phi){ return this->_r * (this->_k - 1) * sin(phi) - this->_d * sin((this->_k - 1) * phi);}
            
            double _r;
            double _k;
            double _d;
    };

}
#endif 
