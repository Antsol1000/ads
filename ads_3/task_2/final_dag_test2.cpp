#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<ctime>
#include"../graphs.hpp"

const std::string RESULT_FILENAME = "1";
const int MAX_V = 10000;
const int V_STEP = 1000;
const int NUMBER_OF_TRIALS = 3;

const double SAT = 0.3;


int main() {
    srand(time(0));
    clock_t start_t, end_t;
    std::ofstream results;
    results.open(RESULT_FILENAME + ".txt");
    results << "vertices;edges;time_of_trial;time_of_kahn_trial" << std::endl;
    std::list<int> *a;

    for (int V = V_STEP; V <= MAX_V; V += V_STEP) {
        std::cout << "test with size " << V;

        Digraph *g = new Digraph(V);
        results << V << ";";

        g->generate_dag(SAT);
        results << g->get_edges() << ";";

        clock_t dfs = 0, kahn = 0;

        for (int i = 0; i < NUMBER_OF_TRIALS; i++) {
            start_t = clock();
            a = g->topological_sort();
            end_t = clock();
            dfs += end_t - start_t;
            delete a;

            start_t = clock();
            a = g->kahn();
            end_t = clock();
            kahn += end_t - start_t;
            delete a;

            delete g;
            g = new Digraph(V);
            g->generate_dag(SAT);
        }
        results << dfs << ";";
        results << kahn << std::endl;
        delete g;
        std::cout << " complete!\n";
    }
    results.close();
}

