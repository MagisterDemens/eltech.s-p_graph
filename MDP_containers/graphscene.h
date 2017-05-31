#ifndef GRAPHSCENE_H
#define GRAPHSCENE_H

#include <QGraphicsScene>
#include <QObject>

#include "nodeitem.h"
//#include "spgraph.h"
//#include "tasksolver.h"

//using namespace spg;

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
/*
GraphScene::GraphScene(QObject *parent)
    :QGraphicsScene(parent){

}

GraphScene::~GraphScene(){

}

void GraphScene::drawNode(NodeItem* node){
    //NodeItem* item = new NodeItem(node, x, y);
    addItem(node);
    node->setPos(node->x, node->y);

    //nodesList.insert(nodesList.end(), item);

    emit itemInserted(node);
}

void GraphScene::drawGraph(SPGraph<CircuitElemData> graph){
    GraphScene::clear();

    for(int i = 0; i < graph.size(); i++){
        NodeItem* item = new NodeItem(graph.at(i), i*40, i*40);
        nodesList.insert(nodesList.end(), item);
        drawNode(item);
    }
    QGraphicsLineItem* item = new QGraphicsLineItem(0,0,60,60);
    item->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    item->setZValue(-1000);
    addItem(item);
}

void GraphScene::drawEdges(SPGraph<CircuitElemData>* graph){
    foreach(NodeItem* pair, nodesList){
        std::vector<unsigned int> destinations = graph->getVertexDestination(pair->node);
        foreach(unsigned int i, destinations){
            //drawLine( , )
        }
    }
}
*/
#endif // GRAPHSCENE_H
