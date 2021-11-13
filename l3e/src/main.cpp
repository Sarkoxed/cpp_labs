// sarkoxed //
#include <string>
#include "fight.hpp"

void logo(){
    std::cout << "   ______           __                   _______       __    __ "      << std::endl;       
    std::cout << "  / ____/___  _____/ /__                / ____(_)___ _/ /_  / /_"      << std::endl;     
    std::cout << " / /   / __ \\/ ___/ //_/    ______     / /_  / / __ `/ __ \\/ __/"    << std::endl;       
    std::cout << "/ /___/ /_/ / /__/ ,<      /_____/    / __/ / / /_/ / / / / /_  "      << std::endl;      
    std::cout << "\\____/\\____/\\___/_/|_|               /_/   /_/\\__, /_/ /_/\\__/  " << std::endl;   
    std::cout << "                                             /____/             "      << std::endl;   
    std::cout << "  ______                                                  __    "      << std::endl;   
    std::cout << " /_  __/___  __  ___________  ____ _____ ___  ___  ____  / /_   "      << std::endl;  
    std::cout << "  / / / __ \\/ / / / ___/ __ \\/ __ `/ __ `__ \\/ _ \\/ __ \\/ __/   " << std::endl;
    std::cout << " / / / /_/ / /_/ / /  / / / / /_/ / / / / / /  __/ / / / /_     "      << std::endl;
    std::cout << "/_/  \\____/\\__,_/_/  /_/ /_/\\__,_/_/ /_/ /_/\\___/_/ /_/\\__/     " << std::endl;
    std::cout << "               No rooster was damaged. They are cock-fessionals!"      << std::endl;
}

int main(){
    srand(time(0));
    
    logo();
    
    std::string filename, ans;                         // getting file
    std::cout << "Input filename: ";
    getEl(filename);
    
    Table::ViewedTable players = genPlayers(filename); // generating players from the file
    
    std::ofstream file;
    std::cout << "Where should I save results?: ";
    getEl(filename);
    file.open(filename, std::ios::ate);                // FILE FOR RESULTS


    std::cout << "Do you wanna add any roosters?(yes/no): "; // adding extra players to the table

    getEl(ans);
    while(ans != "yes" and ans != "no"){
        std::cerr << "try, again: ";
        getEl(ans);
    }
    if(ans == "yes"){
       addExtraPlayers(players);    
    }

    std::cout << "There are " << players.size() << " players available!!!" << std::endl; 
    std::cout << "How many players do you want to participate?: ";
    int num;
    getEl(num);
    try{
        players = genTable(players, num, file);                     // creating a table according to inserted number
    }
    catch(const std::exception &e){
        std::cerr << "No competition this year. We haven't got enough applications" << std::endl; 
        exit(0);
    }
    
    std::cout << players << std::endl;                              // all the players for now

    int round = 1;
    while(players.size()){
        std::cout << std::endl << "####################### ROUND " << round << " #######################" << std::endl;
        fight(players, num, round++,  file);                        // well prepared fights 
    }
    std::cout << "#####################################################" << std::endl;
    return 0;
}
