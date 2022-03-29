#ifndef nodes_hpp
#define nodes_hpp

#include <cassert>
#include <string>

#include "ast_symtab.hpp"

class Node
{
private:
    friend class SymTab;
    int len;
    std::string symID, kind, type, address;
    Node *next;

public:
    Node()
    {
        next = nullptr;
    }

    Node(std::string newSymID, std::string newKind, std::string newType, std::string newAddress, int newLen = 1)
    {
        symID = newSymID;
        kind = newKind;
        type = newType;
        address = newAddress;
        len = newLen;
        next = nullptr;
    }

    ~Node()
    {
        delete next;
    }

    std::string returnSymID()
    {
        return symID;
    }

    std::string returnKind()
    {
        return kind;
    }
    void setKind(std::string _kind)
    {
        kind = _kind;
    }

    std::string returnType()
    {
        return type;
    }

    void setType(std::string _type)
    {
        type = _type;
    }

    std::string returnAddress()
    {
        return address;
    }
    void setAddress(std::string _address)
    {
        address = _address;
    }

    int returnLen()
    {
        return len;
    }
    void setLen(int _len)
    {
        len = _len;
    }

    Node *returnNext()
    {
        return next;
    }
    void setNext(Node *element)
    {
        next = element;
    }
};
#endif