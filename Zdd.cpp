#include "Zdd.hpp"
#include "Edge.hpp"
#include <iostream>

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
std::set<std::set<T> > Zdd<T>::getFamily() {
    // base cases:
    //   zero terminal nodes don't contribute anything (the family is empty)
    //   one terminal nodes contribute a family containing 1 empty set
    if (type == NodeType::zero_terminal) {
        return std::set<std::set<T> >({});
    }
    if (type == NodeType::one_terminal) {
        return std::set<std::set<T> >({{}});
    }
    // if node is non-terminal:
    //   get the family of the zero_child and the one_child
    //     (treat NULL children as  zero terminals)
    //   add this node's element to the sets in the one child's family
    //   return the union of the two families

    std::set<std::set<T> > zeroFamily = zero_child ? zero_child->getFamily() : std::set<std::set<T> >({});
    std::set<std::set<T> > oneFamily = one_child ? one_child->getFamily() : std::set<std::set<T> >({});
    std::set<std::set<T> > thisFamily;

    for (auto s : oneFamily) {
        s.insert(elt);
        thisFamily.insert(s);
    }
    for (auto s : zeroFamily) {
        thisFamily.insert(s);
    }

    return thisFamily;
}

template Zdd<int>::Zdd();
template Zdd<int>::Zdd(int e);
template Zdd<int>::Zdd(NodeType t);
template Zdd<int>::Zdd(int e, Zdd<int>* z, Zdd<int>* o);
template Zdd<int>::Zdd(const Zdd<int>& z);
template Zdd<int>& Zdd<int>::operator = (Zdd<int> z);
template Zdd<int>::~Zdd();
template void Zdd<int>::setZeroChild(Zdd<int>* z);
template void Zdd<int>::setOneChild(Zdd<int>* o);
template Zdd<int>* Zdd<int>::getZeroChild();
template Zdd<int>* Zdd<int>::getOneChild();
template NodeType Zdd<int>::getType();
template std::set<std::set<int> > Zdd<int>::getFamily();

template Zdd<Edge>::Zdd();
template Zdd<Edge>::Zdd(Edge e);
template Zdd<Edge>::Zdd(NodeType t);
template Zdd<Edge>::Zdd(Edge e, Zdd<Edge>* z, Zdd<Edge>* o);
template Zdd<Edge>::Zdd(const Zdd<Edge>& z);
template Zdd<Edge>& Zdd<Edge>::operator = (Zdd<Edge> z);
template Zdd<Edge>::~Zdd();
template void Zdd<Edge>::setZeroChild(Zdd<Edge>* z);
template void Zdd<Edge>::setOneChild(Zdd<Edge>* o);
template Zdd<Edge>* Zdd<Edge>::getZeroChild();
template Zdd<Edge>* Zdd<Edge>::getOneChild();
template NodeType Zdd<Edge>::getType();
template std::set<std::set<Edge> > Zdd<Edge>::getFamily();
