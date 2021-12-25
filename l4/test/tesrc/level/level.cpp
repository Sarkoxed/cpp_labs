// sarkoxed //
#include "level.hpp"
#include <stdexcept>

Level::Level(nlohmann::json& mconf, nlohmann::json& wconf, nlohmann::json& opconf, nlohmann::json& bconf, unsigned int playernum){
    if(playernum > mconf["width"]){
        throw std::invalid_argument("too much players, you need a bigger map");
    }
    a_field.width = mconf["width"];
    a_field.height = mconf["length"];

    for(int i = 0; i < mconf["length"]; i++){
        Vec<Cell> tmp(mconf["width"]);
        for(int j = 0; j < mconf["width"]; j++){
            Cell ttm;
            ttm.a_type = mconf["map"][i][j];

            if(ttm.a_type != cellType::wall){
                ttm.l_items = genRandomThings(wconf);
            }
            ttm.p_player = nullptr;
            tmp[j] = ttm;          
        }
        a_field.a_field.push_back(tmp);
    }

    std::list<std::pair<Character*, std::pair<unsigned int, unsigned int>>> beasts;
    std::list<std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>> players;
    for(int i = 0; i < playernum; i++){
        std::pair<unsigned int, unsigned int> r(0, i);
        std::pair<OpAgent*, std::pair<unsigned int, unsigned int>> zozo(new OpAgent(opconf), r);
        players.push_back(zozo);
        a_field.a_field[0][i].p_player = zozo.first;
    }
   
    for(int i = 0; i < playernum + (playernum / 2); i++){
        std::pair<unsigned int, unsigned int> r;
        while(true){
            r.first = randint(mconf["length"]);
            r.second = randint(mconf["width"]);
            if(a_field.a_field[r.first][r.second].a_type == cellType::floo && a_field.a_field[r.first][r.second].p_player == nullptr){
                break;
            }
        }
        int l = randint(10000);
        std::pair<Character*, std::pair<unsigned int, unsigned int>> pupa;
        pupa.second = r;
        if(l < 3333){
            pupa.first = new WildBeast(bconf);
        }
        else if(l >= 3333 && l < 6666){
            pupa.first = new SmartBeast(bconf);
        }
        else{
            pupa.first = new ForagerBeast(bconf);
        }
        beasts.push_back(pupa);
        a_field.a_field[r.first][r.second].p_player = pupa.first;
    }
    l_players = players;
    l_enemies = beasts;
}

Level::~Level(){
    for(auto i: l_players){
        delete i.first;
    }
    for(auto i: l_enemies){
        delete i.first;
    }
    for(auto i: a_field.a_field){
        for(auto j: i){
            for(auto k: j.l_items){
                delete k;
            }
        }
    }
}


std::list<Item*> genRandomThings(nlohmann::json& wconf){
    int x = randint(1000);
    int y = randint(1000);
    if(y < 500){
        return std::list<Item*>();
    }
    Item* m;
    if(x < 333){
        int l = randint(4);
        m = new Weapon(wconf, static_cast<WeaponType>(l));
    }
    else if(x >= 334 && x < 666){
        int he = randint(200);
        int ht = 10 + randint(50);
        int w = 50 + randint(100);
        m = new MedKit(he, ht, w);
    }
    else{
        int l = randint(4);
        int max = randint(100);
        int s = randint(max);
        int w = randint(200);
        m = new Bandolier(static_cast<WeaponType>(l), s, max, w);
    }
    std::list<Item*> ans;
    ans.push_back(m);
    return ans;
}

