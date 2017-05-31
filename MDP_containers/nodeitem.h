#ifndef NODEITEM_H
#define NODEITEM_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>

#include "spgraphlib.h"
#include "circuitelemdata.h"


using namespace spg;

class NodeItem : public QGraphicsEllipseItem
{

public:
    SPVertex<CircuitElemData>* node;
    QGraphicsTextItem* text;

    NodeItem(SPVertex<CircuitElemData>* vertex, QGraphicsItem* parent = 0);
    NodeItem(SPVertex<CircuitElemData>* vertex, int x, int y, QGraphicsItem* parent = 0);
    ~NodeItem();

    int x;
    int y;
};

#endif // NODEITEM_H
