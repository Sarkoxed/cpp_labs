// sarkoxed //
#include "lib.hpp"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

ims getIms(){
    ims ans;
    ans.troop_im.loadFromFile("images/trooper.png");
    ans.floor_im.loadFromFile("images/floor.png");
    ans.glass_im.loadFromFile("images/glass.png");
    ans.wall_im.loadFromFile("images/wall.png");
    ans.baffle_im.loadFromFile("images/buffle.png");
    ans.john_im.loadFromFile("images/john.png");
    ans.khan_im.loadFromFile("images/khan.png");
    ans.anzan_im.loadFromFile("images/anzan.png"); ans.slava_im.loadFromFile("images/anzan.png");
    ans.mark_im.loadFromFile("images/mark.png");
    ans.gun_im.loadFromFile("images/ratata.png");
    ans.wild_im.loadFromFile("images/wild.png");
    ans.smart_im.loadFromFile("images/smart.png");
    ans.forager_im.loadFromFile("images/forager.png");
    ans.white_im.loadFromFile("images/white.png");
    ans.grey_im.loadFromFile("images/grey.png");
    ans.deadbe_im.loadFromFile("images/dead_be.png");
    ans.deadp_im.loadFromFile("images/dead_p.png");
    ans.pad_im.loadFromFile("images/pad.png");
    ans.win_im.loadFromFile("images/win.png");
    ans.lose_im.loadFromFile("images/lose.png");
    return ans;
}

texs getTex(ims& im){
    texs ans;
    ans.pad_tex.loadFromImage(im.pad_im);
    ans.troop_tex.loadFromImage(im.troop_im);
    ans.floor_tex.loadFromImage(im.floor_im);
    ans.glass_tex.loadFromImage(im.glass_im);
    ans.wall_tex.loadFromImage(im.wall_im);
    ans.baffle_tex.loadFromImage(im.baffle_im);
    ans.john_tex.loadFromImage(im.john_im);
    ans.khan_tex.loadFromImage(im.khan_im);
    ans.anzan_tex.loadFromImage(im.anzan_im);
    ans.slava_tex.loadFromImage(im.slava_im);
    ans.mark_tex.loadFromImage(im.mark_im);
    ans.gun_tex.loadFromImage(im.gun_im);
    ans.wild_tex.loadFromImage(im.wild_im);
    ans.smart_tex.loadFromImage(im.smart_im);
    ans.forager_tex.loadFromImage(im.forager_im);
    ans.white_tex.loadFromImage(im.white_im);
    ans.grey_tex.loadFromImage(im.grey_im);
    ans.deadbe_tex.loadFromImage(im.deadbe_im);
    ans.deadp_tex.loadFromImage(im.deadp_im);
    ans.win_tex.loadFromImage(im.win_im);
    ans.lose_tex.loadFromImage(im.lose_im);
    return ans;
}

