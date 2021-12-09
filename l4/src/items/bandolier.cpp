// sarkoxed //
#include "bandolier.hpp"

//Bandolier Bandolier::operator+(const Bandolier& right){
//    if(a_bullets == right.a_bullets){
//        a_cursize = (a_cursize + right.a_cursize) % a_maxsize;
//        right.a_cursize = 0;
//        return;
//    }
//    throw std::invalid_argument("wrong bullets");
//    
//}
//
//void Bandolier::operator+(const unsigned int right){
//    a_cursize = (a_cursize + right) % a_maxsize;
//}


//void Bandolier::operator-(const unsigned int right){
//    if(right > a_cursize){
//        a_cursize = 0;
//    }
//    a_cursize -= right;
//}

void Bandolier::operator+=(Bandolier& right){
    if(a_bullets == right.a_bullets){
        a_cursize = (a_cursize + right.a_cursize) % a_maxsize;
        right.a_cursize = 0;
    }
    throw std::invalid_argument("wrong bullets");
}

void Bandolier::operator+=(const unsigned int right){
    a_cursize = (a_cursize + right) % a_maxsize;
}

void Bandolier::operator++(){
    if(a_cursize < a_maxsize - 1){
        a_cursize++;
    }
}

void Bandolier::operator--(){
    if(a_cursize < a_maxsize - 1){
        a_cursize++;
    }
}


