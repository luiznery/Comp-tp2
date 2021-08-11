#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>

using namespace std;

#ifndef UTILS_MONTADOR_H
#define UTILS_MONTADOR_H

list<int>::iterator get_element(list<int>* lista, int position);
list<string>::iterator get_element(list<string>* lista, int position);
void print_list(list<string>* lista, string sep, string end);
void print_list_of_lists(list<list<string>*>* lista, string sep, string end);
void print_map(map<string, int>* m, string sep);
list<string>* split(string text, char separator);
int find(string text, char c);
void print_on_format(list<int>* machine_code, list<int>* stats);

bool is_register(string text );
list<string>* row2strings(list<string>* row, map<string,int>* code_map);
list<string>* assemble_intermediary(list<list<string>*>* processed_lines, map<string,int>* code_map);

#endif
