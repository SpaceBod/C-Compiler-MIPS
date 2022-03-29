#ifndef ast_statements_hpp
#define ast_statements_hpp

#include "ast_expressions.hpp"
#include "ast_primitives.hpp"
#include "ast_symtab.hpp"

class Stat;

typedef const Stat *StatPtr;

class Stat
{
public:
    virtual ~Stat() {}

    virtual void pretty_print(std::ostream &dst) const = 0;

    virtual void Translate2MIPS(std::string destReg) const = 0;
};

class StatList;

typedef const StatList *StatListPtr;

class StatList
    : public Stat
{
private:
    StatPtr stat = nullptr;
    Identifier *variable = nullptr;
    StatListPtr statDecList = nullptr;

public:
    StatList(StatPtr _stat, StatListPtr _statDecList = nullptr)
        : stat(_stat), statDecList(_statDecList)
    {
    }
    StatList(Identifier *_variable, StatListPtr _statDecList = nullptr)
        : variable(_variable), statDecList(_statDecList)
    {
    }
    virtual ~StatList()
    {
        delete stat;
        delete statDecList;
        delete variable;
    }
    StatPtr returnStat() const
    {
        return stat;
    }
    Identifier *returnVar() const
    {
        return variable;
    }
    StatListPtr returnStatDecList() const
    {
        return statDecList;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        if (stat != nullptr)
        {
            stat->pretty_print(dst);
        }
        else if (variable != nullptr)
        {
            variable->pretty_print(dst);
        }
        if (statDecList != nullptr)
        {
            statDecList->pretty_print(dst);
        }
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        if (returnStat() != nullptr)
        {
            returnStat()->Translate2MIPS(destReg);
        }
        else if (returnVar() != nullptr)
        {
            returnVar()->Translate2MIPS(destReg);
        }
        if (returnStatDecList() != nullptr)
        {
            returnStatDecList()->Translate2MIPS(destReg);
        }
    }
};

class SelectStat
    : public Stat
{
private:
    ExprPtr cond;
    StatPtr stat;

public:
    SelectStat(ExprPtr _cond, StatPtr _stat = nullptr)
        : cond(_cond), stat(_stat)
    {
    }
    virtual ~SelectStat()
    {
        delete cond;
        delete stat;
    }
    ExprPtr returnCond() const
    {
        return cond;
    }
    StatPtr returnStat() const
    {
        return stat;
    }
};

class IfStat
    : public SelectStat
{
private:
    StatPtr else_branch = nullptr;

public:
    IfStat(ExprPtr _cond, StatPtr _if_branch = nullptr, StatPtr _else_branch = nullptr)
        : SelectStat(_cond, _if_branch), else_branch(_else_branch)
    {
    }
    ~IfStat()
    {
        delete else_branch;
    }
    StatPtr returnElse() const
    {
        return else_branch;
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "if ( ";
        returnCond()->pretty_print(dst);
        dst << " ) ";
        dst << '\n';
        returnStat()->pretty_print(dst);
        if (else_branch != nullptr)
        {
            dst << "else ";
            else_branch->pretty_print(dst);
        }
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnCond()->Translate2MIPS("$t0");
        std::string exit = makeName("exit");
        if (else_branch != nullptr)
        {
            std::string else_stat = makeName("else_stat");
            std::cout << "beq $t0, $0, " << else_stat << std::endl;
            returnStat()->Translate2MIPS(destReg);
            std::string exit = makeName("exit");
            std::cout << "j " << exit << std::endl;
            std::cout << else_stat << ":" << std::endl;
            returnElse()->Translate2MIPS(destReg);
            std::cout << exit << ":" << std::endl;
        }
        else
        {
            std::string exit = makeName("exit");
            std::cout << "beq $t0, $0, " << exit << std::endl;
            returnStat()->Translate2MIPS(destReg);
            std::cout << exit << ":" << std::endl;
        }
    }
};

class SwitchStat
    : public SelectStat
{
public:
    SwitchStat(ExprPtr _cond, StatPtr _stat)
        : SelectStat(_cond, _stat)
    {
    }
    ~SwitchStat()
    {
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "switch ( ";
        returnCond()->pretty_print(dst);
        dst << " ) ";
        returnStat()->pretty_print(dst);
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnCond()->Translate2MIPS("$s0");
        std::string exit = makeName("exit");
        SymTab.setScopeLoop(SymTab.returnLoopScope() + 1);
        SymTab.setEndLoop(exit);
        StkPtr.setIncrement(StkPtr.getIncrement() + 4);
        StkPtr.setScopeIncrement(StkPtr.returnScopeIncrement() + 4);
        std::cout << "addiu $sp, $sp, -4" << std::endl;
        std::cout << "sw $s1, 0($sp)" << std::endl;
        std::cout << "addiu $s1, $0, 0" << std::endl;
        returnStat()->Translate2MIPS(destReg);
        std::cout << exit << ":" << std::endl;
        std::string startCase = makeName("case");
        std::cout << startCase << ":" << std::endl;
    }
};

