#include "graphscene.h"

GraphScene::GraphScene(QObject *parent)
    :QGraphicsScene(parent){

}

GraphScene::~GraphScene(){

}

void GraphScene::drawNode(NodeItem* node){
    addItem(node);
    node->setPos(node->x, node->y);

    emit itemInserted(node);
}

void GraphScene::drawGraph(SPGraph<CircuitElemData> graph){
    GraphScene::clear();
    nodesList.clear();
    notNodes.clear();

    for(unsigned int i = 1; i < graph.size(); i++){
        notNodes.insert(i);
    }

    NodeItem* startNode = new NodeItem(*graph.begin(), initX, initY);
    nodesList.insert(nodesList.end(), startNode);
    drawNode(startNode);

    walkDrawGraph(graph, initX, initY, startNode->node);
}

void GraphScene::walkDrawGraph(SPGraph<CircuitElemData> graph, int x, int y, SPVertex<CircuitElemData>* vertex){
     std::vector<unsigned int> destinations = graph.getVertexDestination(vertex, true);
     unsigned int s = 0;
     NodeItem* item;
     foreach(unsigned int i, destinations){
         if(notNodes.remove(i)){
            item = new NodeItem(graph.at(i), x+dist, int(y+dist*s));
            drawNode(item);
            drawEdges(x, y, x+dist, y+dist*s);
            nodesList.insert(nodesList.end(), item);

            walkDrawGraph(graph, x+dist, y+dist*s, item->node);
         }else{
             foreach(NodeItem* pair, nodesList){
                 if(pair->node == graph.at(i)){
                     drawEdges(x, y, pair->x, pair->y);
                 }
             }
         }
         s++;
     }
}

void GraphScene::drawEdges(int x, int y, int x1, int y1){
    QGraphicsLineItem* line = new QGraphicsLineItem(x, y, x1, y1);
    line->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    line->setZValue(-10);
    addItem(line);
}

void GraphScene::deleteNode(NodeItem *node){
   // nodesList.remove(node);
}
