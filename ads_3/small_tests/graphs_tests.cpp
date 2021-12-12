#include<iostream>
#include"../graphs.hpp"

int main() {
    const std::string FILE_PATH = "generated_graph.txt";

    /** pointer on abstract parent class **/
    IGraph *a;

    /// test for adj matrix
    a = new Graph_AM(5);
    a->load(FILE_PATH);
    a->display();
    std::cout << a->check_edge(1, 2) << std::endl;
    std::cout << a->check_edge(0, 1) << std::endl;
    std::cout << a->check_edge(0, 2) << std::endl;
    delete a;
    std::cout << std::endl;

    /// test for inc matrix
    a = new Graph_IM(5);
    a->load(FILE_PATH);
    a->display();
    std::cout << a->check_edge(1, 2) << std::endl;
    std::cout << a->check_edge(0, 1) << std::endl;
    std::cout << a->check_edge(0, 2) << std::endl;
    delete a;
    std::cout << std::endl;

    /// test for edge list
    a = new Graph_EL(5);
    a->load(FILE_PATH);
    a->display();
    std::cout << a->check_edge(1, 2) << std::endl;
    std::cout << a->check_edge(0, 1) << std::endl;
    std::cout << a->check_edge(0, 2) << std::endl;
    delete a;
    std::cout << std::endl;

    /// test for inc list, using display method from IGraph (because of pointer)
    a = new Graph_IL(5);
    a->load(FILE_PATH);
    a->display();
    std::cout << a->check_edge(1, 2) << std::endl;
    std::cout << a->check_edge(0, 1) << std::endl;
    std::cout << a->check_edge(0, 2) << std::endl;
    delete a;
    std::cout << std::endl;

    /// test for inc list, using display method from Graph_IL (method override)
    Graph_IL *b;
    b = new Graph_IL(5);
    b->load(FILE_PATH);
    b->display();
    std::cout << b->check_edge(1, 2) << std::endl;
    std::cout << b->check_edge(0, 1) << std::endl;
    std::cout << b->check_edge(0, 2) << std::endl;
    delete b;
    std::cout << std::endl;

    return 0;
}
