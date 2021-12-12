#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "../graph.h"

const int MAX_SIZE = 1000;
const int STEP_SIZE = 100;
const double A[] = {.2, .3, .4, .6, .8, .95};
const int TRIALS = 10;

int main() {
    srand(time(0));
    time_t start_t, end_t;
    std::ofstream file;
    file.open("1_results.csv");

    file << "size;";
    for (double sat : A)
        file << sat << ";";
    file << std::endl;

    for (int size = STEP_SIZE; size <= MAX_SIZE; size += STEP_SIZE) {
        graph *g;
        file << size << ";";
        time_t time;

        std::cout << size << ": ";

        for (double sat : A) {
            std::cout << sat << " ";
            time = 0;
            std::list<int> *A[TRIALS];
            for (int i = 0; i < TRIALS; i++) {
                g = new graph(size);
                g->generate_eulerian(sat);

                start_t = clock();
                A[i] = g->eulerian_cycle();
                end_t = clock();

                time += end_t - start_t;
                delete g;
            }
            for (int i = 0; i < TRIALS; i++)
                delete A[i];
            file << time << ";";
            std::cout << "done ";
        }

        file << "\n";
        std::cout << "\n all done!" << std::endl;
    }

    file.close();
}
