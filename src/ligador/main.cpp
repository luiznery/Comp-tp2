#include <iostream>
#include <list>
#include <map>
#include "ligador.h"
using namespace std;


bool is_number(string s){
    for (unsigned i = 0; i < s.size(); ++i)
        if(not isdigit(s[i]))
            return false;
    return true;
}




list<string>* link(list<list<string>*>* programs, map<string, int>* label_table){
    list<string>* linked_program = new list<string>();
    int pc=0;
    for(list<list<string>*>::iterator program_it = programs->begin(); program_it != programs->end(); program_it++){
        for(list<string>::iterator token_it = (*program_it)->begin(); token_it != (*program_it)->end(); token_it++){
            if(is_number(*token_it))
                linked_program->push_back(*token_it);
            else{
                int label_address = label_table->find(*token_it)->second;
                linked_program->push_back(to_string(label_address));
            }
            pc++;
        }
    }



    return linked_program;
}

void print_list(list<string>* lista, string sep, string end){
    for(auto it = lista->begin(); it!=lista->end(); it++){
        cout<<*it<<sep;
    }
    cout<<end;
}

list<int>::iterator get_element(list<int>* lista, int position) {
    int c = 0;
    for(auto it = lista->begin(); it!=lista->end(); it++){
        if (c==position)
            return it;
        c++;
    }
    return lista->end();
}

map<string, int>* merge_label_tables(list<map<string, int>*>* label_tables, list<int>* program_addresses){
    int count = 0;
    map<string, int>* merged_label_table = new map<string, int>();
    for(list<map<string, int>*>::iterator label_table_it = label_tables->begin(); label_table_it != label_tables->end(); label_table_it++){
        for(map<string, int>::iterator item_it = (*label_table_it)->begin(); item_it != (*label_table_it)->end(); item_it++){
            int absolut_address = item_it->second + *get_element(program_addresses, count);
            merged_label_table->insert(pair<string, int>(item_it->first, absolut_address));
        }
        count++;
    }
    return merged_label_table;
}


void print_map(map<string,int>* m) {
    for (const auto& x : (*m)) {
        std::cout << x.first << ": " << x.second << "\n";
    }
}

int main(int argc, char *argv[]) {
    list<string>* program1 = new list<string>();
    program1->push_back("lepo");
    program1->push_back("1");
    program1->push_back("1");
    program1->push_back("1");
    list<string>* program2 = new list<string>();
    program2->push_back("2");
    program2->push_back("2");
    program2->push_back("2");
    program2->push_back("lero");
    list<list<string>*>* programs = new list<list<string>*>();
    programs->push_back(program1);
    programs->push_back(program2);

    map<string, int>* label_table = new map<string, int>();
    label_table->insert(pair<string, int>("lepo", 0));

    map<string, int>* label_table1 = new map<string, int>();
    label_table1->insert(pair<string, int>("lero", 3));

    list<map<string, int>*>* label_tables = new list<map<string, int>*>();

    label_tables->push_back(label_table);
    label_tables->push_back(label_table1);
    list<int>* program_lengths = new list<int>();
    program_lengths->push_back(0);
    program_lengths->push_back(4);

    map<string, int>* absolut_label_table = merge_label_tables(label_tables, program_lengths);

    print_map(absolut_label_table);
    //list<string>* linked_program = link(programs, label_table);
    //print_list(linked_program, " ", "");

    return 0;
}