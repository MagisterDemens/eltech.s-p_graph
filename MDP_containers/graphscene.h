#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QObject>

#include "nodeitem.h"
#include "spgraph.h"

#include <iostream>

using namespace spg;

class GraphScene : public QGraphicsScene
{
    std::list<NodeItem*> nodesList;
    int initX = 45;
    int initY = 45;
    int dist = 120;
    Q_OBJECT
public:
    GraphScene(QObject* parent = 0);
    ~GraphScene();
    void drawGraph(SPGraph<CircuitElemData> graph);
    void walkDrawGraph(SPGraph<CircuitElemData> graph, int x, int y, SPVertex<CircuitElemData>* vertex);
    void drawNode(NodeItem* node);
    void drawEdges(int x, int y, int x1, int y1);
    void deleteNode(NodeItem* node);

signals:
    void itemSelected(QGraphicsItem* item);
    void itemInserted(QGraphicsItem* item);

};

#endif // GRAPHSCENE_H
