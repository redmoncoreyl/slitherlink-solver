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
typedef std::pair<MateFunction, CountFunction> NodeBody;

enum MateType {
    OutOfDomain = -2,
    DegreeTwo = -1
};

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
    std::vector<std::vector<int> > hintEdgeDomIntMag;
    std::vector<boost::unordered_map<NodeBody, Zdd<Edge>*> > existingNodes;
    boost::unordered_map<Zdd<Edge>*, MateFunction> nodesMateFunction;
    boost::unordered_map<Zdd<Edge>*, CountFunction> nodesCountFunction;
    boost::unordered_map<Zdd<Edge>*, int> nodesLayer;

    void createRoot();
    void createTerminals();
    void determineLayerDomains();
    Zdd<Edge>* getNode(const int i, const std::pair<MateFunction, CountFunction>& p);
    bool hasFixedEnd(const MateFunction& mate, const int i);
    bool isIncompatibleCount(const CountFunction& count, const int i);
    MateFunction induceDomain(const MateFunction& m, const int i);
    bool doesFormCycle(const MateFunction& m, const Edge& e);
    CountFunction countUpdate(const CountFunction& count, const int i);
    bool doesMatchHints(const CountFunction& count);
    bool doesDeclineEdge(const MateFunction& m, const int i);
public:
    Slitherlink(std::istream& in); // standard constructor
    Slitherlink(const Slitherlink& s); // copy constructor
    friend void swap(Slitherlink& s1, Slitherlink& s2); // swap function
    Slitherlink& operator = (Slitherlink s); // copy assignment operator
    ~Slitherlink(); // destructor
    friend std::ostream& operator << (std::ostream& out, const Slitherlink& s); // stream insertion operator

    Family<Edge> generateFamily();
};

#endif
