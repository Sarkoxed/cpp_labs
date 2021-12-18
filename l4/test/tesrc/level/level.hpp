#pragma once
#include <vector>
#include <list>

#include "../character/oper.hpp"
#include "../character/beasts.hpp"
#include "../template/vector.hpp"

enum cellType: short{
    floo = 0,
    wall = 1,
    glass = 2,
    baffle = 3,
    storage = 4
};

struct Cell{
    cellType a_type;
    std::list<Item*> l_items;
    Character* p_player;
};

struct Field{
    std::vector<Vec<Cell>> a_field;
    unsigned int width;
    unsigned int height;
};

typedef std::pair<std::pair<unsigned int, unsigned int>, std::vector<std::vector<cellType>>> mapconfig;

typedef std::vector<std::pair<std::vector<unsigned int>, std::pair<unsigned int, unsigned int>>> conftype;

typedef std::pair<std::vector<std::vector<unsigned int>>, std::pair<unsigned int, unsigned int>> lvlmapconfig;

struct lvlconfig{
    lvlmapconfig lvl;
    conftype chars;
    conftype items;
    conftype charitems;
};

class Level{
    private:
        Field a_field;
        std::list<std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>> l_players;
        std::list<std::pair<Character*, std::pair<unsigned int, unsigned int>>> l_enemies;
    public:
        explicit Level(const mapconfig& mconf, wconfig& wconf, opconfig& opconf, bconfig& bconf, unsigned int playernum);

        std::pair<unsigned int, unsigned int> getSize() const { return std::pair<unsigned int, unsigned int>(a_field.width, a_field.height);}

        void setSize(std::pair<unsigned int, unsigned int>);
        
        cellType getCellType(std::pair<unsigned int, unsigned int>) const;
        void setCellType(unsigned int x, unsigned int y, cellType t);

        void addItemToCell(unsigned int x, unsigned int y, Item* item);
        Item* getItemFromCell(unsigned int x, unsigned int y);

        unsigned int getOpCount(){return l_players.size();};
        unsigned int getBeCount(){return l_enemies.size();};

        Field& getField(){return a_field;};

        
        void destroy(unsigned int x, unsigned int y);
        void attack(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1);
        void changeCell(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1);
        void pickItem(unsigned int x, unsigned int y, unsigned int num);
        void throwItem(unsigned int x, unsigned int y);

        void save(const std::string& filename);

        ~Level();  

        friend std::ostream& operator<<(std::ostream& out, const Level& x);
};

mapconfig readmap(const std::string& filename);
std::list<Item*> genRandomThings(wconfig& wconf);
lvlconfig readlvl(const std::string& filename);
