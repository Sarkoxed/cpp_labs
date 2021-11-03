#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <string>
#include <cstring>
#include <random>

#include "../lib/ViewTable.hpp"
#include "../tools/toolib.hpp"

static const short size = 10;

Table::ViewedTable genPlayers(const std::string &name);
Table::ViewedTable genTable(Table::ViewedTable &t, int count);
void genRound(Table::ViewedTable &x);
void fight(Table::ViewedTable &x);
void darkHorse();
char* getCharArray(std::istream &in);
void addExtraPlayers(Table::ViewedTable &t);
void makePowerOfTwo(int &n);
