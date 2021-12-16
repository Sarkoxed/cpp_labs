// sarkoxed //
//#include "../level/level.hpp"
#include <SFML/Graphics.hpp>


int main(){
   // wconfig wep = readweapon("../../config/weapons.conf");
   // opconfig op = readchar("../../config/oper.conf");
   // bconfig be = readbea("../../config/beasts.conf");
   // mapconfig ma = readmap("../../config/map.conf");

    //Level lvl(ma, wep, op, be, 3);


    sf::RenderWindow window(sf::VideoMode(800, 600), "operation");

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
                window.close();
            }
            window.clear();
            


            window.display();
        }
    }
}