Level::Level(const nlohmann::json& js){
    unsigned int width, height;
    width = js["width"];
    height = js["length"];
    a_field.width = width;
    a_field.height = height;

    unsigned int x0 = 0, y0 = 0;
    for(auto i: js["map"]){
        Vec<Cell> cells;
        for(auto j: i){
            Cell x;
            x.a_type = static_cast<cellType>(j["type"]);
            x.p_player = nullptr;
            if(j.contains("items")){
                for(auto it: j["items"]){
                    ItemType type = static_cast<ItemType>(it["type"]);
                    Item* tmp;
                    if(type == ItemType::weapon){ 
                        tmp = new Weapon(it, static_cast<WeaponType>(it["a_name"]));
                    }
                    else if(type == ItemType::medkit){
                        tmp = new MedKit(it["increasing"], it["heltime"], it["a_weight"]); 
                    }
                    else{
                        auto tp = static_cast<WeaponType>(it["a_name"]);
                        tmp = new Bandolier(tp, it["a_cursize"], it["a_maxsize"], it["a_weight"]);
                    }
                    x.l_items.push_back(tmp);
                }
            }
            if(j.contains("person")){
                short type = j["person"]["type"];
                std::pair<unsigned int, unsigned int> r(x0, y0);
                if(type == 0){
                    x.p_player = new OpAgent(j["person"]);
                    l_players.push_back(std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>(dynamic_cast<OpAgent*>(x.p_player), r));
                }
                else if(type == 1){
                    x.p_player = new WildBeast(j["person"]);
                    l_enemies.push_back(std::pair<Character*, std::pair<unsigned int, unsigned int>>(x.p_player, r));
                }
                else if(type == 2){
                    x.p_player = new SmartBeast(j["person"]);
                    l_enemies.push_back(std::pair<Character*, std::pair<unsigned int, unsigned int>>(x.p_player, r));
                }
                else if(type == 3){
                    x.p_player = new ForagerBeast(j["person"]);
                    l_enemies.push_back(std::pair<Character*, std::pair<unsigned int, unsigned int>>(x.p_player, r));
                }
            }
            cells.pushBack(x);            
            x0++;
        }
        a_field.a_field.push_back(cells);
        
        y0++;
    }
}

nlohmann::json getJsonOfItems(OpAgent* agent){
    nlohmann::json items;
    std::vector<nlohmann::json> inventory;
    for(auto k: *(agent)->getInventory().getTable()){
        nlohmann::json tmp2;
        if(k.second->isWeapon()){
            auto wep = dynamic_cast<Weapon*>(k.second);
            tmp2 = {
                {"type", 0},
                {"a_name", static_cast<short>(wep->getName())},
                {"a_damage", wep->getDamage()},
                {"a_tshoot", wep->getShootTime()},
                {"a_treload", wep->getRelTime()},
                {"a_fullmag", wep->getFullAmmo()},
                {"a_curmag", wep->getCurrentAmmo()},
                {"a_weight", wep->getWeight()},
                {"num", k.first}
            };
        }
        else if(k.second->isMedkit()){
            auto med = dynamic_cast<MedKit*>(k.second);
            tmp2 = {
                {"type", 1},
                {"increasing", med->getIncHealth()},
                {"heltime", med->getHealTime()},
                {"a_weight", med->getWeight()},
                {"num", k.first}
            };
        }
        else{
            auto band = dynamic_cast<Bandolier*>(k.second);
            tmp2 = {
                {"type", 2},
                {"a_weight", band->getWeight()},
                {"a_maxsize", band->getMaxSize()},
                {"a_cursize", band->getCurSize()},
                {"a_name", band->getType()},
                {"num", k.first}
            };
        }
        inventory.push_back(tmp2);
    }
    items["inventory"] = inventory;
    
    if(agent->getHand()){
        auto wep = dynamic_cast<Weapon*>(agent->getHand());
        items["hands"] = {
            {"type", 0},
            {"a_name", static_cast<short>(wep->getName())},
            {"a_damage", wep->getDamage()},
            {"a_tshoot", wep->getShootTime()},
            {"a_treload", wep->getRelTime()},
            {"a_fullmag", wep->getFullAmmo()},
            {"a_curmag", wep->getCurrentAmmo()},
            {"a_weight", wep->getWeight()}
        };
    }
    return items;
}

