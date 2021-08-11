#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <map>


using namespace std;

#ifndef LIGADOR_H
#define LIGADOR_H

#define STACK_SIZE 1000
#define CODE_BEGIN 0


list<int>* calculate_stats(list<string>* machine_code, map<string, int>* label_table);
pair<map<string,int>*,list<string>*>* build(list<string>* data);
map<string, int>* merge_label_tables(list<map<string, int>*>* label_tables, list<int>* program_addresses);
list<string>* link(list<list<string>*>* programs, map<string, int>* label_table);
list<int>* get_program_addresses(list<list<string>*>* programs);

#endif
