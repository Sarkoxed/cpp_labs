#pragma once

enum WeaponType: short{
    pistol = 0, 
    rifle = 1, 
    shotgun = 2, 
    canon = 3,
    grenade = 4
};

enum itemType: short{
    weapon = 0,
    medkit = 1,
    bandelier = 2
};


class Item{
    protected:
        itemType a_type;
        unsigned int a_weight;

};
