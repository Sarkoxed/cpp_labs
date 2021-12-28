#include "lib.hpp"
#include <SFML/Window/Keyboard.hpp>

int main(){
    
    std::string ccccc;
    //std::cin >> ccccc;
    ccccc = "rara2";
    nlohmann::json cc = getconf(ccccc);
    Level lvl(cc);
    Game game(lvl);

    int st = 6, it = 5, inv = 10;

    sf::RenderWindow window(sf::VideoMode(32*(lvl.getSize().first + st + inv), 32*(lvl.getSize().second + it)), "operation", sf::Style::Default);
    sf::Clock clock;
    float time;
    
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    time = clock.getElapsedTime().asMilliseconds();
    clock.restart();
     
    ims im = getIms();
    texs tex = getTex(im);
    
    sf::Sprite sprite;
    sf::Vector2f a;
    
    while(window.isOpen()){
        sf::Event event;
        window.clear();
        if(game.a_endr){
            game.newRound();
        }
        else if(game.getLvl().getPlayers().size() == 0){
            drawLose(window, tex);
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
                    window.close();
                }
            }

       }
        else if(game.getLvl().getEnemies().size() == 0){
            drawWin(window, tex);
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
                    window.close();
                }
            }


        }
        else{
            redrawPlane(game, window, tex, sprite);
            drawstats(game, window);
            drawPad(game, window, tex);
            drawInv(game, window, tex);
            handleEvents(game, window, event, tex);
        }

        window.display();
        }
}
