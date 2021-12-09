#pragma once

#include "../inventory/inventory.hpp"
#include <string>

class Character{
    protected:
        unsigned int a_curhealth;
        unsigned int a_maxhealth;
        unsigned int a_curtime;
        unsigned int a_maxtime; 
        unsigned int a_steptime; // may be changed via weight ---!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        unsigned int a_radius;
        unsigned int a_accuracy; // too
    public:
        virtual unsigned int getCurHealth() const { return a_curhealth; };
        virtual unsigned int getMaxHealth() const { return a_maxhealth; };
        virtual unsigned int getCurTime() const { return a_radius; };
        virtual unsigned int getMaxTime() const { return a_maxtime; };
        virtual unsigned int getStepTime() const { return a_steptime; };
        virtual unsigned int getRadius() const { return a_radius;};
        virtual unsigned int getAccuracy() const { return a_accuracy;};
        
        virtual void changeHealth(unsigned int health);
        virtual void recieveDamage(unsigned int dam);
        virtual void changeCurTime(unsigned int time);
        virtual void resetTime();
        virtual void setStepTime();        
};


class OpAgent: Character{
    private:
        std::string a_name;
        unsigned int a_reloadtime; // may be changed via weight
        unsigned int a_strength;
        unsigned int a_curweight;
        Inventory a_inventory;
        Item* a_hands;
    public:
        OpAgent();

        std::string getName() const { return a_name; };
        unsigned int getRelTime() const { return a_reloadtime;};
        unsigned int getStrength() const { return a_strength;};
        unsigned int getCurWeight() const { return a_curweight;};

        void setReload(unsigned int rel);
        void changeWeight(unsigned int weigh);      
        void chooseItemToHold(unsigned int num);

        void pickItem(Item* item);
        Item* throwItem(unsigned int num);
        void makeStep();        
};


class WildBeast: Character{
    private:
        unsigned int a_damage;
    public:
        WildBeast();
        unsigned int getDamage() const { return a_damage; };
};

class SmartBeast: Character{
    private:
        Weapon a_weapon;
    public: 
        SmartBeast();
};

class ForagerBeast: Character{
    private:
        Inventory a_inventory;
    public:
        ForagerBeast();
};

