#pragma once

#include "character.hpp"
#include <random>


class OpAgent: public Character{
    private:
        std::string a_name;
        unsigned int a_reloadtime; // may be changed via weight
        unsigned int a_strength;
        unsigned int a_curweight;
        Inventory a_inventory;
        Weapon* a_hands;
    public:
        explicit OpAgent(std::pair< std::vector<std::string>, std::vector<std::vector<unsigned int>>>& config);

        std::string getName() const { return a_name; };
        unsigned int getRelTime() const { return a_reloadtime;};
        unsigned int getStrength() const { return a_strength;};
        unsigned int getCurWeight() const { return a_curweight;};

        Inventory& getInventory() {return a_inventory;}

        void setReload(unsigned int rel);
        void changeWeight(unsigned int weigh);      
        void chooseItemToHold(unsigned int num);

        void pickItem(Item* item, unsigned int num);
        Item* throwItem(unsigned int num);

        void reload(Bandolier& ammo);
        void heal(MedKit& med);
        unsigned int shoot(unsigned int dist);
        
        const bool isTrooper() const{ return true; }
        const bool isBeast() const { return false; }
};

static std::pair<std::vector<std::string>, std::vector<std::vector<unsigned int>>> readconfig(const std::string& filename);
