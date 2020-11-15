#include "Label.h"

#include <stdlib.h> //for exit()
#include <sstream>

#include <map>
#include <vector>

map<string,int> last_label;
vector<string> label_stack;

void reset_labels()
{
  last_label.erase(last_label.begin(),last_label.end());
  label_stack.resize(0);
}

string new_label(string prefix)
{
  string result;
  stringstream sstream;

  if(last_label.find(prefix) == last_label.end())
    last_label[prefix] = 0;

  sstream << prefix << "_" << last_label[prefix];
  sstream >> result; //No simple conversion int->string in C++ ...

  last_label[prefix]++;

  return result;
}

void push_label(string label)
{
  label_stack.push_back(label);
}

string pop_label()
{
  if(label_stack.size() == 0)
    {
      cerr << "Label::pop_label(): empty stack" << endl;
      exit(1);
    }

  string result = label_stack.back();
  label_stack.pop_back();
  
  return result;
}
