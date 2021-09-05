#include <iostream>
#include <vector>

#ifndef TOOL_LIB
#define TOOL_LIB

template <typename T>
void get_el(T &x){
    try{
        T n;
        std::cin >> n;
        x = n;
    }
    catch(std::exception&e){
        std::cerr << e.what();
    }
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