class LoopStat
    : public Stat
{
private:
    ExprPtr cond;
    StatPtr stat = nullptr;

public:
    LoopStat()
    {
    }
    LoopStat(ExprPtr _cond, StatPtr _stat = nullptr)
        : cond(_cond), stat(_stat)
    {
    }
    ~LoopStat()
    {
        delete cond;
        delete stat;
    }
    ExprPtr returnCond() const
    {
        return cond;
    }
    StatPtr returnStat() const
    {
        return stat;
    }
};

class WhileStat
    : public LoopStat
{
public:
    WhileStat(ExprPtr _cond, StatPtr _stat = nullptr)
        : LoopStat(_cond, _stat)
    {
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "while ( ";
        returnCond()->pretty_print(dst);
        dst << " ) ";
        returnStat()->pretty_print(dst);
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::string exit = makeName("exit");
        std::string enter = makeName("enter");
        SymTab.setScopeLoop(SymTab.returnLoopScope() + 1);
        SymTab.setStartLoop(enter);
        SymTab.setEndLoop(exit);
        std::cout << enter << ":" << std::endl;
        returnCond()->Translate2MIPS("$t0");
        std::cout << "beq $t0, $0, " << exit << std::endl;
        returnStat()->Translate2MIPS(destReg);
        std::cout << "j " << enter << std::endl;
        std::cout << exit << ":" << std::endl;
        SymTab.setScopeLoop(SymTab.returnLoopScope() - 1);
    }
};

class ForStat
    : public LoopStat
{
private:
    Identifier *initVar = nullptr;
    ExprPtr initExpr = nullptr;
    ExprPtr incrementExpr;

public:
    ForStat(ExprPtr _initExpr, ExprPtr _checkExpr, ExprPtr _incrementExpr, StatPtr _stat)
        : LoopStat(_checkExpr, _stat), initExpr(_initExpr), incrementExpr(_incrementExpr)
    {
    }
    ForStat(Identifier *_initVar, ExprPtr _checkExpr, ExprPtr _incrementExpr, StatPtr _stat)
        : LoopStat(_checkExpr, _stat), initVar(_initVar), incrementExpr(_incrementExpr)
    {
    }
    ~ForStat()
    {
        delete initVar;
        delete initExpr;
        delete incrementExpr;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "for ( ";
        if (initVar != nullptr && initExpr == nullptr)
        {
            initVar->pretty_print(dst);
        }
        else if (initVar == nullptr && initExpr != nullptr)
        {
            initExpr->pretty_print(dst);
            dst << " ; ";
        }
        returnCond()->pretty_print(dst);
        dst << " ; ";
        incrementExpr->pretty_print(dst);
        dst << " ) \n";
        returnStat()->pretty_print(dst);
        dst << '\n';
    }
    virtual void Translate2MIPS(std::string destReg) const override
    {
        if (initVar != nullptr && initExpr == nullptr)
        {
            initVar->returnExpr()->Translate2MIPS("$t0");
        }
        else if (initVar == nullptr && initExpr != nullptr)
        {
            initExpr->Translate2MIPS("$t0");
        }
        else
        {
            std::cout << "ERROR: no initial value in for loop" << std::endl;
        }

        std::string enter = makeName("enter");
        std::cout << enter << ":" << std::endl;
        std::string exit = makeName("exit");
        SymTab.setScopeLoop(SymTab.returnLoopScope() + 1);
        SymTab.setStartLoop(enter);
        SymTab.setEndLoop(exit);
        returnCond()->Translate2MIPS("$t1");
        std::cout << "beq $t1, $0, " << exit << std::endl;
        returnStat()->Translate2MIPS(destReg);
        incrementExpr->Translate2MIPS("$t0");
        std::cout << "j " << enter << std::endl;
        std::cout << exit << ":" << std::endl;
        SymTab.setScopeLoop(SymTab.returnLoopScope() - 1);
    }
};

class ExprStat
    : public Stat
{
private:
    ExprPtr expr = nullptr;

public:
    ExprStat(ExprPtr _expr = nullptr)
        : expr(_expr)
    {
    }
    ~ExprStat()
    {
        delete expr;
    }
    ExprPtr returnExp() const
    {
        return expr;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        if (expr != nullptr)
        {
            expr->pretty_print(dst);
        }
        dst << ";";
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        returnExp()->Translate2MIPS(destReg);
    }
};

class JumpStat
    : public Stat
{
public:
    JumpStat()
    {
    }
    ~JumpStat()
    {
    }
};

