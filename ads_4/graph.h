#ifndef ADS_4_GRAPH_H
#define ADS_4_GRAPH_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <random>
#include <set>
#include <stack>
#include <ctime>

int random_int(int a, int b) {
    return rand() % (b - a + 1) + a;
}

bool STOP = false;
const int STOP_CONDITION = 200;

/*********************************************************/
/// UNDIRECTED GRAPH WITH ADJACENCY LIST REPRESENTATION ///
class graph {

private:
    /// number of vertices in graph
    int V;
    /// number of edges in graph
    int E;
    /// adjacency list
    std::vector<std::vector<int>> edges;

public:

    /// constructor with declared number of vertices
    graph(int v) : V(v), E(0) {
        edges = std::vector<std::vector<int>>(V);
    }

    /// destructor
    ~graph() {
        for (auto i : edges)
            i.clear();
        edges.clear();
    }

    int get_E() {
        return E;
    }

    /// add edge from a to b and from b to a since graph is undirected
    void add_edge(int a, int b) {
        E++;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    bool check_edge(int a, int b) {
        return std::find(edges[a].begin(), edges[a].end(), b) != edges[a].end();
    }

    /// print adjacency list of graph
    void display() {
        for (int i = 0; i < V; i++) {
            std::cout << i << ": ";
            for (auto j : edges[i])
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }

    /// generate eulerian graph (all vertices' degrees are even) with given saturation ratio
    void generate_eulerian(double saturation);

    /// finds eulerian cycle if such exists
    std::list<int> *eulerian_cycle();

    /// generate connected graph with given edges saturation ratio
    void generate_connected(double saturation);

    /// finds hamiltonian cycle if such exists
    std::list<int> *hamiltonian_cycle(time_t start_t);

    // recursive methods
private:
    /// recursive (backtracking) function that find hamiltonian cycle (return true if such exists)
    bool __recursive_hamiltonian_cycle(std::list<int> *result, bool visited[], int source, time_t start_t);
};


void graph::generate_eulerian(double saturation) {
    // maximum number of edges
    int max_e = V * (V - 1) / 2 * saturation;

    if (saturation > 0.9) {
        if (V % 2 == 1) {
            for (int i = 0; i < V - 1; i++)
                for (int j = i + 1; j < V; j++)
                    add_edge(i, j);
        }
        else {
            for (int i = 0; i < V - 1; i++) {
                if (i % 2 == 1)
                    add_edge(i, i+1);
                for (int j = i + 2; j < V; j++)
                    add_edge(i, j);
            }
        }
        return;
    }


    // add path 0-1, 1-2, 2-3, ..., V-2 - V-1
    for (int i = 0; i < V - 1; i ++)
        this->add_edge(i, i+1);

    // now we have V-2 even degree nodes and 2 odd degree nodes

    std::vector<int> even;
    std::vector<int> odd;
    odd.push_back(0);
    odd.push_back(V-1);
    for (int i = 1; i < V - 1; i++)
        even.push_back(i);

    // we randomly draw even deg node a and odd deg node b
    // now if there is no edge between a and b we create such
    // now a is odd and b is even
    // so we swap them in even and odd vectors
    // continue

    while (E < max_e) {
        int i = random_int(0, V-3), j = random_int(0, 1);
        int a = even[i], b = odd[j];
        if (!this->check_edge(a, b)) {
            this->add_edge(a, b);
            even[i] = b;
            odd[j] = a;
        }
    }

    // at the end we want to make all nodes even
    // we add edge between odd nodes
    add_edge(odd[0], odd[1]);
}

std::list<int> *graph::eulerian_cycle() {
    std::vector<std::list<int>> adj(V);
    for (int i = 0; i < V; i++)
        for (auto j : edges[i])
            adj[i].push_back(j);

    std::vector<int> curr_path;
    std::list<int> *result = new std::list<int>();
    curr_path.push_back(0);

    while (!curr_path.empty()) {
        int v = curr_path.back();
        if (!adj[v].empty()) {
            int next = adj[v].back();
            adj[v].pop_back();
            adj[next].remove(v);
            curr_path.push_back(next);
        }
        else {
            result->push_back(curr_path.back());
            curr_path.pop_back();
        }
    }
    return result;
}

void graph::generate_connected(double saturation) {
    // maximum number of edges
    int max_e = V * (V - 1) / 2 * saturation;

    // generate connected graph with V-1 edges
    for (int i = 1; i < V; i++) {
        int a = random_int(0, i - 1);
        this->add_edge(a , i);
    }

    // create list with all possible edges without banned ones
    std::vector<std::pair<int, int>> edge_list;
    for (int i = 0; i < V - 1; i++) {
        for (int j = i + 1; j < V; j++) {
            std::pair<int, int> e(i, j);
            if (!check_edge(i, j))
                edge_list.push_back(e);
        }
    }

    // shuffle and draw additional edges
    random_shuffle(edge_list.begin(), edge_list.end());
    int it = 0;
    while (E < max_e) {
        this->add_edge(edge_list[it].first, edge_list[it].second);
        it++;
    }
    edge_list.clear();
}

std::list<int>* graph::hamiltonian_cycle(time_t start_t) {
    // create list to store result, boolean array to sign visited nodes
    std::list<int> *result = new std::list<int>();
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    // push 0 vertex to result
    result->push_back(0);
    visited[0] = true;

    STOP = false;

    // find hamiltonian cycle
    if (__recursive_hamiltonian_cycle(result, visited, 0, start_t)) {
        result->push_back(0);
        delete []visited;
        return result;
    }
    else {
        result->clear();
        delete []visited;
        return result;
    }
}

bool graph::__recursive_hamiltonian_cycle(std::list<int> *result, bool visited[], int source, time_t start_t) {
    if (STOP)
        return false;
    if ((double)(clock() - start_t) / CLOCKS_PER_SEC > STOP_CONDITION) {
        STOP = true;
        return false;
    }
    // if we have V nodes in result check if there is an edge between last and first node
    if (result->size() == V) {
        // if yes we found hamiltonian cycle
        if (check_edge(result->front(), result->back()))
            return true;
        else
            return false;
    }

    // for all nodes
    for (auto i : edges[source]) {
        // check if i is neighbor of source and if we already visited i
        if (!visited[i]) {
            // add i to result
            result->push_back(i);
            visited[i] = true;

            // if we can do deeper and create cycle return true
            if (__recursive_hamiltonian_cycle(result, visited, i, start_t))
                return true;
            // if we cannot create such pop last vertex from result (backtrack)
            result->pop_back();
            visited[i] = false;
        }
    }

    return false;
}

#endif //ADS_4_GRAPH_H
