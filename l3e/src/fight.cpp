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

void makePowerOfTwo(int &n){
    double si = log(n) / log(2);
    if(floor(si) != si){
        n = pow(2, si+1);
    }
}

bool isPrime(int p){
    if(p == 1){
        return false;
    }
    else if(p == 2){
        return true;
    }
    for(int i = 2; i < floor(sqrt(p)) + 1; i+=2){
        if(p % i == 0){
            return false;
        }
    }
    return true;
}

int genCoPrime(int n){
    srand(time(0));
    while(true){
        int p = randRange(3, n-1); 
        if(isPrime(p) && gcd(p, n) == 1){
            return p;
        }
   }
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
        tmp.add(i, x);
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
        t.add(t.size(), x);
    }
}

Table::ViewedTable genTable(Table::ViewedTable &t, int count){
    srand(time(0));
    if(count > t.size()){
        throw std::invalid_argument("not enough players");
    }
    Table::ViewedTable tmp; 
    int p = 2*genCoPrime(t.size());
    int j = 0;
    for(int i = 0; j != count / 2; i = (i + p) % count + 1){
       tmp.add(j+1, t[i].value);
       tmp.add(j+1, t[i+p].value);
       j++;
    }
    return tmp;
}