void redrawPlane(Game& game, sf::RenderWindow& window, texs& tex, sf::Sprite& sprite){
    sf::Vector2f a;
    int hei = game.getLvl().getSize().second;
    int wid = game.getLvl().getSize().first;
    
    int radius = game.getCurPlayer()->getRadius();
    std::pair<unsigned int, unsigned int> pos  = game.getCurPos();
    
    sf::Font font;
    //font.loadFromFile("fonts/pacifico/Pacifico.ttf");
    font.loadFromFile("fonts/open-sans/OpenSans-Bold.ttf");
    //font.loadFromFile("fonts/SeasideResortNF/SEASRN__.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Red);

    for(int i = 0; i < hei; i++){
        for(int j = 0; j < wid; j++){
            auto ce = game.getLvl().getField().a_field[i][j];
            switch(ce.a_type){
                case cellType::floo:
                    sprite.setTexture(tex.floor_tex);
                    break;
                case cellType::glass:
                    sprite.setTexture(tex.glass_tex);
                    break;
                case cellType::wall:
                    sprite.setTexture(tex.wall_tex);
                    break;
                case cellType::baffle:
                    sprite.setTexture(tex.baffle_tex);
                    break;
                case cellType::storage:
                    sprite.setTexture(tex.floor_tex);
                    break;
            }
            text.setString("");
            if(ce.l_items.size() > 0 && (ce.a_type == cellType::floo || ce.a_type == cellType::storage)){
                if(ce.l_items.front()->isAmmo()){
                    text.setString("B");
                }
                else if(ce.l_items.front()->isMedkit()){
                    text.setString("M");
                }
                else if(ce.l_items.front()->isWeapon()){
                    text.setString("W");
                }
            }

            a.x = 32*j;
            a.y = 32*i;
            sprite.setPosition(a);
            window.draw(sprite);

            a.x = 32*j + 10;
            a.y = 32*i + 20;

            text.setPosition(a);
            window.draw(text);
        }
    }
    for(int j = 0; j < 16; j++){
    for(int i = 0; i < hei; i++){
        sprite.setTexture(tex.white_tex);
        a.x = 32*(wid + j);
        a.y = 32*i;
        sprite.setPosition(a);
        window.draw(sprite);
    }
    }
    std::vector<std::string> its = game.getLvl().getIt(pos.first, pos.second);
    for(int j = 0; j < 5; j++){
    for(int i = 0; i < wid+6; i++){
        sprite.setTexture(tex.white_tex);
        a.x = 32*i;
        a.y = 32*(hei + j);
        sprite.setPosition(a);
        window.draw(sprite);
    }
    }
    text.setFillColor(sf::Color::Black);
    int aa = 0;
    for(auto i: its){
        text.setString(i);
        a.x = 5;
        a.y = 10 + (aa++)*20 + 31*hei;
        text.setPosition(a);
        window.draw(text);
    }
    
    text.setFillColor(sf::Color::White);

    for(auto i: game.getLvl().getPlayers()){
        int dist = floor(sqrt(pow(static_cast<int>(pos.first - i.second.first),2) + pow(static_cast<int>(pos.second - i.second.second), 2)));
        if(game.a_team || (!game.a_team && (dist <= radius))){
            if(i.first->getCurHealth() == 0){
                sprite.setTexture(tex.deadp_tex);
            }
            else{
                sprite.setTexture(tex.troop_tex);
            }
            text.setString(i.first->getName()); 

            a.x = i.second.second * 32 + 5;
            a.y = i.second.first * 32 + 6;
            sprite.setPosition(a);
            window.draw(sprite);

            a.x = a.x;
            a.y = a.y - 5;
            text.setPosition(a);
            window.draw(text);
        }
    }
    
    
    for(auto i: game.getLvl().getEnemies()){
        int dist = floor(sqrt(pow(static_cast<int>(pos.first - i.second.first),2) + pow(static_cast<int>(pos.second - i.second.second), 2)));
        if(!game.a_team || (game.a_team && dist <= radius)){
            if(i.first->getCurHealth() != 0 ){
                if(i.first->isWild()){
                    sprite.setTexture(tex.wild_tex);
                }
                else if(i.first->isSmart()){
                    sprite.setTexture(tex.smart_tex);
                }
                else{
                    sprite.setTexture(tex.forager_tex);
                }
            }
            else{
                sprite.setTexture(tex.deadbe_tex);
            }
            a.x = i.second.second * 32 + 5;
            a.y = i.second.first * 32 + 5;
            sprite.setPosition(a);
            window.draw(sprite);
        }
    }

}

