#include "matrix.hpp"
#include <iostream>

    int main(){
        csw<int> matr;
        matr = init_matr();
        matr.debug_print();
        std::cout << matr;
        std::cout << "Palindromes or Double digits?(0/1): "; 
        int choice;
        std::string s;
        std::vector<int> ans; 

        get_el(choice);
        switch (choice){
            case 0:
                ans = create_vec(matr, crit);
                s = "palindromes";
                break;
            case 1:
                ans = create_vec(matr, crit1);
                s = "double-digits";
                break;
            default:
                exit(1);
        }
        std::cout << "Sum of " << s << " of each line is: " << ans;
    }
