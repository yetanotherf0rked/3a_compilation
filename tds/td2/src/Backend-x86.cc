#include "Backend.h"

#include <iostream>
#include <fstream> //for .asm output
#include <sstream> //for address()

#include "Label.h"

extern ofstream asm_output;

#define WORD_SIZE 8

string address(int slot)
{
  stringstream ss;
  int bp_delta = -1*WORD_SIZE*(slot+1);
  if(bp_delta < 0)
    ss << "rbp - " << -1*bp_delta;
  if(bp_delta > 0)
    ss << "rbp + " << bp_delta;
  if(bp_delta == 0) //never!
    ss << "rbp";
  return ss.str();
}

void push(int slot)
{
  asm_output << "\tmov\trax,[" << address(slot) << "]" << endl
	     << "\tpush\trax" << endl;
}

void mpush(int imm)
{
  asm_output << "\tmov\trax," << imm << endl
	     << "\tpush\trax" << endl;
}

void pop(int slot)
{
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tmov\t[" << address(slot) << "],rax" << endl;
}

void add()
{
  asm_output << "\tpop\trbx" << endl;
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tadd\trax,rbx" << endl;
  asm_output << "\tpush\trax" << endl;
}

void sub()
{
  asm_output << "\tpop\trbx" << endl;
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tsub\trax,rbx" << endl;
  asm_output << "\tpush\trax" << endl;
}

void mul()
{
  asm_output << "\tpop\trbx" << endl;
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tmul\trbx" << endl;
  asm_output << "\tpush\trax" << endl;
}

void div()
{
  asm_output << "\tpop\trbx" << endl;
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tmul\trbx" << endl;
  asm_output << "\tpush\trax" << endl;
}

void testg()
{
  asm_output << "\tpop\trbx" << endl;
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tcmp\trax,rbx" << endl;
  asm_output << "\tmov\trax,0" << endl;
  asm_output << "\tsetg\tal" << endl;
  asm_output << "\tpush\trax" << endl;
}

void testne()
{
  asm_output << "\tpop\trbx" << endl;
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tcmp\trax,rbx" << endl;
  asm_output << "\tmov\trax,0" << endl;
  asm_output << "\tsetne\tal" << endl;
  asm_output << "\tpush\trax" << endl;
}

void teste()
{
  asm_output << "\tpop\trbx" << endl;
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tcmp\trax,rbx" << endl;
  asm_output << "\tmov\trax,0" << endl;
  asm_output << "\tsete\tal" << endl;
  asm_output << "\tpush\trax" << endl;
}

void label(string label)
{
  asm_output << label << ":" << endl;
}

void jz(string label)
{
  asm_output << "\tpop\trax" << endl;
  asm_output << "\tcmp\trax,0" << endl;
  string label_end = new_label("end_cmp");
  asm_output << "\tjne\t" << label_end << endl;
  jmp(label);
  asm_output << label_end << ":" << endl;
}

void jmp(string label)
{
  asm_output << "\tjmp\t" << label << endl;
}

void stop()
{
  string label_stop = new_label("stop");
  asm_output << "\tmov\trax,0" << endl << "\tret\t" << endl;
}

void alloc(int nb_slots)
{
  raw("\tpush\trbp");
  raw("\tmov\trbp,rsp");
  asm_output << "\tsub\trsp," << WORD_SIZE*nb_slots << endl;
}

void free()
{
  raw("\tmov\trsp,rbp");
  raw("\tpop\trbp");
}

void call(string label)
{
  asm_output << "\tcall\t" << label << endl;
}

void ret(int n)
{
  asm_output << "\tret\t" << WORD_SIZE*n << endl;
}

void iret(int n)
{
  asm_output << "\tpop\trax" << endl;
  free();
  asm_output << "\tpop\trbx" << endl
	     << "\tadd\trsp," << WORD_SIZE*n << endl
	     << "\tpush\trax" << endl
	     << "\tjmp\trbx" << endl;
}


//
// Runtime handling
//

void call_runtime(string service)
{
  asm_output << "\tcall\t" << service << endl;
}

void raw(string asm_code)
{
  asm_output << asm_code << endl;
}
