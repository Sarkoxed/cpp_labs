#include "matrix.hpp"

//csw<int> init_matr(){
//    int m, n, el;
//    std::cout << "input matrix height: ";
//    get_el(m);
//    std::cout << "input matrix width: ";
//    get_el(n);
//    csw<int> matr = csw<int>(n, m);
//    for(int i = 0; i < m; i++){
//        for(int j = 0; j < n; j++){
//            std::cout << "element " << i << "," <<  j << " : ";
//            get_el(el);
//            if(el != 0){
//                matr.add(i, j, el);
//            }
//        }
//    }
//    return matr;
//}
//
//std::vector<int> create_vec(csw<int> &matr, bool (*func)(int)){
//    int sum = 0;
//    std::vector<int> ans;
//    for(auto i: matr.lines()){
//        sum = 0;
//        for(auto j: i.els()){
//            if(func(j.val())){
//                sum += j.val();
//            }
//        }
//        ans.push_back(sum);
//
//    }
//    return ans;
//}



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
    int prev, cur;
    prev = z % 10;
    z /= 10;
    while(z != 0){
        cur = z % 10;
        if(cur == prev){
            return true;
        }
        z /= 10;
        prev = cur;
    }
    return false;
}

