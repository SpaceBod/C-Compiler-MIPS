#ifndef symtab_hpp
#define symtab_hpp
#include <vector>
#include <cassert>
#include <map>

#include "ast_nodes.hpp"
#include "ast_stackptr.hpp"

const int MAX = 100;


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
    bool insert(std::string symID, std::string symKind, std::string symType, std::string symAddr, int symLen = 1)
    {        
        if(head[scopeCurrent] != nullptr)
        {
            Node *start = head[scopeCurrent];
            // Finds free location
            while(start->getNext() != nullptr)
            {
                start = start->getNext();
            }
            // Inserts new symbol
            start->setNext(new Node(symID, symKind, symType, symAddr, symLen));
            return true;
        }
        else
        {
            // Inserts new symbol if first location is free
            head[scopeCurrent] = new Node(symID, symKind, symType, symAddr, symLen);
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
            if(start->getSymID() == symID)
            {
                return start->getLen();
            }
            else
            {
                start = start->getNext();
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
            if(start->getSymID() == symID)
            {
                return start->getAddress();
            }
            else
            {
                start = start->getNext();
            }
        }
        return ("Symbol ID: " + symID + " not found");
    }

    // Looks up the symID and return the type
    std::string getType(std::string symID)
    {
        Node *start = head[scopeCurrent];
        while(start != nullptr)
        {
            if(start->getSymID() == symID)
            {
                return start->getType();
            }
            else
            {
                start = start->getNext();
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
            if(start->getKind() == symKind)
            {
                vectorSymIDs.push_back(start->getSymID());
            }
            start = start->getNext();
        }
        return vectorSymIDs;
    }

    // Looks up the symID and return the kind
    std::string getKind(std::string symID)
    {
        Node *start = head[scopeCurrent];
        while(start != nullptr)
        {
            if(start->getSymID() == symID)
            {
                return start->getKind();
            }
            else
            {
                start = start->getNext();
            }
        }
        return ("Symbol ID: " + symID + " not found");
    }

    // Edit an existing symID's values
    bool edit(std::string symID, std::string symKind, std::string symType, std::string symAddr, int symLen = 1)
    {
        if(head[scopeCurrent] != nullptr)
        {
            Node *start = head[scopeCurrent];
            while(start != nullptr)
            {
                // if symID matches -> edit properties
                if(start->getSymID() == symID)
                {
                    start->setType(symType);
                    start->setKind(symKind);
                    start->setAddress(symAddr);
                    start->setLen(symLen);
                    return true;
                }
                start = start->getNext();
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
            head[scopeCurrent] = new Node(plist->getSymID(), plist->getKind(), plist->getType(), plist->getAddress());
            Node *start = head[scopeCurrent];
            while(plist->next != nullptr)
            {
                plist = plist->next;
                head[scopeCurrent]->next = new Node(plist->getSymID(), plist->getKind(), plist->getType(), plist->getAddress());
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
            next = current->getNext();
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