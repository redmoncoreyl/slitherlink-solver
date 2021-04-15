#include "Slitherlink.hpp"
#include <algorithm>
#include <queue>

// standard constructor
Slitherlink::Slitherlink(std::istream& in) : diagram(NULL), zeroTerminal(NULL), oneTerminal(NULL) {
    // read number of vertices, edges, and hints
    in >> n >> m >> k;

    // reserve vectors
    edgeList.reserve(m);
    hintDomain.reserve(k);
    hints.reserve(k);
    layerDomain.reserve(m+1);
    existingNodes.reserve(m);
    for (int i = 0; i < m; i++) {
        existingNodes.push_back(boost::unordered_map<NodeBody, Zdd<Edge>* >());
    }
    hintEdgeDomIntMag.reserve(k);
    for (int i = 0; i < k; i++) {
        hintEdgeDomIntMag.push_back(std::vector<int>(m+1, 0));
    }

    // read edges
    for (int i = 0; i < m; i++) {
        Vertex v1, v2;
        in >> v1 >> v2;
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
            for (int l = 0; l < edge_index + 1; l++) {
                hintEdgeDomIntMag[i][l]++;
            }
        }
        int hint_value;
        in >> hint_value;
        hintDomain.push_back(index_set);
        hints.push_back(hint_value);
    }

    createRoot();
    createTerminals();
    determineLayerDomains();
}

// copy constructor
Slitherlink::Slitherlink(const Slitherlink& s)
    : n(s.n),
      m(s.m),
      k(s.k),
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

void Slitherlink::createRoot() {
    // the root node doesn't have any edges added to the set
    // therefore, the mate function is the identity, where every
    // node is its own mate
    MateFunction mateIdentity;
    mateIdentity.reserve(n);
    for (int i = 0; i < n; i++) {
        mateIdentity.push_back(i);
    }
    // the count function identity is all zeros becuase none of the
    // edge sets in the domain have any edges included yet
    CountFunction countIdentity(k, 0);
    diagram = getNode(0, std::make_pair(mateIdentity, countIdentity));
}

void Slitherlink::createTerminals() {
    zeroTerminal = new Zdd<Edge>(NodeType::zero_terminal);
    oneTerminal = new Zdd<Edge>(NodeType::one_terminal);
}

void Slitherlink::determineLayerDomains() {
    // to create the domains, add the edges in reverse order
    layerDomain.push_back(boost::unordered_set<Vertex>());
    for (int i = 0; i < m; i++) {
        layerDomain.push_back(layerDomain[i]);
        layerDomain[i+1].insert(edgeList[i].getA());
        layerDomain[i+1].insert(edgeList[i].getB());
    }
    std::reverse(layerDomain.begin(), layerDomain.end());
}

Zdd<Edge>* Slitherlink::getNode(const int i, const NodeBody& p) {
    // "It is conveniently assumed that GN(|E| + 1, m) gives the 1 terminal"
    if (i >= m) return oneTerminal;
    // if the pair of mate and count functions already exists, return that node
    if (existingNodes[i].count(p)) return existingNodes[i][p];
    // otherwise, a new node is required. when creating a new node:
    //   allocate the node and add it to the existing nodes
    //   add the node's mate function, count function, and layer
    Zdd<Edge>* n = new Zdd<Edge>(edgeList[i]);
    existingNodes[i][p] = n;
    nodesMateFunction[n] = p.first;
    nodesCountFunction[n] = p.second;
    nodesLayer[n] = i;
    return n;
}

bool Slitherlink::hasFixedEnd(const MateFunction& mate, const int i) {
    Vertex a = edgeList[i].getA();
    Vertex mateA = mate[a];
    if (!layerDomain[i+1].count(a) && mateA != MateType::DegreeTwo && mateA != a) {
        return true;
    }
    Vertex b = edgeList[i].getB();
    Vertex mateB = mate[b];
    if (!layerDomain[i+1].count(b) && mateB != MateType::DegreeTwo && mateB != b) {
        return true;
    }
    return false;
}

bool Slitherlink::isIncompatibleCount(const CountFunction& count, const int i) {
    for (int j = 0; j < k; j++) {
        if (count[j] > hints[j]) return true;
        if (count[j] + hintEdgeDomIntMag[j][i+1] < hints[j]) return true;
    }
    return false;
}

MateFunction Slitherlink::induceDomain(const MateFunction& m, const int i) {
    MateFunction subMate = m;
    for (int j = 0; j < n; j++) {
        if (!layerDomain[i].count(j)) {
            subMate[j] = MateType::OutOfDomain;
        }
    }
    return subMate;
}

Family<Edge> Slitherlink::generateFamily() {
    // this set allows us to skip nodes that have already spawned children
    std::unordered_set<Zdd<Edge>* > visited;
    // ... or don't have chilren such as terminals
    visited.insert(zeroTerminal);
    visited.insert(oneTerminal);
    // this is the queue of nodes that still require processing
    std::queue<Zdd<Edge>* > toVisit;
    toVisit.push(diagram);

    // to process the queue:
    //   create the children of node at front of queue
    //   add children to back of queue (but not terminals)
    //   pop queue
    while (!toVisit.empty()) {
        Zdd<Edge>* n = toVisit.front();

        if (visited.count(n)) {
            toVisit.pop();
            continue;
        }

        MateFunction mate = nodesMateFunction[n];
        CountFunction count = nodesCountFunction[n];
        int i = nodesLayer[n];
        Edge e = edgeList[i];
    }
}
