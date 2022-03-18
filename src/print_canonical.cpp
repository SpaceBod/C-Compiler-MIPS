#include "ast.hpp"

int main(int argc, char *argv[])
{
    FILE *fileInput = fopen(argv[1],"r");
    std::cout << ".text" << std::endl;

    const Function *ast=parseAST(fileInput);

    ast->pretty_print(std::cout);
    std::cout<<std::endl;

    return 0;
}