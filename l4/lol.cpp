// sarkoxed //

#include <gtest/gtest.h>
#include <cassert>
#include <ostream>
#include <map>

#include "tools/toolib.hpp"
#include "src/items/item.hpp"
#include "src/items/medkit.hpp"
#include "src/items/bandolier.hpp" 
#include "src/items/weapon.hpp"
#include "src/inventory/inventory.hpp"
#include "src/character/character.hpp"
#include "src/character/oper.hpp"
#include "src/character/beasts.hpp"

int main(){
    std::map<WeaponType, std::vector<unsigned int>> x = readweapon("config/weapons.conf");
    std::pair<std::vector<std::string>, std::vector<std::vector<unsigned int>>> y = readchar("config/oper.conf");

    OpAgent a(y);
    //std::cout << a.getCurWeight() << std::endl;
    //std::cout << a.getMaxHealth() << std::endl;
    std::cout << a.getName() << std::endl;
    std::cout << a.getRelTime() << std::endl;
    std::cout << a.getStrength() <<std::endl;
}
