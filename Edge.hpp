#ifndef EDGE_H
#define EDGE_H

#include <iostream>

typedef int Vertex;

class Edge {
private:
    Vertex v_a;
    Vertex v_b;
    int id;
public:
    Edge(); // default constructor
    Edge(Vertex a, Vertex b); // standard constructor
    Edge(Vertex a, Vertex b, int i); // standard constructor
    Edge(const Edge& e); // copy constructor
    friend void swap(Edge& e1, Edge& e2); // swap function
    Edge& operator = (Edge e); // copy assignment operator
    ~Edge(); // destructor
    friend std::ostream& operator << (std::ostream& out, const Edge& e); // stream insertion operator
    friend bool operator < (const Edge& lhs, const Edge& rhs); // compare operator
    friend bool operator > (const Edge& lhs, const Edge& rhs); // compare operator
    friend bool operator <= (const Edge& lhs, const Edge& rhs); // compare operator
    friend bool operator >= (const Edge& lhs, const Edge& rhs); // compare operator
    friend bool operator == (const Edge& lhs, const Edge& rhs); // compare operator
    bool isIncident(Vertex a) const;
    Vertex getA() const;
    Vertex getB() const;
    int getId() const;
};

namespace std {
    template <>
    struct hash<Edge> {
        size_t operator()(const Edge& e) const {
            return hash<int>()(e.getId());
        }
    };
}

#endif
