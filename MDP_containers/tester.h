#ifndef TESTER_H
#define TESTER_H

#include "spgraph.h"
#include "circuitelemdata.h"

using namespace spg;

class Tester
{
    void UnitTest1();
    void UnitTest2();
    void UnitTest3();
public:
    Tester(){}
    void RunTests();
};

void Tester::UnitTest1()
{
    std::cout << "Creating graph\n";
    SPGraph<CircuitElemData> graph(CircuitElemData(1,1,1), CircuitElemData(1,1,1));
    std::cout << graph << std::endl;
    std::cout << "Trying delete start vertex\n";
    try {
        graph.deleteVertex(graph.at(0));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << "Trying delete end vertex\n";
    try {
        graph.deleteVertex(graph.at(1));
    } catch (SPGException e) {
        std::cout << e.what();
    }

    std::cout << "Final graph\n";
    std::cout << graph << std::endl;
    graph.clear();
}

void Tester::UnitTest2()
{
    std::cout << "Creating graph\n";
    SPGraph<CircuitElemData> graph(CircuitElemData(1,1,1), CircuitElemData(1,1,1));
    std::cout << graph << std::endl;
    std::cout << "Trying to add parallel vertex to start vertex\n";
    try {
        graph.PSPlit(graph.at(0), CircuitElemData(2,2,2));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;
    std::cout << "Trying to add parallel vertex to end vertex\n";
    try {
        graph.PSPlit(graph.at(0), CircuitElemData(3,3,3));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;
    graph.clear();
}

void Tester::UnitTest3()
{
    std::cout << "Creating graph\n";
    SPGraph<CircuitElemData> graph(CircuitElemData(1,1,1), CircuitElemData(1,1,1));
    std::cout << graph << std::endl;
    std::cout << "Trying to add parallel vertex to start vertex\n";
    try {

    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;
}

void Tester::RunTests()
{
    std::cout << "Test #1\n";
    this->UnitTest1();
    std::cout << "Test #2\n";
    this->UnitTest2();
}

#endif // TESTER_H
