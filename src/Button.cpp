#include "Button.h"
#include <QBrush>

Button::Button(QString _text, QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    setRect(0, 0, 200, 50);
    text = new QGraphicsTextItem(_text, this);
    int x = (rect().width() - text->boundingRect().width()) / 2;
    int y = (rect().height() - text->boundingRect().height()) / 2;
    text->setPos(x, y);

    setAcceptHoverEvents(true);
    setBrush(QBrush(Qt::darkCyan));
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::cyan));
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::darkCyan));
}