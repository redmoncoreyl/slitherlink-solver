#ifndef SLITHERLINK_H
#define SLITHERLINK_H

#include "Edge.hpp"
#include "Zdd.hpp"
#include <set>
#include <map>
#include <vector>
#include <iostream>

typedef std::map<Vertex, Vertex> MateFunction;
typedef std::map<std::set<int>, int> CountFunction;

class Slitherlink {
private:
    int n; // number of vertices
    int m; // number of edges
    int k; // number of hints
    std::set<Vertex> vertexSet;
    std::vector<Edge> edgeList;
    CountFunction hints;
    Zdd<Edge>* diagram;
    Zdd<Edge>* zeroTerminal;
    Zdd<Edge>* oneTerminal;
    std::vector<std::set<Vertex> > domain;
    std::vector<std::map<std::pair<MateFunction, CountFunction>, Zdd<Edge>*> > existingNodes;
    std::map<Zdd<Edge>*, MateFunction> nodesMateFunction;
    std::map<Zdd<Edge>*, CountFunction> nodesCountFunction;
    std::map<Zdd<Edge>*, int> nodesLayer;
public:
    Slitherlink(); // default constructor
    Slitherlink(std::istream& in); // standard constructor
    Slitherlink(const Slitherlink& s); // copy constructor
    friend void swap(Slitherlink& s1, Slitherlink& s2); // swap function
    Slitherlink& operator = (Slitherlink s); // copy assignment operator
    ~Slitherlink(); // destructor
    friend std::ostream& operator << (std::ostream& out, const Slitherlink& s); // stream insertion operator
};

#endif
