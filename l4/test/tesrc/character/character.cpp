// sarkoxed //
#include "character.hpp"

void Character::recieveDamage(unsigned int dam){
    if(dam >= a_curhealth){
        a_curhealth = 0;
        throw std::out_of_range("dead");
    }
    a_curhealth -= dam;
}


void Character::resetTime(){
    a_curtime = a_maxtime;
}

void Character::setStepTime(unsigned int t){
    a_steptime = t;
}


void Character::makeStep(){
    if(a_curtime < a_steptime){
        throw std::out_of_range("not enough time");
    }
    a_curtime -= a_steptime;
}


void Character::decTime(unsigned int t){
    if(t > a_curtime){
        throw std::out_of_range("no more time");
    }
    a_curtime -= t;
}
