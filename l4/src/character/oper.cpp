// sarkoxed //
#include "oper.hpp"


OpAgent::OpAgent(opconfig& config){
    unsigned int num = randint(config.second[0].size()-1);
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

    a_inventory = Inventory(0, a_strength, 0);
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
        return;
    }
    throw std::invalid_argument("not a weapon");
}

void OpAgent::pickItem(Item* item, unsigned int num){
    if(a_hands != nullptr){
        if(a_hands->getWeight() + a_curweight + item->getWeight() > a_strength){
            throw std::out_of_range("not enough stamina");
        }
    }
    a_inventory.add(num, item);
    a_curweight += item->getWeight(); 
}

Item* OpAgent::throwItem(unsigned int num){
    if(num == 0){
        Item* tmp = a_hands;
        a_hands = nullptr;
        a_curweight -= tmp->getWeight();
        return tmp;
    }
    Item* tmp = a_inventory.extract(num);
    a_curweight -= tmp->getWeight();
    return tmp;
}

Item* OpAgent::throwHand(){
    if(a_hands == nullptr){
        throw std::out_of_range("nothing to throw");
    }
    Item* tmp = a_hands;
    a_hands = nullptr;
    a_curweight -= tmp->getWeight();
    return tmp;
}


void OpAgent::reload(Bandolier& ammo){
    unsigned int a = ammo.getCurSize();
    a_hands->reload(a, a_curtime);
    ammo -= (ammo.getCurSize() - a);
}

void OpAgent::heal(MedKit& med){
    med.decHeal(a_curhealth, a_maxhealth);
}

unsigned int OpAgent::shoot(unsigned int dist){
    a_hands->makeShot(a_curtime);
    if(a_hands->getShotResult(dist, a_accuracy, a_radius)){
        return a_hands->getDamage();
    }
    return 0;
}

opconfig readchar(const std::string& filename){
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    
    std::vector<std::vector<unsigned int>> cha;
    int count;
    fin >> count;
    
    std::vector<std::string> names;
    std::string name;
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
    opconfig config(names, cha); 
    return config;
}

