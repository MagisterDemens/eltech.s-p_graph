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
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>

#include <iostream>
#include <fstream>
#include <sstream>

#include "graphscene.h"
#include "nodeitem.h"
#include "spgraphlib.h"
#include "tasksolver.h"

using namespace spg;


class MainWindow : public QMainWindow
{
    Q_OBJECT
    SPGraph<CircuitElemData> graph;
    TaskSolver taskSolver;

    GraphScene* scene;
    QGraphicsView* view;

    QFileDialog* fileDialog;

    QToolBar* fileToolBar;
    QToolBar* mainToolBar;

    QAction* addNodeParallel;
    QAction* addNodeSeries;
    QAction* deleteNode;
    QAction* calculateGraph;
    QAction* openFile;
    QAction* saveFile;
    QAction* newGraph;
    QAction* showInfo;

    QLineEdit* editR;
    QLineEdit* editU;
    QLineEdit* editI;

    QPushButton* setCircuitData;

    void createScene();
    void createActions();
    void createToolBars();
    void createLineEdits();
    void createInitialGraph();

private slots:

    void itemInsertS();
    void itemInsertP();
    void itemDelete();
    void calculate();
    void openFileGraph();
    void saveFileGraph();
    void setIUR();
    void createInitGraph();
    void showInfoWindow();

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
