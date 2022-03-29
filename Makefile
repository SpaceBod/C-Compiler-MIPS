  
CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : bin/print_canonical, bin/compiler, bin/compile_test

src/parser.tab.cpp src/parser.tab.hpp : src/C90Parser.y
	bison -v -d src/C90Parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/C90Lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/C90Lexer.flex


bin/c_compiler : bin/compiler src/wrapper.sh
	cp src/wrapper.sh bin/c_compiler
	chmod u+x bin/c_compiler

bin/compiler : src/compiler.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compiler $^

bin/print_canonical : src/print_canonical.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/print_canonical $^

bin/compile_test : src/compile_test.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o bin/compile_test $^
	
clean :
	rm -f src/*.tab.cpp
	rm -f src/*.yy.cpp
	rm -f src/*.tab.hpp
	rm -f src/*.o
	rm -f src/*.output
	rm -f bin/*
	rm -r testout
	rm -r bin
