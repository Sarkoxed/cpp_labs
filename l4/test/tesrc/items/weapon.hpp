#pragma once

#include "item.hpp"

class Weapon: public Item{
    private:
        WeaponType a_name;
        unsigned int a_damage;
        unsigned int a_tshoot;
        unsigned int a_treload;
        unsigned int a_mag;
        unsigned int a_fullmag;
    public:
        explicit Weapon(WeaponType t,std::map<WeaponType, std::vector<unsigned int>>& config);
        explicit Weapon(const Weapon& vx) = default;
        explicit Weapon(Weapon&& x) = default;

        Weapon& operator=(const Weapon& right) = default;
        Weapon& operator=(Weapon&& right) = default;

        
        unsigned int getCurrentAmmo() const {return a_mag;}
        unsigned int getFullAmmo() const { return a_fullmag;}
        unsigned int getRelTime() const {return a_treload;}
        unsigned int getShootTime() const {return a_tshoot;}
        WeaponType getName() const { return a_name;}


        unsigned int getDamage() const{ return a_damage; };
        void makeShot(unsigned int& time);
        const bool getShotResult(unsigned int dist, unsigned int accuracy, unsigned int radius);
        void reload(unsigned int& ammo, unsigned int& time);

        const bool isWeapon() const{ return true; }
        const bool isMedkit() const{ return false; }
        const bool isAmmo() const{ return false; }
};

std::map<WeaponType, std::vector<unsigned int>> readconfig(std::string filename);
