#include "ast.hpp"

SymTabADT SymTab;
StackPtr StkPtr;

int main()
{
    const Main *ast = parseAST();
    std::cout << ".text" << std::endl;
    ast->Translate2MIPS("$v0");
    std::cout << std::endl;

    return 0;
}
