#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <string>
#include <cstring>
#include <random>
#include <chrono>
#include <thread>

#include "../lib/ViewTable.hpp"
#include "../tools/toolib.hpp"

#pragma once 

static const short size = 10;

Table::ViewedTable genPlayers(const std::string &name);
Table::ViewedTable genTable(const Table::ViewedTable &t, int count, std::ofstream &file);
void addExtraPlayers(Table::ViewedTable &t);
void fight(Table::ViewedTable &x,int max, int no, std::ofstream &file);

int randRange(int a, int b);
int gcd(int a, int b);
int genCoPrime(int n);

const Table::TableElement* getPlayer(const Table::ViewedTable& pla, int& num, int step, int mod);

bool pairFight(const Table::TableElement* el1,const Table::TableElement* el2, int no);
double getStats(const Table::TableElement* el, int no);

char* getCharArray(std::istream &in);
std::string update(char* val, int no, int wo);
std::string parsename(const Table::TableElement* el);
std::string excuses();
