// sarkoxed //
#include "oper.hpp"

unsigned int randint(unsigned int a){
    return random() % a;
}


OpAgent::OpAgent(std::pair<std::vector<std::string>, std::vector<std::vector<unsigned int>>>& config){
    srand(time(0));
    unsigned int num = randint(config.second.size());
    int j = 0;
    a_name = config.first[num];
    a_strength = config.second[j++][num];
    a_maxhealth = config.second[j++][num];
    a_curhealth = a_maxhealth;
    a_maxtime = config.second[j++][num];
    a_curtime = a_maxtime;
    a_steptime = config.second[j++][num];
    a_radius = config.second[j++][num];
    a_accuracy = config.second[j++][num];
    a_reloadtime = 0;
    a_curweight = 0;
    a_hands = nullptr;
}

void OpAgent::setReload(unsigned int rel){
    a_reloadtime = rel;
}

void OpAgent::changeWeight(unsigned int weigh){
    a_curweight = weigh;
}

void OpAgent::chooseItemToHold(unsigned int num){
    if(a_inventory[num]->isWeapon()){
        Weapon* w = dynamic_cast<Weapon*>(a_inventory.extract(num));
        a_inventory.add(num, a_hands);
        a_hands = w;
        a_reloadtime = w->getRelTime();
    }
    throw std::invalid_argument("not a weapon");
}

void OpAgent::pickItem(Item* item, unsigned int num){
    a_inventory.add(num, item);
}

Item* OpAgent::throwItem(unsigned int num){
    return a_inventory.extract(num);
}


void OpAgent::reload(Bandolier& ammo){
    unsigned int a = ammo.getCurSize();
    a_hands->reload(a, a_curtime);
    ammo -= ammo.getCurSize() - a;
}

void OpAgent::heal(MedKit& med){
    med.decHeal(a_curhealth, a_maxhealth);
}

unsigned int OpAgent::shoot(unsigned int dist){
    if(a_hands->getShotResult(dist, a_accuracy, a_radius)){
        a_hands->makeShot(a_curtime);
        return a_hands->getDamage();
    }
    return 0;
}

static std::pair<std::vector<std::string>, std::vector<std::vector<unsigned int>>> readconfig(const std::string& filename){
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    
    std::vector<std::string> names(5);
    std::vector<std::vector<unsigned int>> cha;
    int count;
    fin >> count;
    std::string name;
    fin >> name;
    for(int i = 0; i < count; i++){
        fin >> name;
        names.push_back(name);
    }
    while(!fin.eof()){
        try{
            unsigned int val;
            fin >> name;
            std::vector<unsigned int> vals;
            for(int i = 0; i < count; i++){
                fin >> val;
                vals.push_back(val);
            }
            cha.push_back(vals);
        }
        catch(const std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    std::pair<std::vector<std::string>, std::vector<std::vector<unsigned int>>> config; 
    return config;
}

