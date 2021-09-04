#include "lib.hpp"

template <typename T>
void get_el(T &x){
    try{
        int n;
        std::cin >> n;
        x = n;
    }
    catch(std::exception&e){
        std::cerr << e.what();
    }
}

template <typename T>
std::ostream&operator<<(std::ostream&out, const std::vector<std::vector<T>> &x){
    for(auto p1: x){
       for(auto p2: p1){
           std::cout << p2 << " ";
       }
       std::cout << std::endl;
    }
    return out;
}

template <typename T>
void init_matr(std::vector<std::vector<T>> &x){
    int n, m;
    T el;
    std::cout << "insert the amount of lines: ";
    get_el(n);
    std::cout << std::endl; 
    x.resize(n);
    for(int i = 0; i < n; i++){
        std::cout << "insert the amount of elements in line "<< i << ": ";
        get_el(m);
        std::cout << std::endl;
        x[i].resize(m);
            for(int j = 0; j < m; j++){
            std::cout << "element " << j << ": ";
            get_el(el);
            std::cout << std::endl;
            x[i][j] = el;
        }
    }
}


