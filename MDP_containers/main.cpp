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

void test();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //test();

    return a.exec();    
}

void test(){
    Tester tester;
    tester.RunTests();
}
