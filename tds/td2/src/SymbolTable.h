#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <string>

using namespace std;

void reset_symbol_table();
//Empty the symbol table

void declare_argument(string id);
//Add argument 'id' to the symbol table

void declare_local(string id);
//Add local variable 'id' to the symbol table

int get_slot(string id);
//Get the delta assigned to variable 'id'

int get_nb_argument();
//#declared arguments

int get_nb_local();
//#declared local variable

#endif
