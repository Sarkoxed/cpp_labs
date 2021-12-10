#include "inventory.hpp"

void Inventory::add(unsigned int inv, Item* it){
    auto tmp = a_table.find(inv);
    if(tmp != a_table.end() && a_table[inv] != nullptr){
        throw std::invalid_argument("this cell if full");
    }
    if(a_curweight + it->getWeight() > a_maxweight){
        throw std::out_of_range("not enough stamina");
    }

    a_table[inv] = it;
    a_curweight += it->getWeight();
    a_itcount++;
}


Item* Inventory::extract(unsigned int inv){
    auto tmp = a_table.find(inv);
    if(tmp != a_table.end() && a_table[inv] != nullptr){
       Item* tmp1 = a_table[inv];
       a_table[inv] = nullptr;
       a_curweight -= tmp1->getWeight();
       a_itcount--;
       return tmp1;
    }
    throw std::invalid_argument("this cell is empty");
}


Item* Inventory::operator[](unsigned int inv){
    auto tmp = a_table.find(inv);
    if(tmp != a_table.end() && a_table[inv] != nullptr){
        return a_table[inv];
    }
    throw std::out_of_range("no such an element");
}

Inventory::~Inventory(){
    for(auto i: a_table){
        delete i.second;
    }
}
