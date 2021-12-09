#pragma once

#include "item.hpp"

class Weapon: Item{
    private:
        static std::map<short, std::vector<unsigned int>> m_config;
        WeaponType a_name;
        unsigned int a_damage;
        unsigned int a_tshoot;
        unsigned int a_treload;
        unsigned int a_mag;
        unsigned int a_fullmag;
    public:
        explicit Weapon(WeaponType t);
        explicit Weapon(const Weapon& vx) = default;
        explicit Weapon(Weapon&& x) = default;

        Weapon& operator=(const Weapon& right) = default;
        Weapon& operator=(Weapon&& right) = default;

        void readconfig(std::string filename);

        unsigned int getDamage() const{ return a_damage; };
        void makeShot();
        const bool getShotResult(unsigned int dist, unsigned int accuracy, unsigned int radius);
        void reload(unsigned int& ammo);

        const bool isWeapon() const{ return true; }
        const bool isMedkit() const{ return false; }
        const bool isAmmo() const{ return false; }
};


