#include "Slitherlink.hpp"

// standard constructor
Slitherlink::Slitherlink(std::istream& in) {
    // read number of vertices, edges, and hints
    in >> n >> m >> k;

    // read edges
    for (int i = 0; i < m; i++) {
        Vertex v1, v2;
        in >> v1 >> v2;
        vertexSet.insert(v1);
        vertexSet.insert(v2);
        edgeList.push_back(Edge(v1, v2, i));
    }

    // read hints
    for (int i = 0; i < k; i++) {
        int e; // number of edges in the current hint
        in >> e;
        boost::unordered_set<int> index_set;
        for (int j = 0; j < e; j++) {
            int edge_index;
            in >> edge_index;
            index_set.insert(edge_index);
        }
        int hint_value;
        in >> hint_value;
        hintDomain.push_back(index_set);
        hints.push_back(hint_value);
    }
}

// copy constructor
Slitherlink::Slitherlink(const Slitherlink& s)
    : n(s.n),
      m(s.m),
      k(s.k),
      vertexSet(s.vertexSet),
      edgeList(s.edgeList),
      hintDomain(s.hintDomain),
      hints(s.hints),
      diagram(new Zdd<Edge>(*s.diagram)),
      zeroTerminal(new Zdd<Edge>(*s.zeroTerminal)),
      oneTerminal(new Zdd<Edge>(*s.oneTerminal)),
      layerDomain(s.layerDomain),
      existingNodes(s.existingNodes),
      nodesMateFunction(s.nodesMateFunction),
      nodesCountFunction(s.nodesCountFunction),
      nodesLayer(s.nodesLayer) {}

// swap function
void swap(Slitherlink& s1, Slitherlink& s2) {
    std::swap(s1.n, s2.n);
    std::swap(s1.m, s2.m);
    std::swap(s1.k, s2.k);
    std::swap(s1.vertexSet, s2.vertexSet);
    std::swap(s1.edgeList, s2.edgeList);
    std::swap(s1.hintDomain, s2.hintDomain);
    std::swap(s1.hints, s2.hints);
    std::swap(s1.diagram, s2.diagram);
    std::swap(s1.zeroTerminal, s2.zeroTerminal);
    std::swap(s1.oneTerminal, s2.oneTerminal);
    std::swap(s1.layerDomain, s2.layerDomain);
    std::swap(s1.existingNodes, s2.existingNodes);
    std::swap(s1.nodesMateFunction, s2.nodesMateFunction);
    std::swap(s1.nodesCountFunction, s2.nodesCountFunction);
    std::swap(s1.nodesLayer, s2.nodesLayer);
}

// copy assignment operator
Slitherlink& Slitherlink::operator = (Slitherlink s) {
    std::swap(*this, s);
    return *this;
}

// destructor
Slitherlink::~Slitherlink() {
    delete diagram;
    delete zeroTerminal;
    delete oneTerminal;
}

// stream insertion operator
std::ostream& operator << (std::ostream& out, const Slitherlink& s) {
    out << s.n << " " << s.m << " " << s.k << std::endl;
    for (auto e : s.edgeList) {
        out << e << std::endl;
    }
    for (int hd  = 0; hd < s.hintDomain.size(); hd++) {
        for (auto i : s.hintDomain[hd]) {
            out << i << " ";
        }
        out << s.hints[hd] << std::endl;
    }
    return out;
}
