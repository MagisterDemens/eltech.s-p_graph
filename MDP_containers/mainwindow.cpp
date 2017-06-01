#include "mainwindow.h"

void MainWindow::createActions(){
    deleteNode = new QAction("Delete node", this);
    connect(deleteNode, SIGNAL(triggered()),
            this, SLOT(itemDelete()));

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

    taskSolver = TaskSolver();
}

void MainWindow::itemDelete(){
    NodeItem* item = dynamic_cast<NodeItem*> (scene->selectedItems().at(0));

//    std::cout << "Normal" << std::endl;
    scene->removeItem(item);
    auto vertex = item->node;
    delete item;
    graph.deleteVertex(vertex);
//    std::cout << "WOW" << std::flush;

    scene->drawGraph(graph);
}

void MainWindow::itemInsertS(){
    CircuitElemData data = CircuitElemData();
    NodeItem* item = dynamic_cast<NodeItem*> (scene->selectedItems().at(0));
    graph.SSPlit(item->node, data);
    scene->drawGraph(graph);
}

void MainWindow::itemInsertP(){
    CircuitElemData data = CircuitElemData();
    NodeItem* item = dynamic_cast<NodeItem*> (scene->selectedItems().at(0));
    graph.PSPlit(item->node, data);
    scene->drawGraph(graph);
}

void MainWindow::openFileGraph(){
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
    taskSolver.solve(graph);

    scene->drawGraph(graph);
}

void MainWindow::setIUR(){
    QString R = editR->text();
    QString U = editU->text();
    QString I = editI->text();

    NodeItem* item = dynamic_cast<NodeItem*> (scene->selectedItems().at(0));
    CircuitElemData data = CircuitElemData(R.toDouble(), U.toDouble(), I.toDouble());
    item->node->setData(data);
    scene->drawGraph(graph);
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

    QHBoxLayout* circEditLayout = new QHBoxLayout;

    editR = new QLineEdit();
    editU = new QLineEdit();
    editI = new QLineEdit();
    circEditLayout->addWidget(editR);
    circEditLayout->addWidget(editU);
    circEditLayout->addWidget(editI);

    editR->setPlaceholderText("R = ");
    editU->setPlaceholderText("U = ");
    editI->setPlaceholderText("I = ");

    editR->setMaximumWidth(50);
    editU->setMaximumWidth(50);
    editI->setMaximumWidth(50);

    setCircuitData = new QPushButton();
    connect(setCircuitData, SIGNAL(clicked()), this, SLOT(setIUR()));

    setCircuitData->setText("Accept");

    circEditLayout->addWidget(setCircuitData);

    circEditLayout->setAlignment(Qt::AlignTop);
    workspace->addItem(circEditLayout);

    centralLayout->addItem(workspace);

    workspace->addWidget(view);

    QWidget* centre = new QWidget;
    centre->setLayout(centralLayout);
    setCentralWidget(centre);

    createInitialGraph();
    scene->drawGraph(graph);

    statusBar()->showMessage("Started correctly");
}

MainWindow::~MainWindow(){

}

