// sarkoxed //
#include "level.hpp"

Level::Level(const mapconfig& mconf, wconfig& wconf, opconfig& opconf, bconfig& bconf, unsigned int playernum){
    if(playernum > mconf.first.first){
        throw std::invalid_argument("too much players, you need a bigger map");
    }

    for(int i = 0; i < mconf.first.second; i++){
        Vec<Cell> tmp(mconf.first.first);
        for(int j = 0; j < mconf.first.first; j++){
            Cell ttm;
            ttm.a_type = mconf.second[i][j];
            ttm.l_items = genRandomThings(wconf);
            ttm.p_player = nullptr;
            tmp[j] = ttm;
        }
        a_field.a_field.push_back(tmp);
    }

    std::list<std::pair<Character*, std::pair<unsigned int, unsigned int>>> beasts;
    std::list<std::pair<OpAgent*, std::pair<unsigned int, unsigned int>>> players;
    for(int i = 0; i < playernum; i++){
        std::pair<unsigned int, unsigned int> r(0, i);
        std::pair<OpAgent*, std::pair<unsigned int, unsigned int>> zozo(new OpAgent(opconf), r);
        players.push_back(zozo);
        a_field.a_field[0][i].p_player = zozo.first;
    }
   
    for(int i = 0; i < playernum + (playernum / 2); i++){
        std::pair<unsigned int, unsigned int> r;
        while(true){
            r.first = randint(mconf.first.second);
            r.second = randint(mconf.first.first);
            if(a_field.a_field[r.first][r.second].a_type == cellType::floo && a_field.a_field[r.first][r.second].p_player == nullptr){
                break;
            }
        }
        int l = randint(10000);
        std::pair<Character*, std::pair<unsigned int, unsigned int>> pupa;
        pupa.second = r;
        if(l < 3333){
            pupa.first = new WildBeast(bconf);
        }
        else if(l >= 3333 && l < 6666){
            pupa.first = new SmartBeast(bconf);
        }
        else{
            pupa.first = new ForagerBeast(bconf);
        }
        beasts.push_back(pupa);
        a_field.a_field[r.first][r.second].p_player = pupa.first;
    }
    l_players = players;
    l_enemies = beasts;
}

Level::~Level(){
    for(auto i: l_players){
        delete i.first;
    }
    for(auto i: l_enemies){
        delete i.first;
    }
    for(auto i: a_field.a_field){
        for(auto j: i){
            for(auto k: j.l_items){
                delete k;
            }
        }
    }
}


std::list<Item*> genRandomThings(wconfig& wconf){
    int x = randint(1000);
    int y = randint(1000);
    if(y < 500){
        return std::list<Item*>();
    }
    Item* m;
    if(x < 333){
        int l = randint(4);
        m = new Weapon(static_cast<WeaponType>(l), wconf);
    }
    else if(x >= 334 && x < 666){
        int he = randint(200);
        int ht = 10 + randint(50);
        int w = 50 + randint(100);
        m = new MedKit(he, ht, w);
    }
    else{
        int l = randint(4);
        int max = randint(100);
        int s = randint(max);
        int w = randint(200);
        m = new Bandolier(static_cast<WeaponType>(l), s, max, w);
    }
    std::list<Item*> ans;
    ans.push_back(m);
    return ans;
}



mapconfig readmap(const std::string& filename){
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    std::pair<unsigned int, unsigned int> size;
    std::vector<std::vector<cellType>> cells;
    fin >> size.first;
    fin >> size.second;
    for(int i = 0; i < size.second; i++){
        std::vector<cellType> cs;
        for(int j = 0; j < size.first; j++){
            unsigned int tm;
            fin >> tm;
            cs.push_back(static_cast<cellType>(tm));
        }
        cells.push_back(cs);
    }
    return mapconfig(size, cells); 
}

//lvlconfig readlvl(const std::string& filename){
//    lvlconfig ans;
//
//    std::ifstream fin;
//    fin.open(filename);
//    if(!fin.is_open()){
//        throw std::invalid_argument("no such a file");
//    }
//
//    // map 
//    fin >> ans.lvl.second.first;
//    fin >> ans.lvl.second.second;
//    for(int i = 0; i < ans.lvl.second.first; i++){
//        std::vector<unsigned int> tmp;
//        for(int j = 0; j < ans.lvl.second.second; j++){
//            unsigned int a;
//            fin >> a;
//            tmp.push_back(a);
//        }
//        ans.lvl.first.push_back(tmp);
//    }
//
//    // characters
//    unsigned int n;
//    fin >> n;
//    for(int i = 0; i < n; i++){
//        unsigned int type;
//        if()
//    }
//
//
//    // items 
//    
//
//
//    // charitems 
//    
//
//    return lvlconfig;
//    
//}


std::ostream& operator<<(std::ostream& out, const Level& x){
    std::string str(" #^-");
    for(auto i: x.a_field.a_field){
        for(auto j: i){
            out << "****";
        }
        out << std::endl;
        for(auto j: i){
            out << "*";
            if(j.a_type != cellType::floo && j.a_type != cellType::storage){
                char c = str.c_str()[static_cast<int>(j.a_type)];
                out << c << c << c;
            }
            else if(j.a_type == cellType::floo){
                out << "   ";
            }
            else{
                out << "@ @";
            }
        }
        out << std::endl;
        for(auto j: i){
            out << "*";
            if(j.a_type != cellType::floo && j.a_type != cellType::storage){
                char c = str.c_str()[static_cast<int>(j.a_type)];
                out << c << c << c;
            }
            else if(j.p_player == nullptr){
                out << "   ";
            }
            else if(j.p_player->isTrooper()){
                out << " O ";
            }
            else if(j.p_player->isBeast()){
                if(j.p_player->isWild()){
                    out << " W ";
                }
                else if(j.p_player->isSmart()){
                    out << " S ";
                }
                else{
                    out << " F ";    
                }
            }
        }
        out << std::endl;
        for(auto j: i){
            out << "*";
            if(j.a_type != cellType::floo && j.a_type != cellType::storage){
                char c = str.c_str()[static_cast<int>(j.a_type)];
                out << c << c << c;
            }
            else if(j.l_items.size() == 0){
                out << "   ";
            }
            else if(j.l_items.front()->isAmmo()){
                out << "A  ";
            }
            else if(j.l_items.front()->isMedkit()){
                out << " M ";
            }
            else{
                out << "  B";
            }
        }
        out << std::endl;
    }
//    for(int i = 0; i < x.a_field; i++){
//        out << "****";
//    }
    out << std::endl;
    return out;
}
