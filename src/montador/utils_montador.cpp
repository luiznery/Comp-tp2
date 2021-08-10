#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <map>

#include "utils_montador.h"

using namespace std;

list<int>::iterator get_element(list<int>* lista, int position) {
    int c = 0;
    for(auto it = lista->begin(); it!=lista->end(); it++){
        if (c==position)
            return it;
        c++;
    }
    return lista->end();
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
    for(auto it = lista->begin(); it!=lista->end(); it++){
        cout<<*it<<sep;
    }
    cout<<end;
}

void print_list(list<int>* lista, string sep, string end){
    for(auto it = lista->begin(); it!=(prev(lista->end())); it++){
        cout << *it << sep;
    }
    cout << *(prev(lista->end()));
    cout << end;
}

void print_list_of_lists(list<list<string>*>* lista, string sep, string end){
    for(auto it_i = lista->begin(); it_i!=lista->end(); it_i++){
        for(auto it_j = (*it_i)->begin(); it_j!=(*it_i)->end(); it_j++){
            cout << *it_j << sep;    
        }
        cout<<end;
    }

}

void print_map(map<string,int>* m) {
    for (const auto& x : (*m)) {
        std::cout << x.first << ": " << x.second << "\n";
    }
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

int find(string text, char c){
    for(unsigned i = 0; i < text.size(); i++)
        if(text[i]== c)
            return i;
    return -1;
}

void print_on_format(list<int>* machine_code, list<int>* stats){
    cout << "MV-EXE" << endl << endl;
    print_list(stats, " ", "\n\n");
    print_list(machine_code, " ", "");
}
