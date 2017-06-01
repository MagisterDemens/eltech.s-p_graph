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

    newGraph = new QAction("New", this);
    connect(newGraph, SIGNAL(triggered()),
            this, SLOT(createInitGraph()));

    showInfo = new QAction("Info", this);
    connect(showInfo, SIGNAL(triggered()),
            this, SLOT(showInfoWindow()));
}

void MainWindow::createToolBars(){
    fileToolBar = addToolBar("File");
    fileToolBar->addAction(openFile);
    fileToolBar->addAction(saveFile);

    mainToolBar = addToolBar("Control");
    mainToolBar->addAction(newGraph);
    mainToolBar->addAction(deleteNode);
    mainToolBar->addAction(addNodeParallel);
    mainToolBar->addAction(addNodeSeries);
    mainToolBar->addAction(calculateGraph);
    mainToolBar->addAction(showInfo);

    fileDialog = new QFileDialog();

    saveFile->setEnabled(false);
    deleteNode->setEnabled(false);
    addNodeParallel->setEnabled(false);
    addNodeSeries->setEnabled(false);
    calculateGraph->setEnabled(false);
}

void MainWindow::createScene(){
    scene = new GraphScene();
    scene->setSceneRect(0,0,1500,1500);

    view = new QGraphicsView(this);
    view->setScene(scene);
}

void MainWindow::createLineEdits(){
    editR = new QLineEdit();
    editU = new QLineEdit();
    editI = new QLineEdit();

    editR->setPlaceholderText("R = ");
    editU->setPlaceholderText("U = ");
    editI->setPlaceholderText("I = ");

    editR->setMaximumWidth(50);
    editU->setMaximumWidth(50);
    editI->setMaximumWidth(50);

    setCircuitData = new QPushButton();
    connect(setCircuitData, SIGNAL(clicked()), this, SLOT(setIUR()));

    setCircuitData->setText("Accept");
    setCircuitData->setMaximumWidth(50);
    setCircuitData->setEnabled(false);
}

void MainWindow::createInitialGraph(){
    CircuitElemData data = CircuitElemData();
    graph = SPGraph<CircuitElemData>(data);

    taskSolver = TaskSolver();
}

void MainWindow::itemDelete(){
    NodeItem* item = dynamic_cast<NodeItem*> (scene->selectedItems().at(0));
    scene->removeItem(item);
    auto vertex = item->node;
    scene->deleteNode(item);
    delete item;
    graph.deleteVertex(vertex);
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
    createInitialGraph();

    QString filePath;
    filePath = fileDialog->getOpenFileName();
    std::ifstream in;
    in.open(filePath.toStdString());
    in >> graph;
    in.close();

    saveFile->setEnabled(true);
    deleteNode->setEnabled(true);
    addNodeParallel->setEnabled(true);
    addNodeSeries->setEnabled(true);
    calculateGraph->setEnabled(true);
    setCircuitData->setEnabled(true);

    scene->drawGraph(graph);


}

void MainWindow::saveFileGraph(){
    QString filePath;
    filePath = fileDialog->getSaveFileName();
    std::ofstream out;
    out.open(filePath.toStdString());
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

void MainWindow::createInitGraph(){
    CircuitElemData data = CircuitElemData();
    graph = SPGraph<CircuitElemData>(data);

    taskSolver = TaskSolver();

    saveFile->setEnabled(true);
    deleteNode->setEnabled(true);
    addNodeParallel->setEnabled(true);
    addNodeSeries->setEnabled(true);
    calculateGraph->setEnabled(true);
    setCircuitData->setEnabled(true);

    scene->drawGraph(graph);


}

void MainWindow::showInfoWindow(){
    QWidget *infoWindow = new QWidget;
    infoWindow->setFixedWidth(400);
    infoWindow->setFixedHeight(200);

    QLabel* labelInfo = new QLabel("Система расчета однофазных электрических цепей.\nКонтейнер - параллельно-последовательный граф.\n\nАлексеевич\nБудчан\nЖангиров\nЧуланов\nСПбГЭТУ\n2017");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(labelInfo);

    infoWindow->setLayout(mainLayout);

    infoWindow->show();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    createScene();
    createActions();
    createToolBars();
    createLineEdits();

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->setAlignment(Qt::AlignLeft);

    QHBoxLayout* workspace = new QHBoxLayout;
    workspace->setAlignment(Qt::AlignTop);

    QHBoxLayout* circEditLayout = new QHBoxLayout;
    circEditLayout->setAlignment(Qt::AlignLeft);

    QLabel* labelR = new QLabel("Resistance: ");
    labelR->setMaximumWidth(67);
    QLabel* labelU = new QLabel("Voltage: ");
    labelU->setMaximumWidth(57);
    QLabel* labelI = new QLabel("Amperage: ");
    labelI->setMaximumWidth(62);

    circEditLayout->addWidget(labelR);
    circEditLayout->addWidget(editR);
    circEditLayout->addWidget(labelU);
    circEditLayout->addWidget(editU);
    circEditLayout->addWidget(labelI);
    circEditLayout->addWidget(editI);
    circEditLayout->addWidget(setCircuitData);

    centralLayout->addItem(circEditLayout);
    centralLayout->addItem(workspace);

    workspace->addWidget(view);

    QWidget* centre = new QWidget;
    centre->setLayout(centralLayout);
    setCentralWidget(centre);

//    createInitialGraph();
//    scene->drawGraph(graph);

    statusBar()->showMessage("Started correctly");
}

MainWindow::~MainWindow(){

}

