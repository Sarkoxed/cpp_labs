#include "csw.hpp"
#include <limits>

#ifndef MAIN_LIB
#define MAIN_LIB


csw<int> init_matr();

std::vector<int> create_vec(csw<int> &matr,bool (*function)(int));

bool crit(int);
bool crit1(int);

template <typename T>
void get_el(T &x){
    bool valid;
    do{
        try{
            valid = true;
            std::cin >> x;
            if(std::cin.fail()){
                throw false;
            }
        }
        catch(bool e){
            valid = e;
            std::cerr << "Wrong input, retry" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(!valid);
}

template <typename T>
std::ostream&operator<<(std::ostream& out,const std::vector<T> &x){
    for(auto i: x){
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return out;
}

#endif
