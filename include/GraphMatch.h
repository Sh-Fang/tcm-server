#ifndef GRAPH_MATCH_H
#define GRAPH_MATCH_H

#include <string>

struct GraphData {
    std::string nodes;
    std::string edges;
};

struct OutputData {
    std::string matched_subgraph;
};

OutputData GraphMatch(const GraphData& graph);

#endif
