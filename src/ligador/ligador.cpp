#include "ligador.h"
#include "utils_ligador.h"


pair<map<string,int>*,list<string>*>* build(list<string>* data){
    list<string>* row = new list<string>;

    map<string,int>* dicio = new map<string,int>;
    list<string>* program = new list<string>;

    for(auto it = data->begin(); it != data->end(); ++it)
    {
        if (it->size() == 0){
            it++;
            program = split(*it,' ');
        }
        else{
            row = split(*it,' ');
            dicio->insert(pair<string, int>(*get_element(row,0), stoi(*get_element(row,1))));
        }
    }
    pair<map<string,int>*,list<string>*>* program_pair = new pair<map<string,int>*,list<string>*>(dicio, program);
    return program_pair;
}


list<string>* link(list<list<string>*>* programs, map<string, int>* label_table){
    list<string>* linked_program = new list<string>();
    int pc=0;
    for(list<list<string>*>::iterator program_it = programs->begin(); program_it != programs->end(); program_it++){
        for(list<string>::iterator token_it = (*program_it)->begin(); token_it != (*program_it)->end(); token_it++){
            pc++;
            if(is_number(*token_it)){
                linked_program->push_back(*token_it);
			}               
            else{
                int label_address = label_table->find(*token_it)->second;
                linked_program->push_back(to_string(label_address - pc));
            }
        }
    }
    return linked_program;
}

map<string, int>* merge_label_tables(list<map<string, int>*>* label_tables, list<int>* program_addresses){
    int count = 0;
    map<string, int>* merged_label_table = new map<string, int>();
    for(list<map<string, int>*>::iterator label_table_it = label_tables->begin(); label_table_it != label_tables->end(); label_table_it++){
        for(map<string, int>::iterator item_it = (*label_table_it)->begin(); item_it != (*label_table_it)->end(); item_it++){
            int absolute_address = item_it->second + *get_element(program_addresses, count);
            merged_label_table->insert(pair<string, int>(item_it->first, absolute_address));
        }
        count++;
    }
    return merged_label_table;
}


list<int>* get_program_addresses(list<list<string>*>* programs){
    list<int>* program_addresses = new list<int>();
    int count = 0;
    for(list<list<string>*>::iterator program_it = programs->begin(); program_it != programs->end(); ++program_it){
        program_addresses->push_back(count);
        count += (*program_it)->size();
    }
    return program_addresses;
}
