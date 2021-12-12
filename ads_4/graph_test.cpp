#include <iostream>
#include "graph.h"

int main() {
    graph *g = new graph(100);
    std::list<int> *a;
    /*g->add_edge(0, 1);
    g->add_edge(0, 6);
    g->add_edge(1, 2);
    g->add_edge(2, 0);
    g->add_edge(2, 3);
    g->add_edge(3, 4);
    g->add_edge(4, 2);
    g->add_edge(4, 5);
    g->add_edge(5, 0);
    g->add_edge(6, 4);*/
    g->generate_eulerian(0.95);
    std::cout << "l\n";
    //g->display();

    a = g->eulerian_cycle();
    //for (auto i : *a)
        //std::cout << i << " ";

    std::cout << std::endl << std::endl;

    delete g;
    g = new graph(10);

    g->generate_connected(0.95);
    g->display();

    //std::cout << g->get_E();

    a = g->hamiltonian_cycle();
    if (a->empty())
        std::cout << "no hamiltonian cycle!";
    else
        for (auto i : *a)
            std::cout << i << " ";

    delete g;
    return 0;
}
