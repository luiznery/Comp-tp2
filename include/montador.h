#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>

using namespace std;

#ifndef MONTADOR_H
#define MONTADOR_H

#define STACK_SIZE 1000
#define CODE_BEGIN 0

map<string,int>* get_code_map();
list<string>* read_input(string file_name);
list<string>* process_single_line(string line);
list<list<string>*>* process_lines(list<string>* lines, map<string, int>* label_table);
bool is_label(string text, map<string, int> label_table);
list<int>* row2ints(list<string>* row, map<string, int>* cod_dicio, map<string, int>* label_table, int pc);
list<int>* assemble(list<list<string>*>* processed_lines, map<string,int>* code_map, map<string,int>* label_table);
list<int>* calculate_stats(list<int>* machine_code, list<list<string>*>* processed_lines );

#endif
