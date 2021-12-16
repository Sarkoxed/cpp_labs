// sarkoxed //

#include "toolib.hpp"
unsigned int randint(unsigned int a){
    srand(time(0)); 
    return random() % a;
}
