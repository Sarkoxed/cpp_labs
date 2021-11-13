#include <iostream>
#include "vect.hpp"
#include <string>
#include "../tools/toolib.hpp"
using namespace vector;

void heeelp(int n,const std::string *x){
    for(int i = 0; i < n; i++){
        std::cout << x[i] << std::endl;
    }
}

int main(){
    std::string x[13] = {"1. construct vector from nothing", "2. construct a vector of length n with all equal elements", "3. construct a vector of array and its size", "4. input a vector(only for pre-determined vectors)", "5. append an element", "6. print out a vector", "7. make a slice", "8. add two vectors", "9. sort a vector", "10. get max element", "11. help", "12. exit", "13 bool"};
    int c;
    vec p;
    int ad[10] = {2, -4,3 ,2,1 ,0, -2, -3, -7, 11};
    heeelp(13, x);
    while(true){
        std::cout << "input a number: ";
        getEl(c);
        switch (c){
            case 1:
                {
                    vec o;
                    p = o;
                    std::cout << p << std::endl;
                }
                break;
            case 2:
                {
                    std::cout << "input length: ";
                    int n;
                    getEl(n);
                    std::cout << "input an integer: ";
                    int z;
                    getEl(z);
                    vec o(n, z);
                    p = o;
                    std::cout << p << std::endl;;
                }
                break;
            case 3:
                {
                    std::cout << "input length: ";
                    int n;
                    getEl(n);
                    std::cout << "input " << n << "i integers: " << std::endl;
                    int *a = new int [n];
                    for(int i = 0; i < n; i++){
                        getEl(a[i]);
                    }
                    vec o(n, a);
                    p = o;
                    std::cout << p << std::endl;;
                    delete[] a;
                }
                break;
            case 4:
                {
                std::cout << "input length: ";
                int n;
                getEl(n);
                vec o(n);
                std::cout << "insert a line of "<< n << " numbers: ";
                    std::cin >> o;
                }
                break;
            case 5:
                {
                    std::cout << "input an integer: ";
                    int z;
                    getEl(z);
                    p.append(z);
                }
                break;

            case 6:
                std::cout << p << std::endl;;
                break;
            case 7:
                {
                    std::cout  << "input a beginning index: ";
                    int ind;
                    int len;
                    getEl(ind);
                    std::cout << "input a length: ";
                    getEl(len);
                    p = p.slice(ind, len);
                }
                break;
            case 8:
                {
                    std::cout << p << std::endl;;
                    std::cout << "+" << std::endl;
                    vec o(10,ad);
                    std::cout << o << std::endl;
                    std::cout << "=" << std::endl;
                    p += o;
                    std::cout << p << std::endl;
                }
                break;
            case 9:
                std::cout << "beginin with" << std::endl;
                std::cout << p << std::endl;;
                std::cout << "sorted one: "<< std::endl;
                p.sort();
                std::cout << p << std::endl;;
                break;
            case 10:
                std::cout << "maxelement : " << p.getmax() << std::endl;
                break;
            case 11:
                heeelp(12, x);
                break;
            case 13:
                std::cout << bool(p) << std::endl;
                break;
            case 12:
                exit(1);
            default:
                std::cout << "I don't get it. Try a little bit more shwifty" << std::endl;

        }
    }
}
