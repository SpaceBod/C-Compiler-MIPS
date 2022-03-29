#include <iostream>
#include "ast.hpp"

SymTabADT SymTab;
StackPtr StkPtr;

int main(int argc, char *argv[])
{
    FILE *fileInput = fopen(argv[1], "r");
    std::cout << ".text" << std::endl;
    const Main *ast = parseAST(fileInput);
    ast->Translate2MIPS("$v0");
    /*
    if(ast->getType() == "INT") {
        ast->Translate2MIPS("$v0");
    }
    else if(ast->getType() == "FLOAT") {
        ast->Translate2MIPS("$f0");
    }
    */
    return 0;
}