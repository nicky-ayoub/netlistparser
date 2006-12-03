cdlParser : cdlParser.tab.c lex.yy.c netlistclasses.hpp netlistfunctions.hpp
	@g++ -o cdlParser cdlParser.tab.c lex.yy.c

cdlParser.tab.c: cdlParser.y
	@/usr/bin/bison -v -d cdlParser.y

lex.yy.c: cdlLex.l
	@flex cdlLex.l

.PHONY: test clean

test: cdlParser
	@cat ../../NETLIST/cdl  |./cdlParser

clean:
	@\rm lex.yy.c cdlParser.output cdlParser.tab.c cdlParser.tab.h cdlParser
