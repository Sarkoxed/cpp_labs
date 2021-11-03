// sarkoxed //
#include <string>

#include "fight.hpp"

int main(){
    std::string name, ans;
    std::cout << "Input filename: ";
    getEl(name);
    
    Table::ViewedTable players = genPlayers(name);
    
    std::cout << "Do you wanna add any roosters?(yes/no): ";
    getEl(ans);
    while(ans != "yes" and ans != "no"){
        std::cerr << "try, again: ";
        getEl(ans);
    }
    
    if(ans == "yes"){
       addExtraPlayers(players); 
    }
    
    std::cout << "How many players do you want to participate?: ";
    int n;
    getEl(n);
    makePowerOfTwo(n);
    try{
        players = genTable(players, n);
    }
    catch(const std::exception &e){
        std::cerr << "No competition this year. We've not got enough applications" << std::endl; 
        exit(0);
    }
//todo: while cycle while one in the end
//how to keep record of wins?
//how to save after all defeats?
}


