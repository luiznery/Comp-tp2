#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include "montador.h"
#include "utils_montador.h"

using namespace std;

map<string,int>* get_code_map(){
    map<string,int>* code_map = new map<string,int>;
    code_map->insert(pair<string, int>("HALT", 0));
    code_map->insert(pair<string, int>("LOAD", 1));
    code_map->insert(pair<string, int>("STORE", 2));
    code_map->insert(pair<string, int>("READ", 3));
    code_map->insert(pair<string, int>("WRITE", 4));
    code_map->insert(pair<string, int>("COPY", 5));
    code_map->insert(pair<string, int>("PUSH", 6));
    code_map->insert(pair<string, int>("POP", 7));
    code_map->insert(pair<string, int>("ADD", 8));
    code_map->insert(pair<string, int>("SUB", 9));
    code_map->insert(pair<string, int>("MUL", 10));
    code_map->insert(pair<string, int>("DIV", 11));
    code_map->insert(pair<string, int>("MOD", 12));
    code_map->insert(pair<string, int>("AND", 13));
    code_map->insert(pair<string, int>("OR", 14));
    code_map->insert(pair<string, int>("NOT", 15));
    code_map->insert(pair<string, int>("JUMP", 16));
    code_map->insert(pair<string, int>("JZ", 17));
    code_map->insert(pair<string, int>("JN", 18));
    code_map->insert(pair<string, int>("CALL", 19));
    code_map->insert(pair<string, int>("RET", 20));
    return code_map;
}