void handleEvents(Game& game, sf::RenderWindow& window, sf::Event& event, texs& tex){
    sf::Sprite sprite;
    unsigned int wid = game.getLvl().getSize().first;
    unsigned int hei = game.getLvl().getSize().second;
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
            window.close();
            return;
        }

        switch(event.type){
            case sf::Event::KeyPressed:
                {    
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    case sf::Keyboard::H:
                        game.action(Actions::mleft);
                        break;
                    case sf::Keyboard::J:
                        game.action(Actions::mdown);
                        break;
                    case sf::Keyboard::L:
                        game.action(Actions::mright);
                        break;
                    case sf::Keyboard::K:
                        game.action(Actions::mup);
                        break;
                    case sf::Keyboard::R:
                        {
                            sf::Vector2i pos = sf::Mouse::getPosition(window);
                            int po = (pos.x/32 - wid) + 16 * (pos.y / 32 - hei);
                            game.action(Actions::reload, po);
                            break;
                        }
                    case sf::Keyboard::S:
                        game.action(Actions::skip);
                        break;
                    case sf::Keyboard::P:
                        {
                            if(game.getCurPlayer()->isWild()){
                                break;
                            }
                            sf::Vector2i pos = sf::Mouse::getPosition(window);
                            int po = (pos.x/32 - wid) + 16 * (pos.y / 32 - hei);
                            game.action(Actions::picki, po);
                            break;
                        }
                    case sf::Keyboard::T:
                        {   
                            if(game.getCurPlayer()->isWild() || game.getCurPlayer()->isSmart()){
                                break;
                            }
                            sf::Vector2i pos = sf::Mouse::getPosition(window);
                            int po = (pos.x/32 - wid) + 16 * (pos.y / 32 - hei);
                            game.action(Actions::throwi, po);
                            break;
                        }
                    case sf::Keyboard::O:
                        {
                            sf::Vector2i pos = sf::Mouse::getPosition(window);
                            int po = (pos.x/32 - wid) + 16 * (pos.y / 32 - hei);
                            game.action(Actions::heal, po);
                            break;
                        }
                    default:
                        break;
                    }
                    break;
            }
            case sf::Event::MouseButtonPressed:
                {
                    sf::Vector2i pos = sf::Mouse::getPosition(window);
                    std::cout << pos.x / 32 << " " << pos.y/32 << std::endl;
                    game.action(Actions::shootxy, pos.y/32, pos.x/32);
                    break;
                }
            default:
                break;
        } 
                
        break;
        }
}


void drawInv(Game& game, sf::RenderWindow& window, texs& tex){
    if(game.getCurPlayer()->isWild() || game.getCurPlayer()->isSmart()){
        return;
    }
    sf::Vector2f a;
    int hei = game.getLvl().getSize().second;
    int wid = game.getLvl().getSize().first;
    Character* cha = game.getCurPlayer();
    sf::Font font;
    //font.loadFromFile("fonts/pacifico/Pacifico.ttf");
    font.loadFromFile("fonts/open-sans/OpenSans-Bold.ttf");
    //font.loadFromFile("fonts/SeasideResortNF/SEASRN__.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);

    int p = 0;
    std::vector<std::string> items;
    if(cha->isTrooper()){
        items = dynamic_cast<OpAgent*>(cha)->getInventory().toString();
    }
    else if(cha->isForager()){
        items = dynamic_cast<ForagerBeast*>(cha)->getInventory().toString();
    }
    else{
        return;
    }
    for(auto i: items){
        text.setString(i);
        a.x = (wid+5) * 32 + 6;
        a.y = (p++)*20 + 5;
        text.setPosition(a);
        window.draw(text);    
    }
}



void drawPad(Game& game,sf::RenderWindow& window,texs& tex){
    sf::Vector2f a;
    int hei = game.getLvl().getSize().second;
    int wid = game.getLvl().getSize().first;
    sf::Font font;
    //font.loadFromFile("fonts/pacifico/Pacifico.ttf");
    font.loadFromFile("fonts/open-sans/OpenSans-Bold.ttf");
    //font.loadFromFile("fonts/SeasideResortNF/SEASRN__.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(10);
    text.setFillColor(sf::Color::Black);
    sf::Sprite sprite;
    sprite.setTexture(tex.pad_tex);

    for(int i = hei; i < hei+5; i++){
        for(int j = wid; j < wid+16; j++){
            a.x = 32*j;
            a.y = 32*i;
            sprite.setPosition(a);
            window.draw(sprite);

            a.x = a.x + 16;
            a.y = a.y + 16;
            text.setPosition(a);
            int pos = (j - wid) + (i-hei) * 16;
            text.setString(std::to_string(pos));
            window.draw(text);
        }
    }

}

