#include "GraphMatch.h"

OutputData GraphMatch(const GraphData& graph) {
    OutputData output;
    output.matched_subgraph = "Matched: " + graph.nodes + " - " + graph.edges;
    return output;
}
