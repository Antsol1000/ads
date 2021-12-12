#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<ctime>
#include"../graphs.hpp"

const std::string PATH = "dag_gen/";
const std::string RESULT_FILENAME = "top_sort";
const int MAX_V = 5000;
const int V_STEP = 250;
const int NUMBER_OF_TRIALS = 1;


int main() {
    clock_t start_t, end_t;
    std::ofstream results;
    results.open(RESULT_FILENAME + ".txt");
    results << "vertices;edges;time_of_trial;avg_time;time_of_kahn_trial;avg_kahn_time" << std::endl;

    for (int V = V_STEP; V <= MAX_V; V += V_STEP) {
        std::cout << "test with size " << V;
        const std::string FILE_PATH = PATH + std::to_string(V) + ".txt";

        Digraph *g = new Digraph(V);
        results << V << ";";

        g->load(FILE_PATH);
        results << g->get_edges() << ";";

        start_t = clock();
        for (int i = 0; i < NUMBER_OF_TRIALS; i++)
            g->topological_sort();
        end_t = clock();
        results << end_t - start_t << ";" << (double) (end_t - start_t) / NUMBER_OF_TRIALS << ";";

        start_t = clock();
        for (int i = 0; i < NUMBER_OF_TRIALS; i++)
            g->kahn();
        end_t = clock();
        results << end_t - start_t << ";" << (double) (end_t - start_t) / NUMBER_OF_TRIALS << std::endl;

        delete g;

        std::cout << " complete!\n";
    }
    results.close();
}
