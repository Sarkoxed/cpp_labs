#pragma once

#include "item.hpp"

class Weapon: Item{
    private:
        WeaponType a_name;
        unsigned int a_damage;
        unsigned int a_tshoot;
        unsigned int a_treload;
        unsigned int a_mag;
        unsigned int a_fullmag;
    public:
//        explicit Weapon(WeaponType x);
//        Weapon(const Weapon& copy);
//        Weapon(Weapon&& move);
//
//        Weapon operator+(unsigned int extra);
//        void operator+=(unsigned int extra); 
//        
//        Weapon operator-(unsigned int dec);
//        void operator-=(unsigned int dec);
//        
//        Weapon& operator=(const Weapon& copy);
//        Weapon& operator=(Weapon&& move);
        Weapon();
        unsigned int getDamage() const{ return a_damage; };
        void makeShot();
        bool getShotResult(unsigned int dist, unsigned int accuracy);
        void reload(unsigned int ammmo);
};
