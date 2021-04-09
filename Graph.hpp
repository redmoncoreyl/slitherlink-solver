#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.hpp"
#include <boost/unordered_map>
#include <boost/unordered_set>
#include <iostream>

class Graph {
private:
    int n; // number of vertices
    int m; // number of edges
    boost::unordered_set<Edge> edgeSet;
    boost::unordered_set<Vertex> vertexSet;
    boost::unordered_map<Vertex, boost::unordered_set<Vertex> > adjacencyList;
public:
    Graph(); // default constructor
    Graph(std::istream& in); // standard constructor
    Graph(const Graph& g); // copy constructor
    friend void swap(Graph& g1, Graph& g2); // swap function
    Graph& operator = (Graph g); // copy assignment operator
    ~Graph(); // destructor
    friend std::ostream& operator << (std::ostream& out, const Graph& g); // stream insertion operator
    boost::unordered_set<Edge> getEdges() const;
    boost::unordered_set<Vertex> getVertices() const;
};

#endif
