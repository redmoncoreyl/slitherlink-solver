#ifndef ZDD_H
#define ZDD_H

#include <iostream>
#include <unordered_set>

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
    std::unordered_set<std::unordered_set<T> > getFamily(); // getter

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

// default constructor
template <typename T>
Zdd<T>::Zdd() : zero_child(NULL), one_child(NULL), type(NodeType::normal) { }

// standard constructor
template <typename T>
Zdd<T>::Zdd(T e) : elt(e), zero_child(NULL), one_child(NULL), type(NodeType::normal) { }

// standard constructor
template <typename T>
Zdd<T>::Zdd(NodeType t) : zero_child(NULL), one_child(NULL), type(t) { }

// standard constructor
template <typename T>
Zdd<T>::Zdd(T e, Zdd<T>* z, Zdd<T>* o) : elt(e),
    zero_child(z), one_child(o), type(NodeType::normal) { }

// copy constructor
template <typename T>
Zdd<T>::Zdd(const Zdd<T>& z) : elt(z.elt),
    zero_child(z.zero_child ? new Zdd<T>(*z.zero_child) : NULL),
    one_child(z.one_child ? new Zdd<T>(*z.one_child) : NULL) { }

// copy assignment constructor
template <typename T>
Zdd<T>& Zdd<T>::operator = (Zdd<T> z) {
    swap(*this, z);
    return *this;
}

// destructor
template <typename T>
Zdd<T>::~Zdd() {
    delete zero_child;
    delete one_child;
}

// setter
template <typename T>
void Zdd<T>::setZeroChild(Zdd<T>* z) {
    zero_child = z;
}

// setter
template <typename T>
void Zdd<T>::setOneChild(Zdd<T>* o) {
    one_child = o;
}

// getter
template <typename T>
Zdd<T>* Zdd<T>::getZeroChild() {
    return zero_child;
}

// getter
template <typename T>
Zdd<T>* Zdd<T>::getOneChild() {
    return one_child;
}

// getter
template <typename T>
NodeType Zdd<T>::getType() {
    return type;
}

// getter
template <typename T>
std::unordered_set<std::unordered_set<T> > Zdd<T>::getFamily() {
    // base cases:
    //   zero terminal nodes don't contribute anything (the family is empty)
    //   one terminal nodes contribute a family containing 1 empty set
    if (type == NodeType::zero_terminal) {
        return std::unordered_set<std::unordered_set<T> >({});
    }
    if (type == NodeType::one_terminal) {
        return std::unordered_set<std::unordered_set<T> >({{}});
    }
    // if node is non-terminal:
    //   get the family of the zero_child and the one_child
    //     (treat NULL children as  zero terminals)
    //   add this node's element to the sets in the one child's family
    //   return the union of the two families

    std::unordered_set<std::unordered_set<T> > zeroFamily = zero_child ? zero_child->getFamily() : std::unordered_set<std::unordered_set<T> >({});
    std::unordered_set<std::unordered_set<T> > oneFamily = one_child ? one_child->getFamily() : std::unordered_set<std::unordered_set<T> >({});
    std::unordered_set<std::unordered_set<T> > thisFamily;

    for (auto s : oneFamily) {
        s.insert(elt);
        thisFamily.insert(s);
    }
    for (auto s : zeroFamily) {
        thisFamily.insert(s);
    }

    return thisFamily;
}

#endif
