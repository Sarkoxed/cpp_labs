#include <iostream>
#include <vector>
#include <limits>

#pragma once 

template <typename T>
void getEl(T &x, std::istream &in = std::cin, std::ostream &err= std::cerr){
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
