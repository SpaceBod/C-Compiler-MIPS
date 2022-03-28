#ifndef symtab_hpp
#define symtab_hpp
#include <vector>
#include <cassert>
#include <map>

#include "ast_nodes.hpp"
#include "ast_stackptr.hpp"

// +--------+-------+--------+
// |   ID   | KIND  |  TYPE  |
// +--------+-------+--------+
// | _var_1 | var   | int    |
// | _var_2 | var   | bool   |  
// | _var_3 | var   | double |
// +--------+-------+--------+

// Class for the symbol table - accesses NODES 
class SymTab
{
private:
    Node *head[MAX];
    
    int scopeCurrent;
    int scopeFunction;
    int scopeLoop;

    std::string startFunction[MAX], endFunction[MAX];
    std::string startLoop[MAX], endLoop[MAX];

public:
    SymTab()
    {
        int size = sizeof(head)/sizeof(head[0]);
        for(int i = 0; i < size; i++)
        {
            // sets head[i] to "zero as an symAddr"
            head[i] = nullptr;
        }
        // Init scope to zero
        scopeCurrent = 0;
    }

    int getScopeCurrent()
        {
            return scopeCurrent;
        }

    // Function scopes
    void setScopeFunction(int newScopeFunction)
    {
        scopeFunction = newScopeFunction;
    }
    int returnScopeFunction()
    {
        return scopeFunction;
    }
    std::string returnStartFunction()
    {
        return startFunction[scopeFunction];
    }
    void setStartFunction(std::string newStartFunction)
    {
        startFunction[scopeFunction] = newStartFunction;
    }
    std::string returnEndFunction()
    {
        return endFunction[scopeFunction];
    }
    void setEndFunction(std::string newEndFunction)
    {
        endFunction[scopeFunction] = newEndFunction;
    }
    
    // Loop scopes
    void setScopeLoop(int newScopeLoop)
    {
        scopeLoop = newScopeLoop;
    }
    int returnScopeLoop()
    {
        return scopeLoop;
    }
    std::string returnStartLoop()
    {
        return startLoop[scopeLoop];
    }
    std::string returnEndLoop()
    {
        return endLoop[scopeLoop];
    }
    void setStartLoop(std::string newStartLoop)
    {
        startLoop[scopeLoop] = newStartLoop;
    }
    void setEndLoop(std::string newEndLoop)
    {
        endLoop[scopeLoop] = newEndLoop;
    }

    // Inserting a new symbol into the table
    // Table: ID    KIND    TYPE
    bool insert(std::string symID, std::string symKind, std::string symType, std::string symAddr)
    {        
        if(head[scopeCurrent] != nullptr)
        {
            Node *start = head[scopeCurrent];
            // Finds free location
            while(start->returnNext() != nullptr)
            {
                start = start->returnNext();
            }
            // Inserts new symbol
            start->setNext(new Node(symID, symKind, symType, symAddr));
            return true;
        }
        else
        {
            // Inserts new symbol if first location is free
            head[scopeCurrent] = new Node(symID, symKind, symType, symAddr);
            return true;
        }
        return false;
    }

    // returns the length of th symID
    int getSize(std::string symID)
    {
        Node *start = head[scopeCurrent];
        while(start != nullptr)
        {
            if(start->returnSymID() == symID)
            {
                return start->returnLen();
            }
            else
            {
                start = start->returnNext();
            }
        }
        return 0;
    }

    // Looks up the address location of the symID
    std::string lookup(std::string symID)
    {
        Node *start = head[scopeCurrent];
        while(start != nullptr)
        {
            if(start->returnSymID() == symID)
            {
                return start->returnAddress();
            }
            else
            {
                start = start->returnNext();
            }
        }
        return ("Symbol ID: " + symID + " not found");
    }

    // Looks up the symID and return the type
    std::string returnType(std::string symID)
    {
        Node *start = head[scopeCurrent];
        while(start != nullptr)
        {
            if(start->returnSymID() == symID)
            {
                return start->returnType();
            }
            else
            {
                start = start->returnNext();
            }
        }
        return ("Symbol ID: " + symID + " not found");
    }

    // Returns a vector of symIDs of the same symKind
    std::vector<std::string> vectorSymID(std::string symKind)
    {
        std::vector<std::string> vectorSymIDs;
        Node *start = head[scopeCurrent];
        while(start != nullptr)
        {
            if(start->returnKind() == symKind)
            {
                vectorSymIDs.push_back(start->returnSymID());
            }
            start = start->returnNext();
        }
        return vectorSymIDs;
    }

    // Looks up the symID and return the kind
    std::string returnKind(std::string symID)
    {
        Node *start = head[scopeCurrent];
        while(start != nullptr)
        {
            if(start->returnSymID() == symID)
            {
                return start->returnKind();
            }
            else
            {
                start = start->returnNext();
            }
        }
        return ("Symbol ID: " + symID + " not found");
    }

    // Edit an existing symID's values
    bool edit(std::string symID, std::string symKind, std::string symType, std::string symAddr)
    {
        if(head[scopeCurrent] != nullptr)
        {
            Node *start = head[scopeCurrent];
            while(start != nullptr)
            {
                // if symID matches -> edit properties
                if(start->returnSymID() == symID)
                {
                    start->setType(symType);
                    start->setKind(symKind);
                    start->setAddress(symAddr);
                    return true;
                }
                start = start->returnNext();
            }
        }
        else
        {
            return false;
        }
    }

    // Adding a new scope
    bool scopeEnter()
    {
        scopeCurrent += 1;
        Node *plist = head[scopeCurrent-1];
        if (plist != nullptr)
        {
            head[scopeCurrent] = new Node(plist->returnSymID(), plist->returnKind(), plist->returnType(), plist->returnAddress());
            Node *start = head[scopeCurrent];
            while(plist->next != nullptr)
            {
                plist = plist->next;
                head[scopeCurrent]->next = new Node(plist->returnSymID(), plist->returnKind(), plist->returnType(), plist->returnAddress());
                head[scopeCurrent] = head[scopeCurrent]->next;
            }
            head[scopeCurrent] = start;
            return true;
        }
        else
        {
            head[scopeCurrent] = nullptr;
            return true;
        }
    }

    bool scopeExit()
    {
        if(head[scopeCurrent] == nullptr)
        {
            scopeCurrent -= 1;
            return true;
        }
        Node **list = &head[scopeCurrent]; // pointer-to-pointer
        Node *current = *list;
        Node *next = nullptr;
        if (current != nullptr)
        {
            next = current->returnNext();
            delete(current);
            current = next;
        }
        *list = nullptr;
        if(head[scopeCurrent] != nullptr)
        {
            return false;
        }
        scopeCurrent -= 1;
        return true;
    }
};
#endif