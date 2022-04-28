#include "Airplane.h"
#include "Bullet.h"
#include "Game.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QGraphicsScene>

extern Game *game;

Airplane::Airplane(QGraphicsItem *parent)
{
    bullet_sound = new CuteSoundPlayer("qrc:/sound/weapon_0.wav", this);
    draw();
}

void Airplane::draw()
{
    QPixmap body(body_image_url());
    QPixmap flame(speed_image_url());
    QPixmap full(body.width(), body.height() + flame.height());
    full.fill(Qt::transparent);
    QPainter painter(&full);
    painter.drawPixmap((body.width() - flame.width()) / 2, body.height() + flame_offset, flame);
    painter.drawPixmap(0, 0, body);
    setPixmap(full);
    update_flame_cnt();
    check_hit();
}

void Airplane::check_hit()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (QGraphicsItem *item : colliding_items)
    {
        if (typeid(*item) == typeid(Enemy))
        {
            emit game->stop();
        }
    }
}

QString Airplane::body_image_url()
{
    switch (direction)
    {
    case Left:
        return QString(":/image/airplane_%1/left.png").arg(airplane_id);
    case Right:
        return QString(":/image/airplane_%1/right.png").arg(airplane_id);
    default:
        return QString(":/image/airplane_%1/normal.png").arg(airplane_id);
    }
}

QString Airplane::speed_image_url()
{
    switch (speed)
    {
    case Fast:
        return QString(":/image/rocket_flame_%1/fast_%2.png").arg(flame_id).arg(flame_cnt);
    case Slow:
        return QString(":/image/rocket_flame_%1/slow_%2.png").arg(flame_id).arg(flame_cnt);
    default:
        return QString(":/image/rocket_flame_%1/normal_%2.png").arg(flame_id).arg(flame_cnt);
    }
}

void Airplane::update_flame_cnt()
{
    flame_cnt++;
    if (flame_cnt >= flame_cnt_total)
    {
        flame_cnt = 0;
    }
}

void Airplane::shoot()
{
    Bullet *new_bullet = new Bullet(this);
    new_bullet->setPos(x() + width() / 2 - new_bullet->width() / 2, y());
    game->add_item_to_layer(new_bullet, 1);
    bullet_sound->play();
}

void Airplane::backto_normal_direction()
{
    direction = Normal;
    draw();
}

void Airplane::backto_normal_speed()
{
    speed = Default;
    draw();
}

void Airplane::move_left(int distance)
{
    direction = Left;
    draw();
    if (x() > 0)
    {
        setPos(x() - distance, y());
    }
}

void Airplane::move_right(int distance)
{
    direction = Right;
    draw();
    if (x() + width() < game->width())
    {
        setPos(x() + distance, y());
    }
}

void Airplane::move_up(int distance)
{
    speed = Fast;
    draw();
    if (y() > 10)
    {
        setPos(x(), y() - distance);
    }
}

void Airplane::move_down(int distance)
{
    speed = Slow;
    draw();
    if (y() < game->height() - height() - 10)
    {
        setPos(x(), y() + distance);
    }
}