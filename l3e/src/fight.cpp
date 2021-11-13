#include "fight.hpp"
#include <stdexcept>

int randRange(int a, int b){
    return static_cast<int>(a + (b - a) * (static_cast<double>(rand()) / RAND_MAX));
}


int gcd(int a, int b){
    while(a*b != 0){
        if(a > b){
            a %= b;
        }
        else{
            b %= a;
        }
    }
    return a+b;
}


int genCoPrime(int n){
    if(n <= 2){
        return 1;
    }
    while(true){
        int p = randRange(2, n-1); 
        if(gcd(p, n) == 1){
            return p;
        }
   }
}


std::string excuses(){
    static std::string first = "Ooops! This player suddenly has fallen sick";
    static std::string second = "This player's mom took him home by force";
    double x = rand();
    if(x < RAND_MAX / 2){
        return first;
    }
    return second;
}


char* getCharArray(std::istream &in){
    std::string str;
    std::getline(in, str);
    if(str.size() == 0){
        return nullptr;
    }
    char *x = new char [str.size() + 1];
    std::copy(str.c_str(), str.c_str() + str.size()+1, x);
    return x;
}


std::string update(char* val, int no, int wo){
    std::string s(val);
    static std::string tf("\'total fights\': "), tw("\'total wins\': ");
    int x = s.find(tf) + tf.size();
    int y = s.find(" ", x);
    int tot = stoi(s.substr(x, y - x + 1)) + no;
    int beg = x - tf.size();    
    x = s.find(tw, y) + tw.size();
    y = s.find(" ", x);
    int tow = stoi(s.substr(x, y - x + 1)) + wo;
    std::string ans = s.substr(0, beg) + tf;
    ans += std::to_string(tot) + ", " + tw;
    ans += std::to_string(tow) + ", \'winrate\': ";
    if(tot){
        ans += std::to_string(static_cast<int>(static_cast<double>(tow) / tot * 100));
    }
    else{
        ans += "0";
    }
    ans += "%}";
    return ans;
}


const Table::TableElement* getPlayer(const Table::ViewedTable &pla, int &num, int step, int mod){
    const Table::TableElement* tmp = pla.find(num);
    while(!tmp){
        num = (num - 1 + step) % mod + 1;
        tmp = pla.find(num);
    }
    return tmp;
}


bool pairFight(const Table::TableElement* el1,const Table::TableElement* el2, int no){
     double a = getStats(el1, no);
     double b = getStats(el2, no);
     return a < b;
}


double getStats(const Table::TableElement* el, int no){
    double lucky = 10.0 * static_cast<double>(rand())/ RAND_MAX;
    std::string winrate("\'winrate\': ");
    std::string s(el->value);
    int beg = s.find(winrate) + winrate.size();
    int end = s.find("%", beg);
    int win = stoi(s.substr(beg, end-beg + 1));
    return static_cast<double>(win)/no + lucky;   
}


std::string parsename(const Table::TableElement* el){
    std::string s(el->value), t("\'name\': ");
    int beg = s.find(t) + t.size() + 1;
    int end = s.find("\'", beg) - 1;
    return s.substr(beg, end-beg + 1);
}


Table::ViewedTable genPlayers(const std::string &filename){
    Table::ViewedTable tmp;
    std::ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        throw std::invalid_argument("no such a file");
    }
    int i = 1;
    char *x = getCharArray(fin);
    while(x != nullptr){
        tmp.add(i++, x);
        delete[] x;
        x = getCharArray(fin);
    }
    return tmp;
} 


void addExtraPlayers(Table::ViewedTable &t){
    int n;
    std::cout << "How many players do you have? ";
    getEl(n);
    for(int i = 0; i < n; i++){
        std::string tmp;
        std::cout << "What is it's name? ";
        getEl(tmp);
        tmp = "{'name':" + tmp + ", 'kind': rooster, 'total fights': 0, 'total wins': 0, 'winrate': '0%'";
        char* x = new char [tmp.size()];
        std::copy(tmp.c_str(), tmp.c_str() + tmp.size() + 1, x);
        t.add(t.size()+1, x);
    }
}


Table::ViewedTable genTable(const Table::ViewedTable &t, int count, std::ofstream &file){
    if(count > t.size()){
        throw std::invalid_argument("not enough players");
    }

    Table::ViewedTable tmp; 
    int p = genCoPrime(t.size());
    int j = 0, i = 0;
    while(j != count){
       i = (p*j) % t.size() + 1;
       tmp.add(++j, t[i].value);
    }
    while(j != t.size()){ 
        i = (p*j) % t.size() + 1;
        file << std::string(t[i].value) << std::endl;
        j++;
    }
    return tmp;
}


void fight(Table::ViewedTable &pla, int max, int no, std::ofstream &file){
    if(pla.size() == 1){
        int i = 1;
        const Table::TableElement* win = getPlayer(pla, i, 1, max);
        file << update(win->value, no, no);
        std::cout << std::endl << std::endl << "ABSOLUTE WINNER: " << parsename(win) << ", Wins this tournament: " << no << std::endl;
        pla.remove(win->key);
        pla = !pla;
        return;
    }

    Table::ViewedTable winners;
    int j = 0, i = 1;
    int p = genCoPrime(max);
    while(j++ != pla.size() / 2){
        std::cout << "------- " << j << " pair -------" << std::endl;
        const Table::TableElement* el1 = getPlayer(pla, i, p, max);
        i = (i - 1 + p) % max + 1;
        const Table::TableElement* el2 = getPlayer(pla, i, p, max);
        i = (i - 1 + p) % max + 1;
        std::cout << "№" << el1->key << " " << parsename(el1);
        std::cout << " vs ";
        std::cout << "№" << el2->key << " " << parsename(el2) << std::endl;

        bool res = pairFight(el1, el2, no);
        if(!res){
            std::cout << "PLAYER № " << el1->key << " " << parsename(el1) << " WON!!!!" << std::endl;
            file << update(el2->value, no, no-1) << std::endl;
            pla.remove(el2->key);
        }
        else{
            std::cout << "PLAYER № " << el2->key << " " << parsename(el2) << " WON!!!!" << std::endl;
            file << update(el1->value, no, no -1) << std::endl;
            pla.remove(el1->key);
        }
        std::cout << "---------------------" << std::endl;
        
            }
    if(pla.size() & 1){
        const Table::TableElement* el = getPlayer(pla, i, p, max);
        std::cout << "player № " << el->key << " " << parsename(el) << ". " << excuses() << std::endl;
        file << update(el->value, 0, 0) << std::endl;
        pla.remove(el->key);
    }
    pla = !pla;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
