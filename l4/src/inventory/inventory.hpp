// sarkoxed //
#pragma once

#include <map>

#include "weapon.hpp"
#include "medkit.hpp"
#include "bandolier.hpp"

class Inventory{
    private:
        unsigned int a_curweight;
        std::map<int, Item*> a_table;
    
};
