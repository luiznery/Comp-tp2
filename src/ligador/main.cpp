#include "ligador.h"
#include "utils_ligador.h"
using namespace std;

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

int main(int argc, char *argv[]) {
    // list<string>* program1 = new list<string>();
    // program1->push_back("lepo");
    // program1->push_back("lero");
    // program1->push_back("1");
    // program1->push_back("1");
    // program1->push_back("1");
    // list<string>* program2 = new list<string>();
    // program2->push_back("2");
    // program2->push_back("2");
    // program2->push_back("2");
    // list<list<string>*>* programs = new list<list<string>*>();
    // programs->push_back(program1);
    // programs->push_back(program2);

    // map<string, int>* label_table = new map<string, int>();
    // label_table->insert(pair<string, int>("lepo", 4));

    // map<string, int>* label_table1 = new map<string, int>();
    // label_table1->insert(pair<string, int>("lero", 2));

    
    // list<map<string, int>*>* label_tables = new list<map<string, int>*>();

    // label_tables->push_back(label_table);
    // label_tables->push_back(label_table1);

    // list<int>* program_lengths = get_program_addresses(programs);

    // map<string, int>* absolute_label_table = merge_label_tables(label_tables, program_lengths);

    // list<string>* linked_program = link(programs, absolute_label_table);
    // print_list(linked_program, " ", "");

    list<string>* program1 = read_input("tst/test");
    list<string>* program2 = read_input("tst/test1");

    pair<map<string, int>*, list<string>*>* program1_pair = build(program1);        
    pair<map<string, int>*, list<string>*>* program2_pair = build(program2);        

    list<map<string, int>*>* label_tables = new list<map<string, int>*>();
    label_tables->push_back(program1_pair->first);
    label_tables->push_back(program2_pair->first);

    list<list<string>*>* programs = new list<list<string>*>();
    programs->push_back(program1_pair->second);
    programs->push_back(program2_pair->second);

    list<int>* program_addresses =  get_program_addresses(programs);

    map<string, int>* absolute_label_table = merge_label_tables(label_tables, program_addresses);


    list<string>* linked_program = link(programs, absolute_label_table);


    print_list(linked_program, " ", "");

    return 0;
}