#include "ast.hpp"

#include <string>

static int makeNameUnq = 0;

static std::string makeName(std::string base)
{
    return "_" + base + "_" + std::to_string(makeNameUnq++);
}

void CompileFunc(const Function *ast){


}