#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream> //for .asm output

//Interface with Flex & Bison
extern FILE *yyin;              //from Flex
extern int yyparse(void);       //from Bison
extern int line_number;         //

using namespace std;

ofstream asm_output;

int main(int argc, char** argv)
{
  if(argc != 2)
    {
      cout << "syntax: scc input.c" << endl;
      return 1;
    }

  //Open .asm file
  char* input_file = strdup(argv[1]);
  int len = strlen(input_file);
  input_file[len-1] = 0; //remove final 'c'
  string output_file = string(input_file);
  output_file += "asm";
  asm_output.open(output_file.c_str());

  yyin = fopen(argv[1],"r");
  if(yyin == 0)
    {
      cerr << "File not found: " << argv[1] << endl;
      exit(1);
    }

  line_number = 1;

  //Compile...
  int bison_return_code = yyparse();

  //Close .asm file
  asm_output.close();

  //Concat the runtime library to the asm file...
  string add_runtime_command = "cat ";
  add_runtime_command += "runtime-x86.asm ";
  add_runtime_command += output_file;
  add_runtime_command += " > ";
  add_runtime_command += output_file;
  add_runtime_command += ".swap";
  system(add_runtime_command.c_str());

  add_runtime_command = "mv ";
  add_runtime_command += output_file;
  add_runtime_command += ".swap ";
  add_runtime_command += output_file;
  system(add_runtime_command.c_str());
}
