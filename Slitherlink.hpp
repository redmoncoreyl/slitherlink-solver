#ifndef SLITHERLINK_H
#define SLITHERLINK_H

#include "Edge.hpp"
#include "Zdd.hpp"
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <vector>
#include <iostream>

typedef std::map<Vertex, Vertex> MateFunction;
typedef std::map<std::unordered_set<Edge>, int> CountFunction;

class Slitherlink {
private:
    int n; // number of vertices
    int m; // number of edges
    int k; // number of hints
    std::unordered_set<Vertex> vertexSet;
    std::vector<Edge> edgeList;
    std::map<std::unordered_set<Edge>, int> hints;
    Zdd<Edge>* diagram;
    Zdd<Edge>* zeroTerminal;
    Zdd<Edge>* oneTerminal;
    std::vector<std::unordered_set<Vertex> > domain;
    std::vector<std::unordered_map<std::pair<MateFunction, CountFunction>, Zdd<Edge>*> > existingNodes;
    std::unordered_map<Zdd<Edge>*, MateFunction> nodesMateFunction;
    std::unordered_map<Zdd<Edge>*, CountFunction> nodesCountFunction;
    std::unordered_map<Zdd<Edge>*, int> nodesLayer;
public:
    Slitherlink(); // default constructor
    Slitherlink(std::istream& in); // standard constructor
    Slitherlink(const Slitherlink& s); // copy constructor
    friend void swap(Slitherlink& s1, Slitherlink& s2); // swap function
    Slitherlink& operator = (Slitherlink s); // copy assignment operator
    ~Slitherlink(); // destructor
    friend std::ostream& operator << (std::ostream& out, const Slitherlink& s); // stream insertion operator
};

namespace std {
    template <class T1, class T2>
    struct hash<std::pair<T1, T2> > {
        std::size_t operator()(const std::pair<T1, T2>& p) const {
            return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
        }
    };
}

#endif
