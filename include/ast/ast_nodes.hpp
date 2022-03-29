#ifndef ast_nodes_hpp
#define ast_nodes_hpp

#include <cassert>
#include <string>

class Node
{
private:
    std::string name, kind, type, address;
    Node *next;
    friend class SymTabADT;

public:
    Node()
    {
        next = nullptr;
    }

    Node(std::string _type, std::string _format, std::string _name, std::string _address)
    {
        type = _type;
        kind = _format;
        name = _name;
        address = _address;
        next = nullptr;
    }

    ~Node()
    {
        delete next;
    }

    std::string returnType()
    {
        return type;
    }

    void setType(std::string _type)
    {
        type = _type;
    }

    std::string returnKind()
    {
        return kind;
    }

    void setFormat(std::string _format)
    {
        kind = _format;
    }

    std::string getName()
    {
        return name;
    }

    std::string getAddress()
    {
        return address;
    }

    void setAddress(std::string _address)
    {
        address = _address;
    }

    Node *getNext()
    {
        return next;
    }

    void setNext(Node *element)
    {
        next = element;
    }
};

#endif