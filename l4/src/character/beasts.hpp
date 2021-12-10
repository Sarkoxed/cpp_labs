#include "character.hpp"

class WildBeast: public Character{
    private:
        unsigned int a_damage;
    public:
        explicit WildBeast(std::vector<std::vector<unsigned int>>& config);
        unsigned int getDamage() const { return a_damage; };

        const bool isTrooper() const{ return false; }
        const bool isBeast() const { return true; }


};

class SmartBeast: public Character{
    private:
        Weapon* a_hands;
    public: 
        explicit SmartBeast(std::vector<std::vector<unsigned int>>& config);
        void pickItem(Weapon* item);
        Item* throwItem();

        unsigned int shoot(unsigned int dist);

        const bool isTrooper() const{ return false; }
        const bool isBeast() const { return true; }
};

class ForagerBeast: public Character{
    private:
        unsigned int a_strength;
        Inventory a_inventory;
    public:
        explicit ForagerBeast(std::vector<std::vector<unsigned int>>& config);
        void pickItem(Item* item, unsigned int num = 0);
        Item* throwItem(unsigned int num);

        const bool isTrooper() const{ return false; }
        const bool isBeast() const { return true; }


};

static std::vector<unsigned int> readcofig(const std::string& filename);
