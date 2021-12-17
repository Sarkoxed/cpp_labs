// sarkoxed //
#include <ostream>

#include "src/level/level.hpp"
int main(){
    srand(time(0));
    wconfig wep = readweapon("config/weapons.conf");
    opconfig op = readchar("config/oper.conf");
    bconfig be = readbea("config/beasts.conf");
    mapconfig ma = readmap("config/map.conf");

    Level lvl(ma, wep, op, be, 3);
    std::cout << lvl;
}
