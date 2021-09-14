#include "matrix.hpp"

void init_matr(csw<int> &matr){
    int m, n, el;
    std::cout << "input matrix height: ";
    get_el(m);
    std::cout << "input matrix width: ";
    get_el(n);
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            std::cout << "element " << i << "," <<  j << " : ";
            get_el(el);
            if(el != 0){
                matr.add(i, j, el);
            }
        }
    }
}

std::vector<int> create_vec(csw<int> &matr, bool (*func)(int)){
    std::vector<int> ans;
    for(size_t i = 0; i < matr.height(); i++){
        int sum = 0;
        for(size_t j = 0; j < matr[i].length(); j++){
            int tmp = matr[i][j];
            if(func(tmp)){
                sum += tmp;
            }
        }
        ans.push_back(sum);

    }
    return ans;
}



//checks for palindrome
bool crit(int z){
    std::string s = std::to_string(z);
    if(s.length() == 1 || (s.length() == 2 && z / 10 == z % 10)){
        return true;
    }
    auto p1 = s.begin(), p2 = s.end()-1;
    while(p1 != p2 && p1 != p2+1){
        if(*p1 != *p2){
            return false;
        }
        p1++;
        p2--;
    }
    return true;
}

bool crit1(int z){
    int prev;
    prev = z % 10;
    z /= 10;
    while(z != 0){
        int cur = z % 10;
        if(cur == prev){
            return true;
        }
        z /= 10;
        prev = cur;
    }
    return false;
}
