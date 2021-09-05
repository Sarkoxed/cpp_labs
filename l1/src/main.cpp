#include "matrix.hpp"
#include <iostream>
int main(){
    csw<int> matr;
    matr = init_matr();
    matr.debug_print();
    std::cout << matr;
    std::vector<int> ans = create_vec(matr, crit);
    std::cout << "Sum of palindromes of each line is: " << ans;
}
