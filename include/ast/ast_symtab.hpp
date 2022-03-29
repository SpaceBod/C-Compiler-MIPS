#ifndef ast_symtab_hpp
#define ast_symtab_hpp

#include <cassert>
#include "ast_stacks.hpp"
#include "ast_nodes.hpp"

class SymTabADT
{
private:
    Node *head[50];
    int current_scope;
    std::string funcstart[50];
    std::string funcend[50];
    std::string loopstart[50];
    std::string loopend[50];
    int funcscope;
    int loopscope;

public:
    SymTabADT()
    {
        int size = sizeof(head) / sizeof(head[0]);
        for (int i = 0; i < size; i++)
        {
            head[i] = nullptr;
        }
        current_scope = 0;
    }

    std::string getfuncstart()
    {
        return funcstart[funcscope];
    }

    std::string returnEndFunc()
    {
        return funcend[funcscope];
    }

    std::string returnStartLoop()
    {
        return loopstart[loopscope];
    }

    std::string returnEndLoop()
    {
        return loopend[loopscope];
    }

    int getScopeFunc()
    {
        return funcscope;
    }

    int returnLoopScope()
    {
        return loopscope;
    }

    void setfuncstart(std::string _funcstart)
    {
        funcstart[funcscope] = _funcstart;
    }

    void setfuncend(std::string _funcend)
    {
        funcend[funcscope] = _funcend;
    }

    void setStartLoop(std::string _loopstart)
    {
        loopstart[loopscope] = _loopstart;
    }

    void setEndLoop(std::string _loopend)
    {
        loopend[loopscope] = _loopend;
    }

    int returnScopeCurrent()
    {
        return current_scope;
    }

    void setScopeFunc(int _funcscope)
    {
        funcscope = _funcscope;
    }

    void setScopeLoop(int _loopscope)
    {
        loopscope = _loopscope;
    }

    bool insert(std::string type, std::string kind, std::string name, std::string address)
    {
        if (head[current_scope] == nullptr)
        {
            head[current_scope] = new Node(type, kind, name, address);
            return true;
        }
        else
        {
            Node *start = head[current_scope];
            while (start->getNext() != nullptr)
            {
                start = start->getNext();
            }
            start->setNext(new Node(type, kind, name, address));
            return true;
        }
        return false;
    }

    bool edit(std::string type, std::string kind, std::string name, std::string address)
    {
        if (head[current_scope] == nullptr)
        {
            return false;
        }
        else
        {
            Node *start = head[current_scope];
            while (start != nullptr)
            {
                if (start->getName() == name)
                {
                    start->setFormat(kind);
                    start->setAddress(address);
                    start->setType(type);
                    return true;
                }
                start = start->getNext();
            }
        }
        return false;
    }

    std::string lookup(std::string name)
    {
        Node *start = head[current_scope];
        if (start == nullptr)
        {
            return "Unknown reference from ID";
        }
        while (start != nullptr)
        {
            if (start->getName() == name)
            {
                return start->getAddress();
            }
            else
            {
                start = start->getNext();
            }
        }
        return "Unknown reference from ID";
    }

    std::string returnType(std::string name)
    {
        Node *start = head[current_scope];
        if (start == nullptr)
        {
            return "Unknown reference from ID";
        }
        while (start != nullptr)
        {
            if (start->getName() == name)
            {
                return start->returnType();
            }
            else
            {
                start = start->getNext();
            }
        }
        return "Unknown reference from ID";
    }

    std::string returnKind(std::string name)
    {
        Node *start = head[current_scope];
        if (start == nullptr)
        {
            return "Unknown reference from ID";
        }
        while (start != nullptr)
        {
            if (start->getName() == name)
            {
                return start->returnKind();
            }
            else
            {
                start = start->getNext();
            }
        }
        return "Unknown reference from ID";
    }

    bool enterScope()
    {
        current_scope = current_scope + 1;
        assert(head[current_scope] == nullptr);
        Node *old_list = head[current_scope - 1];
        if (old_list != nullptr)
        {
            head[current_scope] = new Node(old_list->returnType(), old_list->returnKind(), old_list->getName(), old_list->getAddress());
            Node *start = head[current_scope];
            while (old_list->next != nullptr)
            {
                old_list = old_list->next;
                head[current_scope]->next = new Node(old_list->returnType(), old_list->returnKind(), old_list->getName(), old_list->getAddress());
                head[current_scope] = head[current_scope]->next;
            }
            head[current_scope] = start;
            return true;
        }
        else
        {
            head[current_scope] = nullptr;
            return true;
        }
    }

    bool exitScope()
    {
        if (head[current_scope] == nullptr)
        {
            current_scope = current_scope - 1;
            return true;
        }
        Node **list = &head[current_scope];
        Node *current = *list;
        Node *next = nullptr;
        if (current != nullptr)
        {
            next = current->getNext();
            delete (current);
            current = next;
        }
        *list = nullptr;
        if (head[current_scope] != nullptr)
        {
            std::cout << "this is wrong" << std::endl;
            return false;
        }
        current_scope = current_scope - 1;
        return true;
    }
};

#endif