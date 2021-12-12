#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "../graph.h"

const int MAX_SIZE = 250;
const int STEP_SIZE = 50;
const double A[] = {.2, .3, .4, .6, .8, .95};
const int TRIALS = 5;

int main() {
    srand(time(0));
    time_t start_t, end_t;
    std::ofstream file, file2;
    file.open("2_results.csv");
    file2.open("full.csv");

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
                g->generate_connected(sat);

                start_t = clock();
                A[i] = g->hamiltonian_cycle(start_t);
                end_t = clock();

                time += end_t - start_t;
                file2 << sat << ";" << size << ";" << end_t - start_t << "\n";
                delete g;
            }
            for (int i = 0; i < TRIALS; i++)
                delete A[i];
            file << time << ";";
            std::cout << time << std::endl;
            std::cout << "done ";
        }

        file << "\n";
        std::cout << "\n all done!" << std::endl;
    }

    file.close();
    file2.close();
}

