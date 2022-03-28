#ifndef nodes_hpp
#define nodes_hpp

#include <cassert>
#include <vector>
#include <string>

#include "ast_symtab.hpp"
#include "ast_stackptr.hpp"

class Node {
private:
    std::string type, format ,name, address;
    int length;
    Node* next;
    friend class SymTab;
public:
    Node() {
        next = nullptr;
    }

    Node(std::string _type, std::string _format, std::string _name, std::string _address, int _length = 1) {
        type = _type;
        format = _format;
        name = _name;
        address = _address;
        length = _length;
        next = nullptr;
    }

    ~Node() {
        delete next;
    }

    void print() {
        std::cout << "Type: " << type << std::endl;
        std::cout << "Format: " << format << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << '\n';
    }

    std::string getType() {
        return type;
    }

    void setType(std::string _type) {
        type = _type;
    }

    void setLength(int _length) {
        length = _length;
    }

    int getLength() {
        return length;
    }

    std::string getFormat() {
        return format;
    }

    void setFormat(std::string _format) {
        format = _format;
    }

    std::string getName() {
        return name;
    }

    std::string getAddress() {
        return address;
    }

    void setAddress(std::string _address) {
        address = _address;
    }

    Node *getNext() {
        return next;
    }

    void setNext(Node *element) {
        next = element;
    }
};
#endif