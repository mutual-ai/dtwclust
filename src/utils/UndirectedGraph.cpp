#include "UndirectedGraph.h"

#include <algorithm> // std::fill

namespace dtwclust {

// constructor
UndirectedGraph::UndirectedGraph(const int max_size)
    : visited_(max_size, false)
    , max_size_(max_size)
    , connected_(false)
{ }

// check if two indices are connected by an edge
bool UndirectedGraph::areNeighbors(const int i, const int j) const {
    auto ii = vertices_.find(i);
    if (ii == vertices_.end())
        return false;

    auto jj = vertices_.find(j);
    if (jj == vertices_.end())
        return false;

    if (ii->second->neighbors.find(jj->second) == ii->second->neighbors.end())
        return false;
    return true;
}

// connect two indices, creating them if they didn't exist
void UndirectedGraph::linkVertices(const int i, const int j, const int link_type) {
    std::shared_ptr<Vertex> i_vertex, j_vertex;

    auto ii = vertices_.find(i);
    if (ii == vertices_.end()) {
        i_vertex = std::make_shared<Vertex>(i, link_type);
        vertices_.insert({i, i_vertex});
    }
    else
        i_vertex = ii->second;

    auto jj = vertices_.find(j);
    if (jj == vertices_.end()) {
        j_vertex = std::make_shared<Vertex>(j, link_type);
        vertices_.insert({j, j_vertex});
    }
    else
        j_vertex = jj->second;

    i_vertex->neighbors.insert(j_vertex);
    j_vertex->neighbors.insert(i_vertex);
}

// is graph conected? https://en.wikipedia.org/wiki/Connectivity_(graph_theory)
bool UndirectedGraph::isConnected() {
    if (connected_) return true;

    int current_size = vertices_.size();
    if (current_size == 0 || current_size < max_size_)
        return false;

    std::fill(visited_.begin(), visited_.end(), false);
    this->dfs(vertices_.begin()->second);
    // if all vertices were visited, the graph is connected
    // see https://www.quora.com/How-do-I-find-if-undirected-graph-is-connected-or-not-using-DFS
    for (const bool flag : visited_) {
        if (!flag) return false;
    }
    connected_ = true;
    return true;
}

// depth-first search
void UndirectedGraph::dfs(const std::shared_ptr<Vertex>& vertex) {
    // ids start with 1 due to R
    if (visited_[vertex->id - 1])
        return;
    visited_[vertex->id- 1] = true;
    for (auto neighbor : vertex->neighbors) {
        if (!(visited_[neighbor->id - 1]))
            dfs(neighbor);
    }
}

} // namespace dtwclust