// sarkoxed //

#include "weapon.hpp"

Weapon::Weapon(WeaponType x,std::map<WeaponType,std::vector<unsigned int>>& config):a_name(x){
    a_type = weapon;
    a_mag = 0;

    if(config[x].size() != 5){
        throw std::invalid_argument("no such a type");
    }
    a_damage = config[x][0];
    a_tshoot = config[x][1];
    a_treload = config[x][2];
    a_fullmag = config[x][3];
    a_weight = config[x][4];
}


void Weapon::makeShot(unsigned int& time){
    if(time < a_tshoot){
        throw std::out_of_range("not enough time");
    }
    if(a_mag == 0){
        throw std::out_of_range("empty load");
    }    
    a_mag--;
    time -= a_tshoot;
}


const bool Weapon::getShotResult(unsigned int dist, unsigned int accuracy, unsigned int radius){
    return ((static_cast<double>(radius)/dist + static_cast<double>(5*a_weight) / a_damage) / 2.0) > 0.5; 
}


void Weapon::reload(unsigned int& ammo, unsigned int& time){
    if(a_mag == a_fullmag){
        return;
    }
    if(time < a_treload){
        throw std::out_of_range("not enough time");
    }
    unsigned int ned = a_fullmag - a_mag;
    if(ned >= ammo){
        ammo = 0;
        a_mag += ammo;
    }
    else{
        ammo -= ned;
        a_mag += ned;
    }
    time -= a_treload;
}

std::map<WeaponType, std::vector<unsigned int>> readconfig(std::string filename){
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    std::map<WeaponType, std::vector<unsigned int>> config;
    while(!fin.eof()){
        try{
            std::string string;
            short type;
            unsigned int val;
            fin >> string;
            fin >> type;
            for(int i = 0; i < 5; i++){
                fin >> string;
                fin >> val;
                config[static_cast<WeaponType>(type)].push_back(val);
            }
        }
        catch(const std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    if(config.size() != 5){
        throw std::invalid_argument("broken config");
    }
    return config;
}



