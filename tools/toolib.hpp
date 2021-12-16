#include <iostream>
#include <vector>
#include <limits>
#include <random>
#pragma once 

template <typename T>
void getEl(T& x, std::istream& in = std::cin, std::ostream& err= std::cerr){
    bool valid;
    do{
        try{
            valid = true;
            in >> x;
            if(in.fail()){
                throw "bad input";
            }
        }
        catch(const char * &e){
            err << e;
            if(in.bad() || in.eof()){
                err << ", bye" << std::endl;
                exit(0);
            }
            valid = false;
            err << ", retry" << std::endl; 
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(!valid);
}

unsigned int randint(unsigned int a);
   
template <typename T>
std::ostream&operator<<(std::ostream& out,const std::vector<T> &x){
    for(auto i: x){
        out << i << " ";
    }
    out << std::endl;
    return out;
}

