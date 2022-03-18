#include "ast.hpp"

int main()
{
    const Function *ast=parseAST();

    ast->pretty_print(std::cout);
    std::cout<<std::endl;

    return 0;
}