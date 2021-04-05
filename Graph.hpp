#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.hpp"
#include <vector>
#include <map>
#include <set>
#include <iostream>

class Graph {
private:
    int n; // number of vertices
    int m; // number of edges
    std::set<Edge> edgeSet;
    std::set<Vertex> vertexSet;
    std::map<Vertex, std::set<Vertex> > adjacencyList;
public:
    Graph(); // default constructor
    Graph(std::istream& in); // standard constructor
    Graph(const Graph& g); // copy constructor
    friend void swap(Graph& g1, Graph& g2); // swap function
    Graph& operator = (Graph g); // copy assignment operator
    ~Graph(); // destructor
    friend std::ostream& operator << (std::ostream& out, const Graph& g); // stream insertion operator
    std::set<Edge> getEdges() const;
    std::set<Vertex> getVertices() const;
};

#endif
