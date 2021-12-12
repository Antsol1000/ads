#include <iostream>
#include"../graphs.hpp"

int main() {
    const std::string FILE_PATH = "generated_dag.txt";
    Digraph *g = new Digraph(5);
    DigraphMatrix *q = new DigraphMatrix(5);
    g->load(FILE_PATH);
    q->load(FILE_PATH);
    //g->generate_dag(0.3);
    g->display();
    std::list<int>*A = g->topological_sort();
    for (auto i : *A)
        std::cout << i << " ";
    delete A;
    std::cout << std::endl;
    A = g->kahn();
    for (auto i : *A)
        std::cout << i << " ";

    delete A;
    delete g;

    std::cout << std::endl << std::endl;
    q->display();
    std::cout << std::endl;
    A = q->new_alg();
    for (auto i : *A)
        std::cout << i << " ";
    delete q;
    delete A;
}
