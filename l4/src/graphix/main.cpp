#include "../game/game.hpp"
#include <SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "operation", sf::Style::Default);
   sf::Clock clock;
   float time;

   window.setVerticalSyncEnabled(true);
   window.setFramerateLimit(60);

   time = clock.getElapsedTime().asMilliseconds();
   clock.restart();


   while(window.isOpen()){
       sf::Event event;
       while(window.pollEvent(event)){
           if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
               window.close();
               break;
           }

           switch(event.type){
               case sf::Event::KeyPressed:
                   if(event.key.code == sf::Keyboard::Escape){
                       window.close();
                   }
                   break;
           }

           //update
           
           //render           
           window.clear(sf::Color::Black);

           //Draw a game
           window.display();
       }
   }
}/ sarkoxed //
