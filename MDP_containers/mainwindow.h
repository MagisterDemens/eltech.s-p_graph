#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QAction>
#include <QToolBar>
#include <QIcon>
#include <QCloseEvent>
#include <QStatusBar>
#include <QCoreApplication>
#include <QLineEdit>

#include <iostream>
#include <fstream>
#include <sstream>

#include "graphscene.h"
//#include "nodeitem.h"
//#include "spgraph.h"
//#include "spgraphlib.h"
//#include "tasksolver.h"

//using namespace spg;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    SPGraph<CircuitElemData> graph;

    GraphScene* scene;
    QGraphicsView* view;

    QToolBar* fileToolBar;
    QToolBar* mainToolBar;

    QAction* addNodeParallel;
    QAction* addNodeSeries;
    QAction* deleteNode;
    QAction* calculateGraph;
    QAction* openFile;
    QAction* saveFile;

    QLineEdit* editR;

    void createScene();
    void createActions();
    void createToolBars();
    void createInitialGraph();

private slots:

    void itemInsertS();
    void itemInsertP();
    void itemDelet();
    void calculate();
    void openFileGraph();
    void saveFileGraph();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};
/*
void MainWindow::createActions(){
    deleteNode = new QAction("Delete node", this);
    connect(deleteNode, SIGNAL(triggered()),
            this, SLOT(itemDelet()));

    addNodeParallel = new QAction("Add parallel", this);
    connect(addNodeParallel, SIGNAL(triggered()),
            this, SLOT(itemInsertP()));

    addNodeSeries = new QAction("Add series", this);
    connect(addNodeSeries, SIGNAL(triggered()),
            this, SLOT(itemInsertS()));

    calculateGraph = new QAction("Calculate", this);
    connect(calculateGraph, SIGNAL(triggered()),
            this, SLOT(calculate()));

    openFile = new QAction("Open", this);
    connect(openFile, SIGNAL(triggered()),
            this, SLOT(openFileGraph()));

    saveFile = new QAction("Save", this);
    connect(saveFile, SIGNAL(triggered()),
            this, SLOT(saveFileGraph()));
}

void MainWindow::createToolBars(){
    fileToolBar = addToolBar("File");
    fileToolBar->addAction(openFile);
    fileToolBar->addAction(saveFile);

    mainToolBar = addToolBar("Control");
    mainToolBar->addAction(deleteNode);
    mainToolBar->addAction(addNodeParallel);
    mainToolBar->addAction(addNodeSeries);
    mainToolBar->addAction(calculateGraph);
}

void MainWindow::createScene(){
    scene = new GraphScene();
    scene->setSceneRect(0,0,500,500);

    view = new QGraphicsView(this);
    view->setScene(scene);
}

void MainWindow::createInitialGraph(){
    CircuitElemData data = CircuitElemData();
    graph = SPGraph<CircuitElemData>(data);
}

void MainWindow::itemDelet(){

}

void MainWindow::itemInsertS(){
    CircuitElemData data = CircuitElemData();

    auto it1 = graph.begin();
    graph.SSPlit(*it1, data);
    scene->drawGraph(graph);
}

void MainWindow::itemInsertP(){
    CircuitElemData data = CircuitElemData();

    auto it1 = graph.at(1);
    graph.PSPlit(it1, data);
    scene->drawGraph(graph);
}

void MainWindow::openFileGraph(){
//    SPGraph<CircuitElemData> graphTemp;
    std::ifstream in;
    in.open("D:\\read1.txt");
    in >> graph;
    in.close();

    scene->drawGraph(graph);
}

void MainWindow::saveFileGraph(){
    std::ofstream out;
    out.open("D:\\test.txt");
    out << graph.SPGStruct();
    out.close();
}

void MainWindow::calculate(){

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    createScene();
    createActions();
    createToolBars();

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->setAlignment(Qt::AlignLeft);

    QHBoxLayout* workspace = new QHBoxLayout;
    workspace->setAlignment(Qt::AlignTop);

    workspace->addWidget(view);
    editR = new QLineEdit();
    //workspace->addWidget(editR);

    centralLayout->addItem(workspace);

    QWidget* centre = new QWidget;
    centre->setLayout(centralLayout);
    setCentralWidget(centre);

    createInitialGraph();
    scene->drawGraph(graph);

    statusBar()->showMessage("Started correctly");
}

MainWindow::~MainWindow(){

}
*/
#endif // MAINWINDOW_H
