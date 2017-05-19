#include "mainwindow.h"
#include <QApplication>

#include"spgraph.h"
#include"spgraphiterator.h"
#include<iostream>

#include<QDebug>

using namespace spg;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SPGraph<int>* graph = new SPGraph<int>(2,3);
    std::cout << graph;
    auto it1 = graph->begin();
    graph->SSPlit(*it1, 4);
    std::cout << graph;
    auto it2 = graph->begin();
    graph->SSPlit(*it2, 0, true);
    std::cout << graph;
    SPGraphIterator<int> it3 = graph->begin();
    ++it3;
    graph->PSPlit(*it3, 69);
    std::cout << graph;
    SPGraphIterator<int> it4 = graph->begin();
    ++it4;
    graph->deleteVertex(*it4);
    std::cout << graph;

    return a.exec();
}
