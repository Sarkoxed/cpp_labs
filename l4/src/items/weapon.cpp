// sarkoxed //

#include "weapon.hpp"

void Weapon::readconfig(std::string filename){
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    while(true){
        try{
            std::string string;
            short type;
            unsigned int val;
            getEl(string, fin);
            getEl(type, fin);
            for(int i = 0; i < 5; i++){
                getEl(string, fin);
                getEl(val, fin);
                m_config[static_cast<short>(type)].push_back(val);
            }
        }
        catch(const std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    if(m_config.size() != 5){
        throw std::invalid_argument("broken config");
    }
}


Weapon::Weapon(WeaponType x):a_name(x){
    a_type = weapon;
    a_mag = 0;
    if(m_config[static_cast<short>(x)].size() != 5){
        throw std::invalid_argument("no such a type");
    }
    a_damage = m_config[static_cast<short>(x)][0];
    a_tshoot = m_config[static_cast<short>(x)][1];
    a_treload = m_config[static_cast<short>(x)][2];
    a_fullmag = m_config[static_cast<short>(x)][3];
    a_weight = m_config[static_cast<short>(x)][4];
}


void Weapon::makeShot(){
    if(a_mag == 0){
        throw std::out_of_range("empty load");
    }    
    a_mag--;
}


const bool Weapon::getShotResult(unsigned int dist, unsigned int accuracy, unsigned int radius){
    return ((static_cast<double>(radius)/dist + static_cast<double>(a_damage) / a_weight) / 2.0) > 0.5; 
}


void Weapon::reload(unsigned int& ammo){
    unsigned int ned = a_fullmag - a_mag;
    a_mag = (a_mag + ammo) % a_fullmag;
    ammo = (ammo < ned) ? 0 : (ammo - ned);
}


