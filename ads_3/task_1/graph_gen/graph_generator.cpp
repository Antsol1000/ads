#include<iostream>
#include<fstream>
#include<ctime>
#include<algorithm>
#include<vector>
#include<string>

const int MAX_V = 5000;
const int V_STEP = 250;
const double sat = 0.6;

int main() {
    srand(time(0));

    for (int V = V_STEP; V <= MAX_V; V += V_STEP) {

        /// make vector with all possible edges (i < j), because we will anyhow add (i, j) and (j, i)
        /// shuffle this vector
        std::vector<std::pair<int, int>> possible_edges;
        for (int i = 0; i < V - 1; i++) {
            for (int j = i + 1; j < V; j++) {
                possible_edges.push_back(std::make_pair(i, j));
            }
        }
        std::random_shuffle(possible_edges.begin(), possible_edges.end());

        /// take only proper number of edges (these are randomly selected because of shuffle)
        std::vector<std::pair<int, int>> list;
        int num_of_edges = V * (V - 1) / 2 * sat;
        for (int i = 0; i <= num_of_edges; i++)
            list.push_back(possible_edges[i]);

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
    }
}
