#include<fstream>
#include<iostream>
#include<ctime>
#include "../sorting_algs.hpp"

const int NUMBER_OF_TESTS = 5;
const int SIZE_STEP = 5000;
const int MAX_SIZE = 1000000;

int main() {
    srand(time(0));

    double total_time[4][MAX_SIZE / SIZE_STEP + 2];
    for (int i = 0; i <= MAX_SIZE / SIZE_STEP + 1; i++) {
        total_time[0][i] = 0;
        total_time[1][i] = 0;
        total_time[2][i] = 0;
        total_time[3][i] = 0;
    }

    for (int test_number = 0; test_number < NUMBER_OF_TESTS; test_number++) {

        for (int i = 1; i <= MAX_SIZE / SIZE_STEP; i++) {
            int size = SIZE_STEP * i;
            int *A = new int [size];
            clock_t start_t, end_t;

            randomize_array(A, size, 1, 2*size);
            start_t = clock();
            if (i <= 5) {
                bubble_sort(A, size);
            }
            end_t = clock();
            total_time[0][i] += (double)(end_t - start_t);

            randomize_array(A, size, 1, 2*size);
            start_t = clock();
            heap_sort(A, size);
            end_t = clock();
            total_time[1][i] += (double)(end_t - start_t);

            randomize_array(A, size, 1, 2*size);
            start_t = clock();
            counting_sort(A, size);
            end_t = clock();
            total_time[2][i] += (double)(end_t - start_t);

            randomize_array(A, size, 1, 2*size);
            start_t = clock();
            SHS_classic(size, A);
            end_t = clock();
            total_time[3][i] += (double)(end_t - start_t);

            delete []A;
            std::cout << "test number\t" << test_number << "\tsize\t" << size << "\n";
        }
    }
    std::ofstream file;
    file.open("1.csv");
    file << "size;BS;HS;CS;SHS\n";
    for (int i = 1; i <= MAX_SIZE / SIZE_STEP; i++) {
        file << i * SIZE_STEP << ";";
        file << total_time[0][i] / NUMBER_OF_TESTS << ";";
        file << total_time[1][i] / NUMBER_OF_TESTS << ";";
        file << total_time[2][i] / NUMBER_OF_TESTS << ";";
        file << total_time[3][i] / NUMBER_OF_TESTS << ";\n";
    }
    file.close();
    return 0;
}
