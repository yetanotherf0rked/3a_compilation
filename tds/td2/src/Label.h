#ifndef __LABEL_H
#define __LABEL_H

#include <iostream>

using namespace std;

void reset_labels(); //labels# and stack

string new_label(string prefix);
void push_label(string label);
string pop_label();

#endif
