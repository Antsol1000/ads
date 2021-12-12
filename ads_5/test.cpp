#include <iostream>
#include "knapsack.hpp"

#define MP(a, b) std::make_pair(a, b)

int main() {
    std::vector<std::pair<int, int>> items;
    items.push_back(MP(1, 2));
    items.push_back(MP(3, 7));
    items.push_back(MP(2, 5));
    items.push_back(MP(10, 9));
    items.push_back(MP(7, 12));
    int capacity = 15;
    // should be 12
    int dynamic_result = dynamic_ks(capacity, items);
    // should be 12
    int exhaustive_result = exhaustive_ks(capacity, items);
    // should be 11
    int greedy_result = greedy_ks(capacity, items);
    std::cout << dynamic_result << std::endl;
    std::cout << exhaustive_result << std::endl;
    std::cout << greedy_result << std::endl;
}
