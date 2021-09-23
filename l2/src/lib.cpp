#include "lib.hpp"
using namespace curve;

hypocycloid& hypocycloid:: operator=(const hypocycloid &x){
    this->_r = x._r;
    this->_k = x._k;
    this->_d = x._d;
    return *this;
}


void hypocycloid:: set_r(double r){ 
    if(r <= 0.0){
        throw "no z-negative allowed";
    }
    this->_r = r;
}

void hypocycloid:: set_k(double k){ 
    if(k <= 0.0){
        throw "no z-negative allowed";
    }
    this->_k = k;
}

void hypocycloid:: set_d(double d){ 
    if(d <= 0.0){
        throw "no z-negative allowed";
    }
    this->_d = d;
}


pair<double, double> hypocycloid:: get_point(double phi){
    return pair<double, double>(get_x(phi), get_y(phi));
}


pair<double, double> hypocycloid:: get_rs(){ return pair<double, double>(this->_r, this->_r * this->_k);}
    
double hypocycloid:: get_x(double phi){ return this->_r * (this->_k - 1) * cos(phi) + this->_d * cos((this->_k - 1) * phi);}

double hypocycloid:: get_y(double phi){ return this->_r * (this->_k - 1) * sin(phi) - this->_d * sin((this->_k - 1) * phi);}
            


hypotypes hypocycloid:: get_type() const{
    double sub = this->_r - this->_d;
    if(sub == 0.0){
        return hypotypes::normal;
    }
    else if(sub < 0.0){
        return hypotypes::extended;
    }
    else{
        return hypotypes::shortened;
    }
}

double hypocycloid:: sectorial_area() const {
    double a = M_1_PI*2.0;
    return (this->_k + 1.0) / 2.0 * (a * (this->_r * this->_r * (this->_k + 1.0) + this->_d * this->_d) - this->_d * this->_r * (this->_k + 2.0) / this->_k * sin(this->_k * a));
}

double hypocycloid:: curvative_radius(double phi) const {
    return (this->_k + 1.0) * pow(this->_r * this->_r + this->_d * this->_d - 2.0 * this->_r * this->_d * cos(this->_k * phi), 1.5) / fabs(pow(this->_r, 2.0) + pow(this->_d, 2.0) * (this->_k + 1.0) - this->_r * this->_d * (this->_k + 2.0)*cos(this->_k * phi));
}


std::ostream& operator<<(std::ostream &out, hypotypes x){
   switch (x){
      case hypotypes::normal:
          std::cout << "normal" << std::endl;
          break;
      case hypotypes::extended: 
          std::cout << "extended" << std::endl;
          break;
      case hypotypes::shortened: 
          std::cout << "shortened" << std::endl;
          break;
      default:
          throw "this might not happen"; 
   }
   return out; 
}
 
