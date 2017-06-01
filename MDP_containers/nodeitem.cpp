#include "nodeitem.h"

NodeItem::NodeItem(SPVertex<CircuitElemData>* vertex, QGraphicsItem* parent)
    :QGraphicsRectItem(parent)
{
    this->x = 0;
    this->y = 0;

    node = vertex;
    this->setRect(-25,-25,50,50);
    this->setBrush(QColor::fromRgbF(0.9,0.9,0.9));
    this->setPen(QPen(QColor::fromRgbF(0,0,0)));
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    QString data = QString("I= ");
    data.append(QString::number(
                    vertex->getData().getI()));
    data.append(QString("\nU= "));
    data.append(QString::number(
                    vertex->getData().getU()));
    data.append(QString("\nR= "));
    data.append(QString::number(
                    vertex->getData().getR()));

    text = new QGraphicsTextItem(data, this);
}

NodeItem::NodeItem(SPVertex<CircuitElemData> *vertex, int x, int y, QGraphicsItem* parent)
    :QGraphicsRectItem(parent){
    this->x = x;
    this->y = y;

    node = vertex;
    this->setRect(-25,-25,50,50);
    this->setBrush(QColor::fromRgbF(0.9,0.9,0.9));
    this->setPen(QPen(QColor::fromRgbF(0,0,0)));
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    QString data = QString("I= ");
    data.append(QString::number(
                    vertex->getData().getI()));
    data.append(QString("\nU= "));
    data.append(QString::number(
                    vertex->getData().getU()));
    data.append(QString("\nR= "));
    data.append(QString::number(
                    vertex->getData().getR()));
    text = new QGraphicsTextItem(data, this);
    text->setPos(-25,-25);
}

NodeItem::~NodeItem(){

}

