#include "Backend.h"

#include <iostream>

void push(int address)
{
  cout << "\tpush\t" << address << endl;
}

void mpush(int imm)
{
  cout << "\tmpush\t" << imm << endl;
}

void pop(int address)
{
  cout << "\tpop\t" << address << endl;
}

void add()
{
  cout << "\tadd\t" << endl;
}

void sub()
{
  cout << "\tsub\t" << endl;
}

void mul()
{
  cout << "\tmul\t" << endl;
}

void div()
{
  cout << "\tdiv\t" << endl;
}

void testg()
{
  cout << "\ttestg\t" << endl;
}

void teste()
{
  cout << "\tteste\t" << endl;
}

void testne()
{
  cout << "\ttestne\t" << endl;
}

void label(string label)
{
  cout << label << ":" << endl;
}

void jz(string label)
{
  cout << "\tjz\t" << label << endl;
}

void jmp(string label)
{
  cout << "\tjmp\t" << label << endl;
}

void stop()
{
  cout << "\tstop\t" << endl;
}

void alloc(int size)
{
  cout << "\talloc\t" << size << endl;
}

void free()
{
  cout << "\tfree\t" << endl;
}

void call(string label)
{
  cout << "\tcall\t" << label << endl;
}

void ret(int n)
{
  cout << "\tret\t" << n << endl;
}

void iret(int n)
{
  cout << "\tiret\t" << n << endl;
}

//
// Runtime handling
//

void call_runtime(string service)
{
  cout << "\tcall\t" << service << endl;
}

void raw(string asm_code)
{
  cout << asm_code << endl;
}
