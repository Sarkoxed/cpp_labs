#pragma once
#include <vector>
#include <list>
#include "../character/character.hpp"

enum cellType: short{
    floor = 0,
    wall = 1,
    glass = 2,
    baffle = 3,
    storage = 4
};

class Cell{
    private:
        cellType a_type;
        std::list<Item> l_items;
    public:
        Cell();
};

struct Field{
    std::vector<std::vector<Cell>> a_field;
    unsigned int width;
    unsigned int height;
};

class level{
    private:
        Field a_field;
        std::list<std::string> l_orders;
    public:
        level();

        std::pair<unsigned int, unsigned int> getSize() const { return std::pair<unsigned int, unsigned int>(a_field.width, a_field.height);}
        void setSize(std::pair<unsigned int, unsigned int>);
        
        cellType getCellType(std::pair<unsigned int, unsigned int>) const;
        void setCellType(unsigned int x, unsigned int y, cellType t);

        void addItemToCell(unsigned int x, unsigned int y, Item* item);
        Item* getItemFromCell(unsigned int x, unsigned int y, itemType t);
};
