#ifndef KNAPSACK_HPP_INCLUDED
#define KNAPSACK_HPP_INCLUDED

#include <vector>
#include <algorithm>


/*** finds maximal value of knapsack with given capacity,
vector items keeps value-weight pairs
*** time O(capacity * n) additional memory O(2*n) ***/
int dynamic_ks(int capacity, std::vector<std::pair<int, int>> items) {
    // number of items
    int n = items.size();

    // array with maximum values for given capacity
    int ** A;
    A = new int * [2];
    A[0] = new int [capacity + 1];
    A[1] = new int [capacity + 1];
    for (int i = 0; i <= capacity; i++) {
        A[0][i] = 0;
        A[1][i] = 0;
    }

    // for every item
    for (int i = 0; i < n; i++) {
        // for every capacity
        for (int j = 0; j <= capacity; j++) {
            // we try if we can add i-th item and if it will make our result greater
            int v = items[i].first, w = items[i].second;
            if (w > j)
                A[1][j] = A[0][j];
            else
                A[1][j] = std::max(A[0][j], A[0][j - w] + v);
        }
        // write from A[1] to A[0], in next step we have recently results in A[0]
        for (int j = 0; j <= capacity; j++) {
            A[0][j] = A[1][j];
        }
    }

    int result = A[0][capacity];

    delete [] A[0];
    delete [] A[1];
    delete [] A;

    return result;
}

/*** brute force for knapsack problem with given capacity,
vector items keeps value-weight pairs
*** time O(n*2^n) additional memory O(1) ***/
int exhaustive_ks(int capacity, std::vector<std::pair<int, int>> items) {
    int n = items.size();
    int result = 0;
    // masks - for example 00100010 = only items with 1 and 5 indexes
    for (int i = 0; i < 1 << n; i++) {
        int mask = i, value = 0, weight = 0;
        for (int j = 0; j < n; j++) {
        	// if last bit is 1 take this item and divide mask by two
            if (mask & 1) {
                value += items[j].first;
                weight += items[j].second;
            }
            mask >>= 1;
        }
        if (weight <= capacity)
            result = std::max(result, value);
    }
    return result;
}

/*** return if a.first/a.second >= b.first/b.second ***/

bool compare(const std::pair<int,int> &a,
                   const std::pair<int,int> &b)
{
       return (double) (a.first/a.second) > (double) (b.first/b.second);
}

/*** greedy algorithm for knapsack problem with given capacity,
vector items keeps value-weight pairs
*** time O(n*log(n)) additional memory O(1) ***/
int greedy_ks(int capacity, std::vector<std::pair<int, int>> items) {
    std::sort(items.begin(), items.end(), compare);
    int result = 0, weight = 0;
    for (auto i : items) {
        if (weight + i.second <= capacity) {
            weight += i.second;
            result += i.first;
        }
    }
    return result;
}

/*** draw n items, with weights in range [1, W], values in range [1, V] ***/
void draw_items(std::vector<std::pair<int, int>> items);

#endif // KNAPSACK_HPP_INCLUDED
