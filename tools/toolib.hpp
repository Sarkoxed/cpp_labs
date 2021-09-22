#include <iostream>
#include <vector>
#include <limits>

#ifndef TOOL_LIB
#define TOOL_LIB

template <typename T>
void get_el(T &x){
    bool valid;
    do{
        try{
            valid = true;
            std::cin >> x;
            if(std::cin.fail()){
                throw "bad input";
            }
        }
        catch(const char * &e){
            std::cerr << e;
            if(std::cin.bad() || std::cin.eof()){
                std::cerr << ", bye" << std::endl;
                exit(0);
            }
            valid = false;
            std::cerr << ", retry" << std::endl; 
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
