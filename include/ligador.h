#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <map>


using namespace std;

pair<map<string,int>*,list<string>*>* build(list<string>* data);
map<string, int>* merge_label_tables(list<map<string, int>*>* label_tables, list<int>* program_addresses);
list<string>* link(list<list<string>*>* programs, map<string, int>* label_table);
list<int>* get_program_addresses(list<list<string>*>* programs);

#ifndef LIGADOR_H
#define LIGADOR_H

#endif
