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

    //рисование нулевой вершины
    NodeItem* startNode = new NodeItem(*graph.begin(), initX, initY);
    nodesList.insert(nodesList.end(), startNode);
    drawNode(startNode);

    //все потомки нулевой вершины
    std::vector<unsigned int> destinations = graph.getVertexDestination(*graph.begin(), true);

    unsigned int y = 0;
    foreach(unsigned int i, destinations){
        //рисование параллельных вершин. Все вершины лежать на dist правее(x) и различаются по высоте(y)
        NodeItem* item = new NodeItem(graph.at(i), initX+dist, initY+dist*y);
        nodesList.insert(nodesList.end(), item);
        drawNode(item);
        drawEdges(0, 0, 1, y);
        //переход в последовательно соединенную вершину сдвиг по x, по y значения не меняется
        walkDrawGraph(graph, 2, y, graph.at(i));
        y++;
    }
}

void GraphScene::walkDrawGraph(SPGraph<CircuitElemData> graph, int x, int y, SPVertex<CircuitElemData> *vertex){
    std::vector<unsigned int> destinations = graph.getVertexDestination(vertex, true);
    unsigned int yN = y;
    foreach(unsigned int i, destinations){
        NodeItem* item = new NodeItem(graph.at(i), initX+dist*x, initY+dist*yN);
        drawNode(item);
        //соединяем текущую вершину с предыдущей вершиной
        drawEdges(x-1, y, x, yN);
        //опять переход в последовательно соединенную вершину; сдвиг по x, по y значения не меняется
        walkDrawGraph(graph, x+1, yN, graph.at(i));
        yN++;
    }
}

void GraphScene::drawEdges(int x, int y, int x1, int y1){
    QGraphicsLineItem* line = new QGraphicsLineItem(initX+dist*x, initY+dist*y, initX+dist*x1, initY+dist*y1);
    line->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    line->setZValue(-10);
    addItem(line);
}

void GraphScene::deleteNode(NodeItem *node){
    nodesList.remove(node);
}