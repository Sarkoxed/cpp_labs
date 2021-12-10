// sarkoxed //
#include <gtest/gtest.h>
#include <cassert>
#include <ostream>

#include "../tesrc/items/item.hpp"
#include "../tesrc/items/medkit.hpp"
#include "../tesrc/items/bandolier.hpp"
#include "../tesrc/items/weapon.hpp"
#include "../tesrc/inventory/inventory.hpp"

TEST(item, weapon){
    std::map<WeaponType, std::vector<unsigned int>> x = readconfig("../config/weapons.conf");
    Weapon pist(WeaponType::pistol, x);
    
    // ned
    ASSERT_TRUE(pist.getDamage() == 233);
    ASSERT_TRUE(pist.getCurrentAmmo() == 0);
    ASSERT_TRUE(pist.getFullAmmo() == 13);
    ASSERT_TRUE(pist.getRelTime() == 230);
    ASSERT_TRUE(pist.getShootTime() == 31);
    ASSERT_TRUE(pist.getWeight() == 15);
    
    unsigned int band = 26, time = 1000;
    pist.reload(band, time);
    ASSERT_TRUE(band == 13);
    ASSERT_TRUE(pist.getCurrentAmmo() == 13);

    ASSERT_TRUE(pist.getShotResult(4, 2, 10));

    pist.makeShot(time);
    ASSERT_TRUE(pist.getCurrentAmmo() == 12);
    pist.reload(band, time);
    ASSERT_TRUE(band == 12);
    
    // my
    Weapon y(pist);
    ASSERT_TRUE(y.getCurrentAmmo() == 13);
    time = 0;
    EXPECT_ANY_THROW(pist.makeShot(time));
    ASSERT_FALSE(pist.isMedkit());
}


TEST(item, medkit){
    MedKit x(100, 14, 10);
    ASSERT_TRUE(x.isMedkit());
    ASSERT_TRUE(x.getHealTime() == 14);
    unsigned int ch = 17, mh = 100;
    x.decHeal(ch, mh);
    ASSERT_TRUE(x.getIncHealth() == 17);
    ASSERT_TRUE(ch == 100);
}

TEST(item, bandolier){
    Bandolier x(WeaponType::canon, 3, 5, 100);

    ASSERT_TRUE(x.getCurSize() == 3);
    ASSERT_TRUE(x.getMaxSize() == 5);

    x += 6;
    ASSERT_TRUE(x.getCurSize() == 5);
    ASSERT_TRUE(x.isAmmo());
    x-=1;
    ASSERT_TRUE(x.getCurSize() == 4);
    Bandolier y(WeaponType::canon, 2, 5, 75);
    Bandolier z(WeaponType::pistol, 10, 10, 10);
    
    EXPECT_ANY_THROW(x+=z);
    x+=y;
    ASSERT_TRUE(x.getCurSize() == 5);
    x-=5;
    EXPECT_ANY_THROW(x-=1);

}

TEST(inventory, all){
    std::map<WeaponType, std::vector<unsigned int>> x = readconfig("../config/weapons.conf");
    Weapon pist(WeaponType::pistol, x);
    Weapon rifle(WeaponType::rifle, x);
    Bandolier b(WeaponType::canon, 3, 5, 100);
    MedKit m(100, 14, 10);
    
    Inventory ma(0, 200);

    EXPECT_ANY_THROW(ma[3]);
    
    ASSERT_TRUE(ma.getCurWeight() == 0);
    ASSERT_TRUE(ma.getMaxWeight() == 200);

    ma.add(5, &pist);
    ASSERT_TRUE(ma.getCurCount() == 1);
    ASSERT_TRUE(ma.getCurWeight() == 15);

    EXPECT_ANY_THROW(ma.add(5, &rifle));

    ma.add(1, &rifle);
    ma.add(3, &b);
    ma.add(7, &m);

    ASSERT_TRUE(ma[1]->isWeapon());
    ASSERT_TRUE(ma[7]->isMedkit());
    ASSERT_TRUE(ma[3]->isAmmo());

    MedKit* l = dynamic_cast<MedKit*>(ma.extract(7));

    ASSERT_TRUE(l->isMedkit());
    EXPECT_ANY_THROW(ma[7]);
    ASSERT_TRUE(ma.getCurWeight() == pist.getWeight() + rifle.getWeight() + b.getWeight());
    EXPECT_ANY_THROW(ma.extract(10));
    EXPECT_ANY_THROW(ma.add(20, &b));
}


int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
