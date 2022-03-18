CPPFLAGS += -std=c++17 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I inc

all : bin/print_canonical

src/C90Parser.tab.cpp src/C90Parser.tab.hpp : src/C90Parser.y
	bison  -v  -d src/C90Parser.y -o src/C90Parser.tab.cpp

src/C90Lexer.yy.cpp : src/C90Lexer.flex src/C90Parser.tab.hpp
	flex -o src/C90Lexer.yy.cpp  src/C90Lexer.flex

*.o: *.c
	g++ ${CPPFLAGS} -c $^

bin/print_canonical : src/print_canonical.o src/C90Parser.tab.o src/C90Lexer.yy.o src/C90Parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) -o $@ $^

clean :
	rm -f src/*.o
	rm -f bin/*