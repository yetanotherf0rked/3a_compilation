#include "SymbolTable.h"

#include <map>
#include <iostream>
#include <stdlib.h>

map<string,int> delta_local;
map<string,int> delta_arg;
int last_delta_arg = -2; //range from -3 to -3-(nb_parameters-1)
int last_delta_local = -1; //range from 0 to nb_local-1


void reset_symbol_table()
{
  delta_arg.erase(delta_arg.begin(),delta_arg.end());
  delta_local.erase(delta_local.begin(),delta_local.end());
  last_delta_arg = -2;
  last_delta_local = -1;
}

void declare_argument(string id)
{
  if(delta_arg.find(id) != delta_arg.end())
    {
      cerr << "SymbolTable::declare_argument: variable " << id << " already defined" << endl;
      exit(1);
    }
  last_delta_arg--;
  delta_arg[id] = last_delta_arg;
}

void declare_local(string id)
{
  if(delta_local.find(id) != delta_local.end())
    {
      cerr << "SymbolTable::declare_local: variable " << id << " already defined" << endl;
      exit(1);
    }
  last_delta_local++;
  delta_local[id] = last_delta_local;
}

int get_slot(string id)
{
  if(delta_local.find(id) != delta_local.end())
    //Local variable?
    return delta_local[id];

  if(delta_arg.find(id) != delta_arg.end())
    //Argument?
    return delta_arg[id];

  cerr << "SymbolTable::get_slot: variable " << id << " is not declared" << endl;
  exit(1);
}

int get_nb_argument()
{
  return delta_arg.size();
}

int get_nb_local()
{
  return delta_local.size();
}

