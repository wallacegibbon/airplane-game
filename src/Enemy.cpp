#include "Enemy.h"
#include "Airplane.h"
#include "Game.h"
#include "StaticExplosion.h"
#include "common.h"
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QTimer>

extern Game *game;

Enemy::Enemy(int _layer) : layer(_layer)
{
    connect(this, &Enemy::hit_by_bullet, this, &Enemy::handle_bullet_hit);
    setPos(QRandomGenerator::global()->bounded(0, game->width()), 0);
    speed = QRandomGenerator::global()->bounded(5, 50);

    QPixmap pixmap(":/image/enemy_0.png");
    setPixmap(pixmap);
    setTransformOriginPoint(pixmap.width() / 2, pixmap.height() / 2);
    if (speed > BASE_SPEED)
    {
        setRotation(180);
    }

    score = 1;

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(interval_from_speed(speed));
}

void Enemy::move()
{
    setPos(x(), y() + 5);
    if (y() > game->height())
    {
        game->removeItem(this);
        delete this;
    }
}

void Enemy::handle_bullet_hit(Airplane *player)
{
    player->inc_score(get_score());
    emit game->score_change();
    emit game->enemy_destroyed();

    // create and attach the explosion animation
    StaticExplosion *explosion = new StaticExplosion_0();
    explosion->set_v_size(width(), height());
    explosion->setPos(x(), y());
    game->add_static_item(explosion, layer);

    game->removeItem(this);
    delete this;
}