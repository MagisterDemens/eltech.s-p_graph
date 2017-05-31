#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QObject>

#include "nodeitem.h"
#include "spgraph.h"

using namespace spg;

class GraphScene : public QGraphicsScene
{
    std::list<NodeItem*> nodesList;
    int initX = 250;
    int intiY = 250;
    Q_OBJECT
public:
    GraphScene(QObject* parent = 0);
    ~GraphScene();
    void drawGraph(SPGraph<CircuitElemData> graph);
    void drawGraph2(SPGraph<CircuitElemData> graph);
    void drawNode(NodeItem* node);
    void drawEdges(SPGraph<CircuitElemData>* graph);

signals:
    void itemSelected(QGraphicsItem* item);
    void itemInserted(QGraphicsItem* item);

};

#endif // GRAPHSCENE_H
