#ifndef GRAPHS_HPP_INCLUDED
#define GRAPHS_HPP_INCLUDED

#include<cmath>
#include<algorithm>
#include<vector>
#include<fstream>
#include<list>

int random(int a, int b) {
    return rand() % (b - a + 1) + a;
}

/*** START OF UNDIRECTED GRAPHS FOR TASK 1 ***/

/****************************/
/*** GRAPH ABSTRACT CLASS ***/
/****************************/
class IGraph {

protected:
    int V, E;
    std::vector< std::vector<int> > edges;

public:
    IGraph(int V) : V(V), E(0) {}
    ~IGraph() {}
    virtual void add_edge(int a, int b)=0;
    virtual bool check_edge(int a, int b)=0;

    /*** return number of edges ***/
    int get_edges () {
        return this->E;
    }

    /*** read graph (edge list!) from file ***/
    void load(const std::string FILE_PATH) {
        std::ifstream file;
        file.open(FILE_PATH);
        if (!file.is_open()) {
            throw "Unable to open the file!";
            return;
        }
        int a, b;
        file >> a >> b;
        while (!file.eof()) {
            this->add_edge(a, b);
            file >> a >> b;
        }
        file.close();
    }

    /*** print edges table (AM, IM, EL, IL) to std output ***/
    void display() {
        for (auto i : edges) {
            for (auto j : i)
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }

    void generate_dag(double sat);
};

void IGraph::generate_dag(double sat) {
    /// make vector with all possible edges (i < j), this guarantees that it will be acyclic
    /// shuffle this vector
    std::vector<std::pair<int, int>> possible_edges;
    for (int i = 0; i < V - 1; i++) {
        for (int j = i + 1; j < V; j++) {
            possible_edges.push_back(std::make_pair(i, j));
        }
    }
    std::random_shuffle(possible_edges.begin(), possible_edges.end());

    /// create hash_table, we will change the numbers of nodes to make this graph more general
    /// if we won't hash, topological order will always be 0, 1, 2, 3, ...
    std::vector<int> hash_table(V);
    for (int i = 0; i < V; i++)
        hash_table[i] = i;
    std::random_shuffle(hash_table.begin(), hash_table.end());

    /// take only proper number of edges, and hash nodes
    std::vector<std::pair<int, int>> list;
    /// we consider all edges even (i, i), despite we didn't generate such ones of course
    int num_of_edges = V * V * sat;
    for (int i = 0; i <= num_of_edges; i++)
        list.push_back(std::make_pair(hash_table[possible_edges[i].first], hash_table[possible_edges[i].second]));

    /// sort them to make it clean
    /// list of a's neighbors will be in format a : i < j < k < ...
    std::sort(list.begin(), list.end());

    /// add this edges
    for (auto i : list) {
        this->add_edge(i.first, i.second);
    }
}

/***********************************
*** GRAPH WITH ADJACENCY MATRIX ****
*** MEMORY O(V^2) ******************
***********************************/
class Graph_AM : public IGraph{
public:

    Graph_AM(int V) : IGraph(V) {
        edges = std::vector<std::vector<int>>(V);
        for (int i = 0; i < V; i++)
            edges[i] = std::vector<int>(V);
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                edges[i][j] = 0;
    }

    ~Graph_AM() {
        edges.clear();
    }

    /*** O(1) ***/
    void add_edge(int a, int b) {
        edges[a][b] = 1;
        edges[b][a] = 1;
        E++;
    }

    /*** O(1) ***/
    bool check_edge(int a, int b) {
        return edges[a][b] == 1;
    }
};

/**********************************
*** GRAPH WITH INCIDENCE MATRIX ***
*** MEMEORY O(V*E) ~ O(V^3) *******
***********************************/
class Graph_IM : public IGraph {
public:

    Graph_IM(int V) : IGraph(V) {
        edges = std::vector<std::vector<int>>(V);
    }

    ~Graph_IM() {
        edges.clear();
    }

    /*** O(V) ***/
    void add_edge(int a, int b) {
        E++;
        for (int i = 0; i < V; i++) {
            if (i == a || i == b)
                edges[i].push_back(1);
            else
                edges[i].push_back(0);
        }
    }

    /*** O(V*logE) ~ O(V*log(V^2)) ***/
    bool check_edge(int a, int b) {

        int beg = 0, end = E - 1;
        int _a = -1, _b = -1;

        /// start binary search
        while (beg < end) {
            int mid = (beg + end) / 2;

            /// _a, _b is edge stored in mid, but we have to find this values in O(V)
            _a = -1, _b = -1;
            for (int i = 0; i < V; i++) {
                if (edges[i][mid] == 1 && _a == -1)
                    _a = i;
                else if(edges[i][mid] == 1)
                    _b = i;
            }
            if (_a > a || (_a == a && _b >= b))
                end = mid;
            else
                beg = mid + 1;
        }

        _a = -1, _b = -1;
        for (int i = 0; i < V; i++) {
            if (edges[i][beg] == 1 && _a == -1)
                _a = i;
            else if(edges[i][beg] == 1)
                _b = i;
        }
        //std::cout << _a << " " << _b << std::endl;
        if (_a == a && _b == b)
            return true;
        return false;
    }
};

/***************************
*** GRAPH WITH EDGE LIST ***
*** MEMORY O(E) ~ O(V^2) ***
****************************/
class Graph_EL : public IGraph {
public:

    Graph_EL(int V) : IGraph(V) {
        edges = std::vector<std::vector<int>>();
    }

