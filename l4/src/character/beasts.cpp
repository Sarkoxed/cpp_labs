// sarkoxed //
#include "beasts.hpp"

unsigned int randint(unsigned int a){
    return random() % a;
}


WildBeast::WildBeast(std::vector<std::vector<unsigned int>>& config){
    srand(time(0));
    unsigned int num = randint(config[0].size());
    int j = 0;
    a_maxhealth = config[j++][num];
    a_curhealth = a_maxhealth;
    a_maxtime = config[j++][num];
    a_curtime = a_maxtime;
    a_steptime = config[j++][num];
    a_radius = config[j++][num];
    a_accuracy = config[j++][num];
    a_damage = randint(200);
}


SmartBeast::SmartBeast(std::vector<std::vector<unsigned int>>& config){
    srand(time(0));
    unsigned int num = randint(config[0].size());
    int j = 0;
    a_maxhealth = config[j++][num];
    a_curhealth = a_maxhealth;
    a_maxtime = config[j++][num];
    a_curtime = a_maxtime;
    a_steptime = config[j++][num];
    a_radius = config[j++][num];
    a_accuracy = config[j++][num];
    a_hands = nullptr;
}


ForagerBeast::ForagerBeast(std::vector<std::vector<unsigned int>>& config){
    srand(time(0));
    unsigned int num = randint(config[0].size());
    int j = 0;
    a_maxhealth = config[j++][num];
    a_curhealth = a_maxhealth;
    a_maxtime = config[j++][num];
    a_curtime = a_maxtime;
    a_steptime = config[j++][num];
    a_radius = config[j++][num];
    a_accuracy = config[j++][num];
    a_strength = randint(400);
}


void SmartBeast::pickItem(Weapon* wep){
    if(a_hands){
        throw std::out_of_range("full hands");
    }
    a_hands = wep;
}

Item* SmartBeast::throwItem(){
    Weapon* tmp = a_hands;
    a_hands = nullptr;
    return tmp;
}

unsigned int SmartBeast::shoot(unsigned int dist){
    if(a_hands->getShotResult(dist, a_accuracy, a_radius)){
        a_hands->makeShot(a_curtime);
        return a_hands->getDamage();
    }
    return 0;
}

void ForagerBeast::pickItem(Item* item, unsigned int num){
    if(num == 0){
        num = a_inventory.getCurCount() + 1;
    }
    a_inventory.add(num, item);
}

Item* ForagerBeast::throwItem(unsigned int num){
    return  a_inventory.extract(num);

}

static std::vector<std::vector<unsigned int>> readconfig(const std::string& filename){
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    
    std::vector<std::vector<unsigned int>> cha;
    int count;
    fin >> count;
    std::string name;
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
    return cha;
}
