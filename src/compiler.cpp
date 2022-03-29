#include <iostream>
#include "ast.hpp"

SymTab SymbolTable;
StackPtr StackPointer;

int main(int argc, char *argv[])
{
	FILE *fileInput = fopen(argv[1], "r");
	std::cout << ".text" << std::endl;
	const Function *ast = parseAST(fileInput);
	ast->Translate2MIPS("$v0");
	return 0;
}