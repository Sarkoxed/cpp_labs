#pragma once

#include "item.hpp"

class Bandolier: Item{
    private:
       WeaponType a_bullets;
       unsigned int a_maxsize;
       unsigned int a_cursize;
    public:
       Bandolier();
       
       unsigned int getCurSize() const { return a_cursize;};
       unsigned int getMaxSize() const { return a_maxsize;};
        
       void operator+(const Bandolier& right);
       void operator+(const unsigned int right);
       void operator-(const unsigned int right);
       void operator-=(unsigned int);
       void operator+=(unsigned int);
       void operator--();
       void operator++();
       
       WeaponType getType() const { return a_bullets; };
       void setType(WeaponType type, unsigned int amo = 0);
};
