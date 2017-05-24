#include "mainwindow.h"
#include <QApplication>

#include "tasksolver.h"
#include"spgraph.h"
#include"spgraphiterator.h"
#include"circuitelemdata.h"
#include<iostream>

#include<fstream>
#include<sstream>
#include<iostream>

#include "tester.h"

using namespace spg;

void output();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //типа тест здесь находятся
    /*
    SPGraph<int>* graph = new SPGraph<int>(2,3);
    //std::cout << graph;
    const char* stru = graph->SPGStruct();
    std::cout << stru << std::endl << std::endl ;
    auto it1 = graph->begin();
    graph->SSPlit(*it1, 4);
    //std::cout << graph;
    stru = graph->SPGStruct();
    std::cout << stru << std::endl << std::endl;
    auto it2 = graph->begin();
    graph->SSPlit(*it2, 0, true);
    //std::cout << graph;
    stru = graph->SPGStruct();
    std::cout << stru << std::endl << std::endl;
    SPGraphIterator<int> it3 = graph->begin();
    ++it3;
    graph->PSPlit(*it3, 69);
    //std::cout << graph;
    stru = graph->SPGStruct();
    std::cout << stru << std::endl << std::endl ;
    SPGraphIterator<int> it4 = graph->begin();
    ++it4;
    graph->deleteVertex(*it4);
    //std::cout << graph;
    stru = graph->SPGStruct();
    std::cout << stru << std::endl << std::endl;
    */

    output();

    return a.exec();    
}

void output(){
    /*SPGraph<CircuitElemData> graph;
    std::ifstream in;
    in.open("D:\\Univer\\MDP\\read4.txt");
    in >> graph;
    in.close();
    TaskSolver *taskSolver = new TaskSolver();
    taskSolver->solve(graph);
    std::ofstream out;
    out.open("D:\\Univer\\MDP\\test.txt");
    out << graph.SPGStruct();
    //std::string str = graph.SPGStruct();
    out.close();
    std::cout << graph;*/
    Tester tester;
    tester.RunTests();
}