class ReturnStat
    : public JumpStat
{
private:
    ExprPtr expr = nullptr;

public:
    ReturnStat(ExprPtr _expr = nullptr)
        : expr(_expr)
    {
    }
    ~ReturnStat()
    {
        delete expr;
    }
    ExprPtr returnExp() const
    {
        return expr;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "return ";
        if (expr != nullptr)
        {
            expr->pretty_print(dst);
        }
        dst << ";";
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        if (destReg[1] == 'f')
        {
            returnExp()->Translate2MIPS("$f0");
            std::cout << "j " << SymTab.returnEndFunc() << std::endl;
            StkPtr.setReturnFunc(1);
        }
        else
        {
            returnExp()->Translate2MIPS("$t0");
            if (StkPtr.returnNullFunc() == 1)
            {
                StkPtr.setNullFunc(0);
            }
            else
            {
                std::cout << "add $v0, $0, $t0" << std::endl;
                std::cout << "j " << SymTab.returnEndFunc() << std::endl;
                StkPtr.setReturnFunc(1);
            }
        }
    }
};

class ContinueStat
    : public JumpStat
{
public:
    ContinueStat()
    {
    }
    ~ContinueStat()
    {
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "continue;";
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::cout << "j " << SymTab.returnStartLoop() << std::endl;
    }
};

class BreakStat
    : public JumpStat
{
public:
    BreakStat()
    {
    }
    ~BreakStat()
    {
    }

    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "break;";
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        std::cout << "j " << SymTab.returnEndLoop() << std::endl;
    }
};

class LabelStat
    : public Stat
{
private:
    ExprPtr expr = nullptr;
    StatPtr stat = nullptr;

public:
    LabelStat(StatPtr _stat, ExprPtr _expr = nullptr)
        : expr(_expr), stat(_stat)
    {
    }
    ~LabelStat()
    {
        delete expr;
        delete stat;
    }
    ExprPtr returnExp() const
    {
        return expr;
    }
    StatPtr returnStat() const
    {
        return stat;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "case ";
        if (expr != nullptr)
        {
            expr->pretty_print(dst);
        }
        dst << ": ";
        if (stat != nullptr)
        {
            stat->pretty_print(dst);
        }
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        if (expr != nullptr)
        {
            std::string startCase = makeName("case");
            std::string endCase = makeName("caseEnd");
            std::cout << startCase << ":" << std::endl;
            std::cout << "bne $0, $s1, " << endCase << std::endl;
            returnExp()->Translate2MIPS("$t0");
            std::cout << "bne $t0, $s0, " << startCase.substr(0, 6) + std::to_string(std::stoi(startCase.substr(6, startCase.length() - 6)) + 2) << std::endl;
            std::cout << "addiu $s1, $0, 1" << std::endl;
            std::cout << endCase << ":" << std::endl;
            returnStat()->Translate2MIPS("destReg");
        }
        else
        {
            std::string startCase = makeName("case");
            std::string endCase = makeName("caseEnd");
            std::cout << startCase << ":" << std::endl;
            std::cout << "bne $0, $s1, " << endCase << std::endl;
            std::cout << "lw $s1, 0($sp)" << std::endl;
            std::cout << endCase << ":" << std::endl;
            returnStat()->Translate2MIPS("destReg");
        }
    }
};

class CompoundStat
    : public Stat
{
private:
    StatListPtr statList = nullptr;

public:
    CompoundStat()
    {
    }
    CompoundStat(StatListPtr _statList)
        : statList(_statList)
    {
    }
    ~CompoundStat()
    {
        delete statList;
    }
    StatListPtr returnStatList() const
    {
        return statList;
    }
    virtual void pretty_print(std::ostream &dst) const override
    {
        dst << "{ ";
        if (statList != nullptr)
        {
            statList->pretty_print(dst);
        }
        dst << "}";
        dst << '\n';
    }

    virtual void Translate2MIPS(std::string destReg) const override
    {
        SymTab.enterScope();
        StkPtr.setScopeCurrent(StkPtr.returnScopeCurrent() + 1);
        StkPtr.setScopeIncrement(0);
        if (returnStatList() != nullptr)
        {
            returnStatList()->Translate2MIPS(destReg);
        }
        std::cout << "addiu $sp, $sp, " << StkPtr.returnScopeIncrement() << std::endl;
        StkPtr.setIncrement(StkPtr.getIncrement() - StkPtr.returnScopeIncrement());
        if (StkPtr.getfreturn() != 1)
        {
            StkPtr.setScopeIncrement(0);
        }
        StkPtr.setScopeCurrent(StkPtr.returnScopeCurrent() - 1);
        SymTab.exitScope();
    }
};

#endif