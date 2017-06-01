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

    for(int i = 1; i < graph.size(); i++){
        notNodes.insert(i);
    }

    //рисование нулевой вершины
    NodeItem* startNode = new NodeItem(*graph.begin(), initX, initY);
    nodesList.insert(nodesList.end(), startNode);
    drawNode(startNode);

    //все потомки нулевой вершины
    std::vector<unsigned int> destinations = graph.getVertexDestination(*graph.begin(), true);

    unsigned int y = 0;
    foreach(unsigned int i, destinations){
        //рисование параллельных вершин. Все вершины лежать на dist правее(x) и различаются по высоте(y)
        if(notNodes.remove(i)){
            NodeItem* item = new NodeItem(graph.at(i), initX+dist, initY+dist*y);
            nodesList.insert(nodesList.end(), item);
            drawNode(item);
            drawEdges(0, 0, 1, y);
            //переход в последовательно соединенную вершину сдвиг по x, по y значения не меняется
            walkDrawGraph(graph, 2, y, graph.at(i));
            y++;
        }else{
            foreach(NodeItem* pair, nodesList){
                if(pair->node == graph.at(i)){
                    //drawEdges((pair->x-initX)/dist, (pair->y-initY)/dist, 0, 0);
                     drawEdges(2, y, (pair->x-initX)/dist, (pair->y-initY)/dist);

                }
            }
            y++;
        }
    }

//    for(auto i = graph.begin(); i != graph.end(); i++){
//        std::vector<unsigned int> dest = graph.getVertexDestination(*i, false);
//         if(dest.size() == 0){
//             nodesList.push_back(new NodeItem(*i, initX, initY));
//             drawNode(nodesList.at(0));
//         }
//         else{
//             unsigned int max_x = 0, min_y = 100000000;
//             NodeItem* temp;
//             for(int j = 0; j < dest.size(); j++){
//                temp = nodesList.at(dest[j]);
//                if(max_x < temp->x){
//                    max_x = temp->x;
//                }

//                std::vector<unsigned int> dest2 = graph.getVertexDestination(graph.at(dest[j]), true);
//                int q = -1;
//                for(int h = 0; h < dest2.size(); h++){
//                    q++;
//                    if(temp->node == graph.at(dest2[h])){
//                        break;
//                    }
//                }
//                if(min_y > temp->y){
//                    min_y = temp->y+q*dist;
//                }
//             }

//             nodesList.push_back(new NodeItem(*i, max_x+dist, min_y));
//             drawNode(temp);
//             for(int j = 0; j < dest.size(); j++){
//                 NodeItem* temp2 = nodesList.at(dest[j]);
//                 drawEdges(temp->x, temp->y, temp2->x, temp2->y );
//             }
//         }
//    }


}

void GraphScene::walkDrawGraph(SPGraph<CircuitElemData> graph, int x, int y, SPVertex<CircuitElemData> *vertex){
    std::vector<unsigned int> destinations = graph.getVertexDestination(vertex, true);
    unsigned int yN = y;
    foreach(unsigned int i, destinations){
        if(notNodes.remove(i)){
            NodeItem* item = new NodeItem(graph.at(i), initX+dist*x, initY+dist*yN);
            drawNode(item);
            //соединяем текущую вершину с предыдущей вершиной
            drawEdges(x-1, y, x, yN);
            //опять переход в последовательно соединенную вершину; сдвиг по x, по y значения не меняется
            walkDrawGraph(graph, x+1, yN, graph.at(i));
            yN++;
        }else{
            foreach(NodeItem* pair, nodesList){
                if(pair->node == graph.at(i)){
//                    drawEdges(x-1, yN, x, yN-1);
                    drawEdges(x-1, yN, (pair->x-initX)/dist, (pair->y-initY)/dist);

                }
            }
            yN++;
        }
    }
}

void GraphScene::drawEdges(int x, int y, int x1, int y1){
    QGraphicsLineItem* line = new QGraphicsLineItem(initX+dist*x, initY+dist*y, initX+dist*x1, initY+dist*y1);
    line->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    line->setZValue(-10);
    addItem(line);
}

void GraphScene::deleteNode(NodeItem *node){
   // nodesList.remove(node);
}
