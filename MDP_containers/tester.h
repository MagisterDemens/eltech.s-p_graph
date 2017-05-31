#ifndef TESTER_H
#define TESTER_H

#include "spgraphlib.h"
#include "circuitelemdata.h"

using namespace spg;

class Tester
{
    void UnitTest1();
    void UnitTest2();
    void UnitTest3();
    void UnitTest4();
    void UnitTest5();
    void UnitTest6();
    void UnitTest7();
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
    std::cout << "Trying to add sequensed vertex after start vertex\n";
    try {
        graph.SSPlit(graph.at(0), CircuitElemData(2,2,2), true);
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;
    std::cout << "Trying to add sequensed vertex before start vertex\n";
    try {
        graph.SSPlit(graph.at(0), CircuitElemData(3,3,3));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;
    std::cout << "Trying to add sequensed vertex before end vertex\n";
    try {
        graph.SSPlit(graph.at(graph.size()-1), CircuitElemData(4,4,4));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;
    std::cout << "Trying to add sequensed vertex after end vertex\n";
    try {
        graph.SSPlit(graph.at(graph.size()-1), CircuitElemData(5,5,5), true);
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;
    graph.clear();
}

void Tester::UnitTest4()
{
    std::cout << "Reading from file\n";
    SPGraph<CircuitElemData> graph;
    std::ifstream in;
    in.open("D:\\Univer\\MDP\\test1.txt");
    in >> graph;
    in.close();
    std::cout << graph << std::endl;

    std::cout << "Trying to delete full bond vertex\n";
    try {
        graph.deleteVertex(graph.at(3));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;

    std::cout << "Trying to add parallel vertex to full bond vertex\n";
    try {
        graph.PSPlit(graph.at(3), CircuitElemData(0,0,0));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;

    std::cout << "Trying to delete first parallel vertex\n";
    try {
        graph.deleteVertex(graph.at(2));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;

    std::cout << "Trying to delete second parallel vertex\n";
    try {
        graph.deleteVertex(graph.at(5));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;

    std::cout << "Trying to delete vertex in middle\n";
    try {
        graph.deleteVertex(graph.at(3));
    } catch (SPGException e) {
        std::cout << e.what();
    }
    std::cout << graph << std::endl;

    graph.clear();
}

void Tester::UnitTest5()
{
    std::cout << "Reading from file\n";
    SPGraph<CircuitElemData> graph;
    std::ifstream in;
    in.open("D:\\Univer\\MDP\\test1.txt");
    in >> graph;
    in.close();
    std::cout << graph << std::endl;

    std::cout << "Show data with iterator\n";
    for(auto i = graph.begin(); i != graph.end(); i++){
        SPVertex<CircuitElemData>* temp = *i;
        std::cout << temp << std::endl;
    }

    std::cout << "Changing data with iteartor\n";
    for(auto i = graph.begin(); i != graph.end(); i++){
        SPVertex<CircuitElemData>* temp = *i;
        temp->setData(CircuitElemData(0,0,0));
    }

    std::cout << graph << std::endl;
    graph.clear();
}

void Tester::UnitTest6()
{
    SPGraph<int> graph = SPGraph<int>(2);

    std::cout << "Testing iterator exceptions\n";
    auto it1 = graph.begin();
    std::cout << "1\n";
    try{
        --it1;
    }
    catch(SPGException e){
        std::cout << e.what();
    }

    std::cout << "3\n";
    try{
        it1 += 100;
    }
    catch(SPGException e){
        std::cout << e.what();
    }
    std::cout << "4\n";
    auto it2 = graph.end();
    try{
        ++it2;
    }
    catch(SPGException e){
        std::cout << e.what();
    }
    std::cout << "5\n";
    try{
        it2++;
    }
    catch(SPGException e){
        std::cout << e.what();
    }
    std::cout << "6\n";
    try{
        it2 -= 100;
    }
    catch(SPGException e){
        std::cout << e.what();
    }
    std::cout << std::flush;

    graph.clear();
}

void Tester::UnitTest7()
{
    std::cout << "Reading from file\n";
    SPGraph<CircuitElemData> graph;
    std::ifstream in;
    in.open("D:\\Univer\\MDP\\test1.txt");
    in >> graph;
    in.close();
    std::cout << graph << std::endl;

    std::cout << "Show data with iterator (reverse)\n";
    for(auto i = --graph.end(); i != graph.begin(); i -= 1){
        SPVertex<CircuitElemData>* temp = *i;
        std::cout << temp << std::endl;
    }

    std::cout << "Changing data with iteartor (reverse)\n";
    for(auto i = --graph.end(); i != graph.begin(); --i){
        SPVertex<CircuitElemData>* temp = *i;
        temp->setData(CircuitElemData(9,9,9));
    }

    std::cout << graph << std::endl;
    graph.clear();
}

void Tester::RunTests()
{
    std::cout << "Test #1\n";
    this->UnitTest1();
    std::cout << "Test #2\n";
    this->UnitTest2();
    std::cout << "Test #3\n";
    this->UnitTest3();
    std::cout << "Test #4\n";
    this->UnitTest4();
    std::cout << "Test #5\n";
    this->UnitTest5();
    std::cout << "Test #6\n";
    this->UnitTest6();
    std::cout << "Test #7\n";
    this->UnitTest7();
}

#endif // TESTER_H