    ~Graph_EL() {
        edges.clear();
    }

    /*** O(1) ***/
    void add_edge(int a, int b) {
        edges.push_back(std::vector<int>(2));
        edges[E][0] = a;
        edges[E++][1] = b;
    }

    /*** O(logE) ~ O(log(V^2)) ***/
    bool check_edge(int a, int b) {
        int beg = 0, end = edges.size()-1;
        while (beg < end) {
            int mid = (beg + end) / 2;
            int _a = edges[mid][0], _b = edges[mid][1];
            if (_a > a || (_a == a && _b >= b))
                end = mid;
            else
                beg = mid + 1;
        }
        //std::cout << edges[beg][0] << " " << edges[beg][1] << std::endl;
        if (edges[beg][0] == a && edges[beg][1] == b)
            return true;
        return false;
    }
};

/********************************
*** GRAPH WITH INCIDENCE LIST ***
*** MEMORY O(E) ~ O(V^2) ********
*********************************/
class Graph_IL : public IGraph {
public:

    Graph_IL(int V) : IGraph(V) {
        edges = std::vector<std::vector<int>>(V);
    }

    ~Graph_IL() {
        edges.clear();
    }

    /*** O(1) ***/
    void add_edge(int a, int b) {
        E++;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }

    /*** O(log(deg(a))) ~ O(logV) ***/
    bool check_edge(int a, int b) {
        if (edges[a].size() > 0) {
            int beg = 0, end = edges[a].size() - 1;
            while (beg < end) {
                int mid = (beg + end) / 2;
                int _b = edges[a][mid];
                if (_b >= b)
                    end = mid;
                else
                    beg = mid + 1;
            }
            if (edges[a][beg] == b)
                return true;
            return false;
        }
        return false;
    }

    void display() {
        for (int i = 0; i < V; i++) {
            std::cout << i << ": ";
            for (auto j : edges[i])
                std::cout << j << " ";
            std::cout << std::endl;
        }
    }
};

/*** END OF UNDIRECTED GRAPHS FOR TASK 1 ***/
/*******************************************/


/**************************
***DIRECTED GRAPH CLASS ***
***WITH INCIDENCE LIST  ***
***MEMORY O(E) ~ O(V^2) ***
***************************/
class Digraph : public Graph_IL {
private:
    int *in_deg;

    /*** recursive method used by topological_sort method ***/
    void __topological_sort_recursive(int v, bool *visited, std::list<int> *result) {
        visited[v] = true;
        for (auto i : edges[v])
            if (!visited[i])
                __topological_sort_recursive(i, visited, result);
        result->push_front(v);
    }

public:

    Digraph(int V) : Graph_IL(V) {
        in_deg = new int[V];
        for (int i = 0; i < V; i++)
            in_deg[i] = 0;
    }

    ~Digraph() {
        delete [] in_deg;
        edges.clear();
    }

    /*** O(1) ***/
    void add_edge(int a, int b) {
        edges[a].push_back(b);
        in_deg[b]++;
        E++;
    }

    /*** uses DFS to sort nodes in topological order
    ******** O(V + E) ~ O(V + V^2) ~ O(V^2) *****/
    std::list<int>* topological_sort() {
        std::list<int> *result = new std::list<int>();
        bool *visited = new bool[V];
        for (int i = 0; i < V; i++)
            visited[i] = 0;
        for (int i = 0; i < V; i++)
            if (!visited[i])
                __topological_sort_recursive(i, visited, result);
        delete []visited;
        return result;
    }

    /*** Kahn's algorithm to find topological order of vertices ***
    *** O(V + E) ***/
    std::list<int>* kahn() {
        std::list<int> *result = new std::list<int>();
        std::list<int> S;

        for (int i = 0; i < V; i++)
            if (in_deg[i] == 0)
                S.push_back(i);
        while (!S.empty()) {
            int node = S.back();
            S.pop_back();
            result->push_back(node);
            for (auto a : edges[node]) {
                in_deg[a]--;
                if (in_deg[a] == 0)
                    S.push_back(a);
            }
        }
        return result;
    }
};

class DigraphMatrix : public Graph_AM {
private:
    int *out_deg;

public:

    DigraphMatrix(int V) : Graph_AM(V) {
        out_deg = new int [V];
        for (int i = 0; i < V; i++)
            out_deg[i] = 0;
    }

    ~DigraphMatrix() {
        edges.clear();
        delete [] out_deg;
    }

    void add_edge(int a, int b) {
        E++;
        edges[a][b] = 1;
        out_deg[a]++;
    }

    void remove_edge(int a, int b) {
        E--;
        edges[a][b] = 0;
        out_deg[a]--;
    }

    std::list<int>* new_alg();
};

std::list<int>* DigraphMatrix::new_alg() {
    std::list<int> *result = new std::list<int>();
    std::list<int> E, NE;

    for (int i = 0; i < V; i++) {
        if (out_deg[i] == 0)
            E.push_back(i);
        else
            NE.push_back(i);
    }

    while (!E.empty()) {
        int v = E.front();
        E.pop_front();
        std::list<int>::iterator it = NE.begin();
        while (it != NE.end()) {
            int w = *it;
            if (check_edge(w, v)) {
                remove_edge(w, v);
                if (out_deg[w] == 0) {
                    E.push_back(w);
                    NE.erase(it++);
                }
                else {
                    it++;
                }
            }
            else {
                it++;
            }
        }
        result->push_front(v);
    }
    return result;
}

#endif // GRAPHS_HPP_INCLUDED