void drawLose(sf::RenderWindow &window, texs &tex){
    sf::Sprite sprite;
    sprite.setTexture(tex.lose_tex);
    sf::Vector2f a;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            a.x = j*200;
            a.y = i*200;
            sprite.setPosition(a);
            window.draw(sprite);
        }
    } 
 }

void drawWin(sf::RenderWindow &window, texs &tex){
    sf::Sprite sprite;
    sprite.setTexture(tex.win_tex);
    sf::Vector2f a;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            a.x = j*100;
            a.y = i*100;
            sprite.setPosition(a);
            window.draw(sprite);
        }
    }
}






void drawstats(Game& game, sf::RenderWindow& window){
    sf::Font font;
    //font.loadFromFile("fonts/pacifico/Pacifico.ttf");
    font.loadFromFile("fonts/open-sans/OpenSans-Bold.ttf");
    //font.loadFromFile("fonts/SeasideResortNF/SEASRN__.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);
    int width = game.getLvl().getSize().second;
    
    sf::Vector2f a;
    
    Character* ch = game.getCurPlayer();
    std::pair<unsigned int, unsigned int> pos = game.getCurPos();
    std::vector<std::string> stats = getStats(ch);
    stats.push_back(std::string("Current Position: ") + std::to_string(pos.first) + std::string(", ") + std::to_string(pos.second)); 
    for(int i = 0; i < stats.size(); i++){
        a.x = width*31 + 3;
        a.y = i*20;
        text.setString(stats[i]);
        text.setPosition(a);
        window.draw(text);                
    }
}

std::vector<std::string> getStats(Character* cha){
    std::vector<std::string> ans;
    ans.push_back(std::string("Health: ") + std::to_string(cha->getCurHealth()) + std::string(" \\ ") + std::to_string(cha->getMaxHealth()));
    
    ans.push_back(std::string("Time: ")+std::to_string(cha->getCurTime()) + std::string(" \\ ") + std::to_string(cha->getMaxTime()));
    ans.push_back(std::string("StepTime: ")+std::to_string(cha->getStepTime()));
    ans.push_back(std::string("Accuracy: ") + std::to_string(cha->getAccuracy()));
    ans.push_back(std::string("Radius: ")+ std::to_string(cha->getRadius()));

    if(cha->isTrooper()){
        auto ka = dynamic_cast<OpAgent*>(cha);
        ans.push_back("Stamina: " + std::to_string(ka->getCurWeight()) + std::string(" \\ ")  + std::to_string(ka->getStrength()));
        ans.push_back("CurObjects: " + std::to_string(ka->getInventory().getCurCount()));
        ans.push_back(std::string("ReloadTime: ") + std::to_string(ka->getRelTime()));
        if(ka->getHand()){
            ans.push_back(std::string("Carring Weapon: ") + std::to_string(static_cast<short>(ka->getHand()->getName())));
        }
    }
    else if(cha->isWild()){
        auto ka = dynamic_cast<WildBeast*>(cha);
        ans.push_back(std::string("Damage: ") + std::to_string(ka->getDamage()));
    }
    else if(cha->isSmart()){
        auto ka = dynamic_cast<SmartBeast*>(cha);
        if(ka->getHand()){
            ans.push_back(std::string("Carring Weapon: ") + std::to_string(static_cast<short>(ka->getHand()->getName())));
        }
    }
    else{
        auto ka = dynamic_cast<ForagerBeast*>(cha);
        ans.push_back(std::string("Stamina: ") + std::to_string(ka->getInventory().getCurWeight()) + std::string(" \\ ") + std::to_string(ka->getStrenght()));
    }
    return ans;
}

sf::Texture getName(const std::string& name, texs& tex){
        if(name == std::string("Anzan")){
            return tex.anzan_tex;
        }
        if(name == std::string("Khan")){
            return tex.khan_tex;
        }
        if(name == std::string("John")){
            return tex.john_tex;
        }
        if(name == std::string("Mark")){
            return tex.mark_tex;
        }
        if(name == std::string("Slava")){
            return tex.slava_tex;
        }
        return tex.mark_tex;
}
