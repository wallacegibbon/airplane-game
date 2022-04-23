#ifndef __STATIC_STUFF_H
#define __STATIC_STUFF_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>

class RandomStaticSmoke : public QGraphicsPixmapItem
{
public:
    RandomStaticSmoke(QGraphicsItem *parent = nullptr);

private:
    int smoke_id = 0;
    int smoke_id_nums = 4;
};

#endif