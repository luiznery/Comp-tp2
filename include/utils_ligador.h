#include <iostream>

using namespace std;

#ifndef UTILS_MONTADOR_H
#define UTILS_MONTADOR_H

bool is_number(string s);
list<int>::iterator get_element(list<int>* lista, int position);
list<string>::iterator get_element(list<string>* lista, int position);
void print_list(list<string>* lista, string sep, string end);
void print_list_of_lists(list<list<string>*>* lista, string sep, string end);
void print_map(map<string, int>* m);
list<string>* split(string text, char separator);
int find(string text, char c);
void print_on_format(list<int>* machine_code, list<int>* stats);

#endif