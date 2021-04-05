#include "Edge.hpp"

// default constructor
Edge::Edge() : v_a(-1), v_b(-1) { }

// standard constructor
Edge::Edge(Vertex a, Vertex b) : v_a(a), v_b(b), id(0) { }

// standard constructor
Edge::Edge(Vertex a, Vertex b, int i) : v_a(a), v_b(b), id(i) { }

// copy constructor
Edge::Edge(const Edge& e) : v_a(e.v_a), v_b(e.v_b), id(e.id) { }

// swap function
void swap(Edge& e1, Edge& e2) {
    std::swap(e1.v_a, e2.v_a);
    std::swap(e1.v_b, e2.v_b);
    std::swap(e1.id, e2.id);
}

// copy assignment operator
Edge& Edge::operator = (Edge e) {
    swap(*this, e);
    return *this;
}

// destructor
Edge::~Edge() { }

// stream insertion operator
std::ostream& operator << (std::ostream& out, const Edge& e) {
    out << e.v_a << " " << e.v_b;
    return out;
}

// compare operator
bool operator < (const Edge& lhs, const Edge& rhs) {
    return lhs.id < rhs.id;
}

// compare operator
bool operator > (const Edge& lhs, const Edge& rhs) {
    return lhs.id > rhs.id;
}

// compare operator
bool operator <= (const Edge& lhs, const Edge& rhs) {
    return lhs.id <= rhs.id;
}

// compare operator
bool operator >= (const Edge& lhs, const Edge& rhs) {
    return lhs.id >= rhs.id;
}

// compare operator
bool operator == (const Edge& lhs, const Edge& rhs) {
    return lhs.id == rhs.id;
}

// tests if edge connects to given vertex
bool Edge::isIncident(Vertex a) const {
    return (v_a == a || v_b == a);
}

Vertex Edge::getA() const {
    return v_a;
}

Vertex Edge::getB() const {
    return v_b;
}