void Level::save(const std::string& filename){
    nlohmann::json save, map;
    save["width"] = a_field.width;
    save["length"] = a_field.height;
    save["map"] = std::vector<std::vector<nlohmann::json>>();
    for(auto i: a_field.a_field){
        std::vector<nlohmann::json> lines = std::vector<nlohmann::json>();

        for(auto j: i){
            nlohmann::json cell;

            cell["items"] = std::vector<nlohmann::json>();
            cell["type"] = static_cast<short>(j.a_type);

            for(auto k: j.l_items){
                nlohmann::json cellitems;
                if(k->isWeapon()){
                    auto wep = dynamic_cast<Weapon*>(k);
                    cellitems["type"] = 0;
                    cellitems["a_name"] = static_cast<short>(wep->getName());
                    cellitems["a_damage"] = wep->getDamage();
                    cellitems["a_tshoot"] = wep->getShootTime();
                    cellitems["a_treload"] = wep->getRelTime();
                    cellitems["a_fullmag"] = wep->getFullAmmo();
                    cellitems["a_curmag"] = wep->getCurrentAmmo();
                    cellitems["a_weight"] = wep->getWeight();
                }
                else if(k->isMedkit()){
                    auto med = dynamic_cast<MedKit*>(k);
                    cellitems["type"] = 1;
                    cellitems["increasing"] = med->getIncHealth();
                    cellitems["heltime"] = med->getHealTime();
                    cellitems["a_weight"] = med->getWeight();
                }
                else{
                    auto bond = dynamic_cast<Bandolier*>(k);
                    cellitems["type"] = 2;
                    cellitems["a_weight"] = bond->getWeight();
                    cellitems["a_maxsize"] = bond->getMaxSize();
                    cellitems["a_cursize"] = bond->getCurSize();
                    cellitems["a_name"] = bond->getType();
                }
                cell["items"].push_back(cellitems);
            }

            nlohmann::json person;
            if(j.p_player){
                auto piri = j.p_player;
                person = {
                    {"a_maxhealth", {piri->getMaxHealth()}},
                    {"a_curhealth", {piri->getCurHealth()}},
                    {"a_maxtime",   {piri->getMaxTime()}},
                    {"a_curtime",   {piri->getCurTime()}},
                    {"a_radius",    {piri->getRadius()}},
                    {"a_steptime",  {piri->getStepTime()}},
                    {"a_accuracy",  {piri->getAccuracy()}}                        
                };

                if(piri->isTrooper()){
                    auto trooper = dynamic_cast<OpAgent*>(piri);
                    person["type"]  = 0;
                    person["a_name"] = {trooper->getName()};
                    person["a_strength"] = {trooper->getStrength()};
                    person["a_reloadtime"] = {trooper->getRelTime()};
                    person["a_curweight"] = {trooper->getCurWeight()};

                    person["items"] = getJsonOfItems(trooper);
                }
                else if(j.p_player->isWild()){
                    person["type"] = 1;
                    person["a_damage"] = {dynamic_cast<WildBeast*>(j.p_player)->getDamage()};
                }
                else if(j.p_player->isForager()){
                    person["type"] = 3;
                    person["a_strength"] = {dynamic_cast<ForagerBeast*>(j.p_player)->getStrenght()};
                }
                else{
                    person["type"] = 2;
                }

                
                if(j.p_player->isSmart()){
                    auto smart = dynamic_cast<SmartBeast*>(j.p_player);
                    if(smart->getHand()){
                        auto hand = dynamic_cast<Weapon*>(smart->getHand());
                        person["items"]["hands"]["type"] = 0;
                        person["items"]["hands"]["a_name"] = static_cast<short>(hand->getName());
                        person["items"]["hands"]["a_damage"] = hand->getDamage();
                        person["items"]["hands"]["a_tshoot"] = hand->getShootTime();
                        person["items"]["hands"]["a_treload"] = hand->getRelTime();
                        person["items"]["hands"]["a_fullmag"] = hand->getFullAmmo();
                        person["items"]["hands"]["a_curmag"] = hand->getCurrentAmmo();
                        person["items"]["hands"]["a_weight"] = hand->getWeight();         
                    }
                }

                if(j.p_player->isForager()){
                    person["items"] = std::vector<nlohmann::json>();
                    for(auto k: *(dynamic_cast<ForagerBeast*>(j.p_player))->getInventory().getTable()){
                        nlohmann::json foreageritems;
                        if(k.second->isWeapon()){
                            auto wep = dynamic_cast<Weapon*>(k.second);
                            foreageritems["type"] = 0;
                            foreageritems["a_name"] = static_cast<short>(wep->getName());
                            foreageritems["a_damage"] = wep->getDamage();
                            foreageritems["a_tshoot"] = wep->getShootTime();
                            foreageritems["a_treload"] = wep->getRelTime();
                            foreageritems["a_fullmag"] = wep->getFullAmmo();
                            foreageritems["a_curmag"] = wep->getCurrentAmmo();
                            foreageritems["a_weight"] = wep->getWeight();
                        }
                        else if(k.second->isMedkit()){
                            auto med = dynamic_cast<MedKit*>(k.second);
                            foreageritems["type"] = 1;
                            foreageritems["increasing"] = med->getIncHealth();
                            foreageritems["heltime"] = med->getHealTime();
                            foreageritems["a_weight"] = med->getWeight();
                        }
                        else{
                            auto bond = dynamic_cast<Bandolier*>(k.second);
                            foreageritems["type"] = 2;
                            foreageritems["a_weight"] = bond->getWeight();
                            foreageritems["a_maxsize"] = bond->getMaxSize();
                            foreageritems["a_cursize"] = bond->getCurSize();
                            foreageritems["a_name"] = bond->getType();
                        }
                        person["items"].push_back(foreageritems);
                    }
                }
                cell["person"] = person;
            }
            lines.push_back(cell);
        }
        save["map"].push_back(lines);
    }
    saveconf(save, filename);
}

