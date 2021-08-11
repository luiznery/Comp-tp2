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

    list<list<string>*>* programs = new list<list<string>*>();
    list<map<string, int>*>* label_tables = new list<map<string, int>*>();

    for(int i = 1; i < argc; i++){
        list<string>* assembler_output = read_input(argv[i]);
        pair<map<string, int>*, list<string>*>* program_pair = build(assembler_output);
        programs->push_back(program_pair->second);
        label_tables->push_back(program_pair->first);
    }

    list<int>* program_addresses =  get_program_addresses(programs);

    map<string, int>* absolute_label_table = merge_label_tables(label_tables, program_addresses);


    list<string>* linked_program = link(programs, absolute_label_table);

    list<int>* stats = calculate_stats(linked_program, absolute_label_table);

    print_on_format(linked_program, stats);

    return 0;
}