list<string>* read_input(string file_name) {
    string line;
    ifstream myfile;

    myfile.open(file_name);
    if(!myfile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    list<string> *lines = new list<string>;
    while(getline(myfile, line)) {
        lines->push_back(line);
    }

    return lines;
}

list<list<string>*>* process_lines(list<string>* lines, map<string,int>* label_table) {
    list<list<string>*>* processed_lines = new list<list<string>*>;

    int pc = CODE_BEGIN;
    for(auto line_it = lines->begin(); line_it!=lines->end(); line_it++) {


        int end_line_i = (*line_it).size();
        int semicolon_i = find(*line_it,';');
        if (semicolon_i >= 0 and semicolon_i < end_line_i)
            end_line_i = semicolon_i;
        
        if (end_line_i==0) // se a linha so tiver comentario
            continue;

        //pega a linha sem comentario
        string processed_line = (*line_it).substr(0,end_line_i);
        
        if (split(processed_line,' ')->size()==0) //pula se a linha for vazia
            continue;

        int colon_i = find(*line_it,':'); //se tiver um label
        if (colon_i > 0){ // se a linha tiver algum label
            string label = processed_line.substr(0,colon_i);
            label_table->insert(pair<string,int>(label,pc) );
        }
        // cout << *line_it << endl;
        processed_line = processed_line.substr(colon_i+1,processed_line.size());
        if (processed_line.size()==0)
            continue;
        
        list<string>* line_elements = split(processed_line, ' ');
        if (line_elements->size()==0) //se for somente um label e mais nada
            continue;

        processed_lines->push_back(line_elements);

        if(*get_element(line_elements,0)=="WORD")
            pc++;
        else if(*get_element(line_elements,0)!="END")
            pc+= line_elements->size();

    }

    return processed_lines;
}

bool is_label(string text, map<string, int>* label_table){
    if( label_table->find(text) == label_table->end() )
        return false;
    else
        return true;
}

list<int>*
row2ints(list<string>* row, map<string,int>* code_map, map<string,int>* label_table, int pc){
    list<int>* out = new list<int>;

    //obtem o operador
    string op = *get_element(row,0);
    if(op=="WORD"){
        out->push_back(stoi(*get_element(row,1)));
        return out;
    }else if(op=="END"){
        return out;
    }
    int code = code_map->find(op)->second;
    pc++;
    out->push_back(code);
    
    
    //trata os operandos
    if (row->size() == 3){ //1 operador + 2 operandos
        pc++;
        out->push_back( //adiciona primeiro operando
            stoi(get_element(row,1)->substr( 1, get_element(row,1)->size() ))
        );
        
        if (is_label(*get_element(row,2), label_table)) { //se segundo operando for label insere valor modificado
            int num_label = label_table->find((*get_element(row,2)))->second;
            pc++;
            out->push_back(num_label-(pc));
            
        } 
        else { //se nao for label
            pc++;
            out->push_back( 
                stoi( get_element(row,2)->substr(1, get_element(row,2)->size()) )
            );
            
        }
    } 
    else if (row->size()==2) { //1 operador + 1 operando
        if (is_label((*get_element(row,1)), label_table)){ //se for label
            int num_label = label_table->find((*get_element(row,1)))->second;
            pc++;
            out->push_back(num_label-pc);
            
        } 
        else{ //se nao for label
            pc++;
            out->push_back(
                stoi(get_element(row,1)->substr(1, get_element(row,1)->size()))
            );
        }
    }
    return out;
}

list<int>* assemble(list<list<string>*>* processed_lines, map<string,int>* code_map, map<string,int>* label_table) {
    list<int>* machine_code = new list<int>;
    int pc = CODE_BEGIN;
    for(auto line_it = processed_lines->begin(); line_it != processed_lines->end(); line_it++){
        list<int>* line_code = row2ints(*line_it, code_map, label_table, pc);
        pc = pc + line_code->size();
        for(auto it = line_code->begin(); it != line_code->end(); it++)
            machine_code->push_back(*it);
    }   
    return machine_code;
}

bool is_register(string text ) {
    if(text == "R0" || text == "R1" || text == "R2" || text == "R3" )
        return true;
    return false;
}

list<string>*
row2strings(list<string>* row, map<string,int>* code_map){
    list<string>* out = new list<string>;

    //obtem o operador
    string op = *get_element(row,0);
    if(op=="END")
        return out;
    
    if(op=="WORD"){
        out->push_back(*get_element(row,1));
        return out;
    }

    string code = to_string(code_map->find(op)->second);
    out->push_back(code);
    
    //trata os operandos
    if (row->size() == 3){ //1 operador + 2 operandos
        out->push_back( //adiciona primeiro operando
            get_element(row,1)->substr( 1, get_element(row,1)->size() )
        );
        
        // Adiciona o segundo operando
        if (is_register(*get_element(row,2))) //se segundo operando for registrador
            out->push_back( 
                get_element(row,2)->substr(1, get_element(row,2)->size()) 
            );
        else //se nao for registrador -> label
            out->push_back(*get_element(row,2)); 
        
        return out;
    }

    if (row->size() == 2) { //1 operador + 1 operando
        if ( is_register( *get_element(row, 1) ) ) //se for registrador
            out->push_back(
                get_element(row,1)->substr(1, get_element(row,1)->size())
            );
            
        else
            out->push_back(*get_element(row,1));

        return out;
    }
    return out;
}

list<string>* 
assemble_intermediary(list<list<string>*>* processed_lines, map<string,int>* code_map) {
    list<string>* machine_code = new list<string>;

    for(auto line_it = processed_lines->begin(); line_it != processed_lines->end(); line_it++){
        list<string>* line_code = row2strings(*line_it, code_map);
        for(auto it = line_code->begin(); it != line_code->end(); it++)
            machine_code->push_back(*it);
    }   

    return machine_code;
}

list<int>* calculate_stats(list<int>* machine_code, list<list<string>*>* processed_lines ) {
    int n = machine_code->size();
    int pc_begin = CODE_BEGIN;
    for(auto line_it = processed_lines->begin(); line_it!=processed_lines->end(); line_it++){
        if ((*get_element(*line_it,0)) != "WORD")
            break;
        pc_begin++;
    }
    list<int>* stats = new list<int>; // n, CODE_BEGIN, (n + CODE_BEGIN + STACK_SIZE), pc_begin
    stats->push_back(n);
    stats->push_back(CODE_BEGIN);
    stats->push_back(n + CODE_BEGIN + STACK_SIZE);
    stats->push_back(pc_begin);
    
    return stats;
}