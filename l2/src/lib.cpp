#include "lib.hpp"
using namespace hypo;

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

