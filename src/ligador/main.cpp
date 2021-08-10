#include <iostream>
#include <list>
#include <map>
#include "ligador.h"
using namespace std;


bool is_number(string s){
    for (int i = 0; i < s.size(); ++i)
        if(not is_digit(s[i]))
            return false;
    return true;
}


list<string>* link(list<*list<string>>* programs, list<*map<string, int>>* dicts){
    list<string>* linked_program;

    for(list<*list<string>>::iterator program_it = programs->begin(); program_it != programs->end(); program_it++){
        for(list<string>::iterator token_it = program_it->begin(); token_it != program_it->end(); token_it++){
            if(not is_number(*token_it)){
                
            }
        }
    }



    return linked_program
}


int main(int argc, char *argv[]) {
    // TODO: executar o ligador...
    cout << "Hello World" << endl;
    return 0;
}