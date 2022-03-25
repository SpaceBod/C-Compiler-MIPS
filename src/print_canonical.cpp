#include "ast.hpp"

int main(int argc, char *argv[])
{
    FILE *fileInput = fopen(argv[1], "r");
    std::cout << ".text" << std::endl;
    std::cout << ".globl main" << std::endl;

    std::cout << "subu $sp, $sp, 4" << std::endl;
    std::cout << "sw $ra, 4($sp)" << std::endl;
    const Function *ast = parseAST(fileInput);
    std::cout << std::endl;
    std::cout << std::endl;
    ast->Translate2MIPS("$t0");
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "lw $ra, 4($sp)" << std::endl;
    std::cout << "addu $sp, $sp, 4" << std::endl;
    std::cout << "j $ra" << std::endl;
    std::cout << std::endl;

    return 0;
}