#include<cstdio>
#include "../sorting_algs.hpp"

const int SIZE = 100;
const int lower_bound = 100, upper_bound = 999;

int main() {
    int A[8][SIZE];
    randomize_array(A[0], SIZE, lower_bound, upper_bound);
    for (int i = 1; i < 8; i++)
        for (int j = 0; j < SIZE; j++)
            A[i][j] = A[0][j];

    print_array(A[0], SIZE);

    insertion_sort(A[0], SIZE);
    selection_sort(A[1], SIZE);
    bubble_sort(A[2], SIZE);
    heap_sort(A[3], SIZE);
    quick_sort(A[4], SIZE);
    merge_sort(A[5], SIZE);
    SHS_ciura(SIZE, A[6]);
    counting_sort(A[7], SIZE);

    for (int i = 0; i < SIZE; i++)
        printf("element %d\tIS: %d; SS: %d; BS: %d; HS: %d; QS: %d; MS: %d; SHS: %d; CS: %d;\n", i, A[0][i], A[1][i], A[2][i], A[3][i], A[4][i], A[5][i], A[6][i], A[7][i]);
}
