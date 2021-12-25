// sarkoxed //

#include "weapon.hpp"

Weapon::Weapon(nlohmann::json& js, WeaponType x, unsigned int curmag):a_name(x), a_mag(curmag){
    nlohmann::json tmp;
    if(!js.contains("a_damage")){
        short ind = static_cast<short>(x);
        tmp = js[ind];
        if(tmp.size() != 6){
            throw std::invalid_argument("no such a type");
        }
    }
    else{
        tmp = js;
    }

    
    a_damage = tmp["a_damage"];
    a_tshoot = tmp["a_tshoot"];
    a_treload = tmp["a_treload"];
    a_fullmag = tmp["a_fullmag"];
    a_weight = tmp["a_weight"];
    a_type = ItemType::weapon;
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

//wconfig readweapon(std::string filename){
//    std::ifstream fin;
//    fin.open(filename);
//    if(!fin.is_open()){
//        throw std::invalid_argument("no such a file");
//    }
//    wconfig config;
//    while(!fin.eof()){
//        try{
//            std::string string;
//            short type;
//            unsigned int val;
//            fin >> string;
//            fin >> type;
//            if(string == ""){
//                break;
//            }
//            for(int i = 0; i < 5; i++){
//                fin >> string;
//                fin >> val;
//                config[static_cast<WeaponType>(type)].push_back(val);
//            }
//        }
//        catch(const std::exception& e){
//            std::cout << e.what() << std::endl;
//        }
//    }
//    if(config.size() != 5){
//        throw std::invalid_argument("broken config");
//    }
//    return config;
//}
