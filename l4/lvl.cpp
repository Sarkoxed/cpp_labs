// sarkoxed //

#include "src/game/game.hpp"
#include <iostream>


int main(){
 //   srand(time(0));
 //   auto wep = getconf("config/weapons.json");
 //   auto op = getconf("config/oper.json");
 //   auto be = getconf("config/beasts.json");
 //   auto ma = getconf("config/map.json");

 //   Level lvl(ma, wep, op, be, 3);
    nlohmann::json cc = getconf("kuka2");
    Level lvl(cc);
    std::cout << lvl;
   // lvl.save("kuka2");

    Game g(lvl);
    while(true){
        int choice;
        std::cin >> choice;
        std::vector<Actions> a = {Actions::skip,Actions::mup, Actions::mdown, Actions::mright, Actions::mleft, Actions::picki, Actions::heal, Actions::reload, Actions::shootxy, Actions::throwi};
        if(!g.getEnd()){
            unsigned int x = 0, y = 0;
            if(choice == 8){
                std::cin >> x >> y;
            }
            g.action(a[choice], x, y);
            std::cout << lvl << std::endl;
        }
        else{
            g.newRound();
        }
    }
    std::cout << lvl << std::endl;
}
