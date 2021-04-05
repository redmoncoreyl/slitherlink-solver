#ifndef ZDD_H
#define ZDD_H

#include <iostream>
#include <set>

enum NodeType {
    normal = 0,
    zero_terminal = 1,
    one_terminal = 2
};

template <typename T>
class Zdd {
private:
    T elt;
    Zdd<T>* zero_child;
    Zdd<T>* one_child;
    NodeType type;
public:
    Zdd(); // default constructor
    Zdd(T e); // standard constructor
    Zdd(NodeType t); // standard constructor
    Zdd(T e, Zdd<T>* z, Zdd<T>* o); // standard constructor
    Zdd(const Zdd<T>& z); // copy constructor
    Zdd<T>& operator = (Zdd<T> z); // copy assignment operator
    ~Zdd(); // destructor
    void setZeroChild(Zdd<T>* z); // setter
    void setOneChild(Zdd<T>* o); // setter
    Zdd<T>* getZeroChild(); // getter
    Zdd<T>* getOneChild(); // getter
    NodeType getType(); // getter
    std::set<std::set<T> > getFamily(); // getter

    friend std::ostream& operator << (std::ostream& out, const Zdd& z) { // stream insertion operator
        out << z.elt;
        return out;
    }

    friend void swap(Zdd<T>& z1, Zdd<T>& z2) { // swap function
        std::swap(z1.elt, z2.elt);
        std::swap(z1.zero_child, z2.zero_child);
        std::swap(z1.one_child, z2.one_child);
        std::swap(z1.type, z2.type);
    }
};

#endif
