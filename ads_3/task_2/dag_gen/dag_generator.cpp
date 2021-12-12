#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
#include<vector>
#include<string>

const int MAX_V = 5000;
const int V_STEP = 250;
const double sat = 0.3;

int main() {
    srand(time(0));

    for (int V = V_STEP; V <= MAX_V; V += V_STEP) {
        std::cout << "generating dag with size " << V;

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

        /// save list of edges in file
        std::string file_name = std::to_string(V);
        file_name = file_name + ".txt";
        std::ofstream file;
        file.open(file_name);
        for (auto i : list) {
            file << i.first << " " << i.second << "\n";
        }
        file.close();

        std::cout << " complete\n";
    }
}
