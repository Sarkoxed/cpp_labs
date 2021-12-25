// sarkoxed //

#include "src/character/beasts.hpp"
#include "src/level/level.hpp"
#include <iostream>


int main(){
    srand(time(0));
   auto wep = getconf("config/weapons.json");
   auto op = getconf("config/oper.json");
   auto be = getconf("config/beasts.json");
   auto ma = getconf("config/map.json");

   Level lvl(ma, wep, op, be, 3);
   std::cout << lvl;
   lvl.save("kuka");

   nlohmann::json js = getconf("kuka");
   Level test(js);
   std::cout << std::endl << test;
   test.save("kuka1");
}
