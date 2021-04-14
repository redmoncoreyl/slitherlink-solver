#ifndef SLITHERLINK_H
#define SLITHERLINK_H

#include "Edge.hpp"
#include "Zdd.hpp"
#include <boost/unordered_set.hpp>
#include <boost/unordered_map.hpp>
#include <vector>
#include <iostream>

typedef std::vector<int> MateFunction;
typedef std::vector<int> CountFunction;

class Slitherlink {
private:
    int n; // number of vertices
    int m; // number of edges
    int k; // number of hints
    std::vector<Edge> edgeList;
    std::vector<boost::unordered_set<int> > hintDomain;
    CountFunction hints;
    Zdd<Edge>* diagram;
    Zdd<Edge>* zeroTerminal;
    Zdd<Edge>* oneTerminal;
    std::vector<boost::unordered_set<Vertex> > layerDomain;
    std::vector<boost::unordered_map<std::pair<MateFunction, CountFunction>, Zdd<Edge>*> > existingNodes;
    boost::unordered_map<Zdd<Edge>*, MateFunction> nodesMateFunction;
    boost::unordered_map<Zdd<Edge>*, CountFunction> nodesCountFunction;
    boost::unordered_map<Zdd<Edge>*, int> nodesLayer;
public:
    Slitherlink(std::istream& in); // standard constructor
    Slitherlink(const Slitherlink& s); // copy constructor
    friend void swap(Slitherlink& s1, Slitherlink& s2); // swap function
    Slitherlink& operator = (Slitherlink s); // copy assignment operator
    ~Slitherlink(); // destructor
    friend std::ostream& operator << (std::ostream& out, const Slitherlink& s); // stream insertion operator
};

#endif
