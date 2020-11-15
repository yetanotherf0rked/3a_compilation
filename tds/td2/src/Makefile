##########################################################################
# Scc, the Simple C Compiler
# written by Christophe Alias and <your name here>
##########################################################################

OBJS            = Label.o SymbolTable.o Backend-x86.o parser.o lexer.o main.o 

BIN             = ../bin/scc

all: $(OBJS)
	g++ $(DEBUG) $(OBJS) -lfl -lm -o $(BIN)

%.o: %.cc
	g++ $(DEBUG) -c $<

clean:
	-rm -f *.o bison_report parser.cc parser.h lexer.cc *~ \#*

realclean:
	$(MAKE) clean
	-rm -f $(BIN)

parser.cc: parser.ypp
	bison --defines=parser.h --report=lookahead --report-file=bison_report -o parser.cc parser.ypp

lexer.cc: lexer.l
	flex -olexer.cc lexer.l

