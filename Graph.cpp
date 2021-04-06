#include "Graph.hpp"

// default constructor
Graph::Graph() { }

// standard constructor
Graph::Graph(std::istream& in) {
    // read number of vertices and edges
    in >> n >> m;

    // read edges
    for (int i = 0; i < m; i++) {
        Vertex v1, v2;
        in >> v1 >> v2;
        edgeSet.insert(Edge(v1, v2, i));
        vertexSet.insert(v1);
        vertexSet.insert(v2);
        adjacencyList[v1].insert(v2);
        adjacencyList[v2].insert(v1);
    }
}

// copy constructor
Graph::Graph(const Graph& g) : n(g.n), m(g.m), edgeSet(g.edgeSet),
    vertexSet(g.vertexSet), adjacencyList(g.adjacencyList) { }

// swap function
void swap(Graph& g1, Graph& g2) {
    std::swap(g1.n, g2.n);
    std::swap(g1.m, g2.m);
    std::swap(g1.edgeSet, g2.edgeSet);
    std::swap(g1.vertexSet, g2.vertexSet);
    std::swap(g1.adjacencyList, g2.adjacencyList);
}

// copy assignment operator
Graph& Graph::operator = (Graph g) {
    swap(*this, g);
    return *this;
}

// destructor
Graph::~Graph() { }

// stream insertion operator
std::ostream& operator << (std::ostream& out, const Graph& g) {
    out << g.n << " " << g.m << std::endl;
    for (auto e : g.edgeSet) {
        out << e << std::endl;
    }
    return out;
}

std::unordered_set<Edge> Graph::getEdges() const {
    return edgeSet;
}

std::unordered_set<Vertex> Graph::getVertices() const {
    return vertexSet;
}
