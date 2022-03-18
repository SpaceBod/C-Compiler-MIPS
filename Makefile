CPPFLAGS += -w -g -Wno-unused-parameter -std=c++11 #17
CPPFLAGS += -I include

all : bin/print_canonical

src/C90Parser.tab.cpp src/C90Parser.tab.hpp : src/C90Parser.y
	bison  -v  -d src/C90Parser.y -o src/C90Parser.tab.cpp

src/C90Lexer.yy.cpp : src/C90Lexer.flex src/C90Parser.tab.hpp
	flex -o src/C90Lexer.yy.cpp  src/C90Lexer.flex

bin/evaluate_expression : src/evaluate_expression.o src/C90Parser.tab.o src/C90Lexer.yy.o src/C90Parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/evaluate_expression $^


bin/print_canonical : src/print_canonical.o src/C90Parser.tab.o src/C90Lexer.yy.o src/C90Parser.tab.o
	make src/C90Parser.tab.cpp 
	make src/C90Parser.tab.hpp
	make src/C90Lexer.yy.cpp
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

clean :
	rm -f src/*.o
	rm -f bin/*

	rm -f src/C90Parser.tab.* 
	rm -f src/C90Parser.output
	rm -f src/C90Lexer.yy.cpp