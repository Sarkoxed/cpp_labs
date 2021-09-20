#include "matrix.hpp"

int main(){
    csw<int> matr = init_matr();
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
            std::cerr << "Bad input" << std::endl;
            exit(1);
    }
    std::cout << "Sum of " << s << " of each line is: " << ans;
}

// try{
//   s = matr[40];
// }
// catch(const std::exception &e){
//  std::cerr << e.what() << std::endl;
// }
