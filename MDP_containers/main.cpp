#include "mainwindow.h"
#include <QApplication>

#include"spgraph.h"
#include"spgraphiterator.h"
#include"circuitelemdata.h"
#include<iostream>

#include<QDebug>
#include<fstream>

using namespace spg;

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

    SPGraph<CircuitElemData> graph;// = new SPGraph<CircuitElemData>(CircuitElemData(1,2,2));
    std::ifstream in;
    in.open("D:\\Univer\\MDP\\read.txt");
    in >> graph;
    in.close();
    graph.SSPlit(graph.at(0), CircuitElemData(2,3,6));
    std::ofstream out;
    out.open("D:\\Univer\\MDP\\test.txt");
    out << graph;
    out.close();

    return a.exec();    
}
