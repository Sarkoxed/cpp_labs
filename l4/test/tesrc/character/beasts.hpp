#pragma once
#include "character.hpp"

typedef std::vector<std::vector<unsigned int>> bconfig;

class WildBeast: public Character{
    private:
        unsigned int a_damage;
    public:
        explicit WildBeast(bconfig& config);
        unsigned int getDamage() const { return a_damage; };

        const bool isTrooper() const override{ return false; }
        const bool isBeast() const override{ return true; }


};

class SmartBeast: public Character{
    private:
        Weapon* a_hands;
    public: 
        explicit SmartBeast(bconfig& config);
        void pickItem(Weapon* item);
        Weapon* throwItem();

        unsigned int shoot(unsigned int dist);
        Weapon* getHand() const{ return a_hands;}

        const bool isTrooper() const override{ return false; }
        const bool isBeast() const override { return true; }
};

class ForagerBeast: public Character{
    private:
        unsigned int a_strength;
        Inventory a_inventory;
    public:
        explicit ForagerBeast(bconfig& config);
        void pickItem(Item* item, unsigned int num = 0);
        Item* throwItem(unsigned int num);
        Inventory& getInventory(){ return a_inventory;}
        unsigned int getStrenght() const{return a_strength;}

        const bool isTrooper() const override{ return false; }
        const bool isBeast() const override { return true; }


};

bconfig readbea(const std::string& filename);
