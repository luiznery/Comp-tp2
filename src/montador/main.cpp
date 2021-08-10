#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <map>

#include "montador.h"
#include "utils_montador.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }
    
    map<string, int>* label_table = new map<string, int>();
    map<string, int>* code_map = get_code_map();
    
    list<string> *lines = read_input(argv[1]);
    // print_list(lines, "\n","\n");
    list<list<string>*>* processed_lines = process_lines(lines,label_table);
    
    // print_list_of_lists(processed_lines,"|","\n");    
    // print_map(label_table);
    
    list<int>* machine_code = assemble(processed_lines, code_map, label_table);
    list<int>* stats = calculate_stats(machine_code, processed_lines);

    print_on_format(machine_code, stats);

    return 0;
}