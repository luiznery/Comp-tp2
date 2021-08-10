#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

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

list<string>* split(string text, char separator){
    list<string>* word_list = new list<string>();

    string word = "";
    for(unsigned i = 0; i < text.size(); i++){
        if(text[i]!= separator){
            word = word + text[i];
        }else{
            if(word!="")
                word_list->push_back(word);
            word = "";
        }

    }
    if(word!="")
        word_list->push_back(word);

    return word_list;
}

list<string>::iterator get_element(list<string>* lista, int position) {
    int c = 0;
    for(auto it = lista->begin(); it!=lista->end(); it++){
        if (c==position)
            return it;
        c++;
    }
    return lista->end();
}

void print_list(list<string>* lista, string sep, string end){
    for(auto it = lista->begin(); it!=(prev(lista->end())); it++){
        cout << *it << sep;
    }
    cout << *(prev(lista->end()));
    cout << end;
}

void print_map(map<string,int>* m) {
    for (const auto& x : (*m)) {
        std::cout << x.first << ": " << x.second << "\n";
    }
}

void teste() {
    cout<<"teste"<<endl;
}