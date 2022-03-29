#include "ast.hpp"

SymTab SymbolTable;
StackPtr StackPointer;

int main(int argc, char *argv[])
{
    FILE *fileInput = fopen(argv[1], "r");
    const Function *ast = parseAST(fileInput);
    ast->pretty_print(std::cout);

    std::cout << std::endl;
    ast->Translate2MIPS("$t0");
    std::cout << std::endl;
    std::cout << std::endl;
    return 0;
}