std::ostream& operator<<(std::ostream& out, const Level& x){
    std::string str(" #^-");
    for(auto i: x.a_field.a_field){
        for(auto j: i){
            out << "****";
        }
        out << std::endl;
        for(auto j: i){
            out << "*";
            if(j.a_type != cellType::floo && j.a_type != cellType::storage){
                char c = str.c_str()[static_cast<int>(j.a_type)];
                out << c << c << c;
            }
            else if(j.a_type == cellType::floo){
                out << "   ";
            }
            else{
                out << "@ @";
            }
        }
        out << std::endl;
        for(auto j: i){
            out << "*";
            if(j.a_type != cellType::floo && j.a_type != cellType::storage){
                char c = str.c_str()[static_cast<int>(j.a_type)];
                out << c << c << c;
            }
            else if(j.p_player == nullptr){
                out << "   ";
            }
            else if(j.p_player->isTrooper()){
                out << " O ";
            }
            else if(j.p_player->isBeast()){
                if(j.p_player->isWild()){
                    out << " W ";
                }
                else if(j.p_player->isSmart()){
                    out << " S ";
                }
                else{
                    out << " F ";    
                }
            }
        }
        out << std::endl;
        for(auto j: i){
            out << "*";
            if(j.a_type != cellType::floo && j.a_type != cellType::storage){
                char c = str.c_str()[static_cast<int>(j.a_type)];
                out << c << c << c;
            }
            else if(j.l_items.size() == 0){
                out << "   ";
            }
            else if(j.l_items.front()->isWeapon()){
                out << "A  ";
            }
            else if(j.l_items.front()->isMedkit()){
                out << " M ";
            }
            else{
                out << "  B";
            }
        }
        out << std::endl;
    }

    for(auto i: x.a_field.a_field){
        out << "***";
    }
    out << std::endl;
    return out;
}


void Level::destroy(unsigned int x, unsigned int y){
    if(a_field.a_field[x][y].a_type == cellType::glass || a_field.a_field[x][y].a_type == cellType::baffle){
        a_field.a_field[x][y].a_type = cellType::floo;
        return;
    }
    throw std::invalid_argument("you cannot destroy it");
}


void Level::changeCell(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1){
    if(a_field.a_field[x1][y1].p_player == nullptr){
        std::swap(a_field.a_field[x1][y1].p_player,a_field.a_field[x][y].p_player);
        for(auto i: l_players){
            if(i.second.first == x && i.second.second == y){
                i.second = std::pair<unsigned int, unsigned int>(x1, y1);
            }
        }
        return;
    }
    throw std::out_of_range("YOU SHALL NOT PASS");
}



void Level::attack(unsigned int x, unsigned int y, unsigned int x1, unsigned int y1){
    Character* a = a_field.a_field[x][y].p_player;
    Character* b = a_field.a_field[x1][y1].p_player;
    if((a->isTrooper() && b->isTrooper()) || (a->isBeast() && b->isBeast())){
        throw std::invalid_argument("friendly fire");
    }
    unsigned int dist = floor(sqrt(pow(x-x1, 2) + pow(y-y1,2)));
    if(dist > a->getRadius()){
        throw std::invalid_argument("this might not happen");
    }


    unsigned int res;
    if(a->isTrooper()){
        res = dynamic_cast<OpAgent*>(a)->shoot(dist);
    }
    else if(a->isSmart()){
        res = dynamic_cast<SmartBeast*>(a)->shoot(dist);
    }
    else if(a->isWild()){
        res = dynamic_cast<WildBeast*>(a)->getDamage();
    }
    else{ 
        throw std::invalid_argument("not an attackable");
    }
    b->recieveDamage(res);
}


void Level::pickItem(unsigned int x, unsigned int y, unsigned int num, Item* it){
    Character* p = a_field.a_field[x][y].p_player;
    if(p->isWild()){
        throw std::invalid_argument("not a pickable");
    }
    else if(p->isSmart()){
        dynamic_cast<SmartBeast*>(p)->takeItem(dynamic_cast<Weapon*>(it));
        return;
    }
    else if(p->isTrooper()){
        dynamic_cast<OpAgent*>(p)->pickItem(it, num);
    }
    else{
        dynamic_cast<ForagerBeast*>(p)->pickItem(it, num);
    }
}

void Level::throwItem(unsigned int x, unsigned int y, Item* it){
    a_field.a_field[x][y].l_items.push_back(it);
}




