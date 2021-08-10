#include "ligador.h"

// TODO: implementação do editor de ligação

tuple<map<string,int>*,list<string>*> build(list<string>* data){
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
    return make_tuple(dicio,program);
}

