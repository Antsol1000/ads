#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<ctime>
#include"../graphs.hpp"

const std::string PATH = "graph_gen/";

template<class T>
void test_graph(int V_STEP, int MAX_V, const std::string RESULT_FILENAME) {
    clock_t start_t, end_t;
    std::ofstream results;
    results.open(RESULT_FILENAME + ".txt");
    results << "vertices;edges;max_edges;time;avg_time" << std::endl;

    for (int V = V_STEP; V <= MAX_V; V += V_STEP) {
        std::cout << RESULT_FILENAME + " test with size " << V;
        const std::string FILE_PATH = PATH + std::to_string(V) + ".txt";

        std::vector<std::pair<int, int>> list;
        for (int i = 0; i < V - 1; i++)
            for (int j = i + 1; j < V; j++)
                list.push_back(std::make_pair(i, j));
        std::random_shuffle(list.begin(), list.end());

        T* graph = new T(V);
        graph->load(FILE_PATH);
        start_t = clock();
        for (auto i : list) {
            graph->check_edge(i.first, i.second);
        }
        end_t = clock();
        results << V << ";" << graph->get_edges() << ";" << list.size() << ";" << end_t - start_t << ";" << (double)(end_t - start_t) / list.size() << std::endl;
        delete graph;
        std::cout << " complete\n";
    }
    results.close();
}


int main() {
    const std::string AM = "AM_results";
    const std::string IM = "IM_results";
    const std::string EL = "EL_results";
    const std::string IL = "IL_results";
    test_graph<Graph_AM>(250, 5000, AM);
    test_graph<Graph_IM>(100, 900, IM);
    test_graph<Graph_EL>(250, 5000, EL);
    test_graph<Graph_IL>(250, 5000, IL);
}
