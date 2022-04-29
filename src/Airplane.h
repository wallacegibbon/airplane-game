#ifndef __MY_RECT_H
#define __MY_RECT_H

#include "Bullet.h"
#include "CuteSoundPlayer.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QPainter>

class Airplane : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    // clang-format off
    enum Direction { Normal, Left, Right };
    enum Speed { Default, Fast, Slow };
    // clang-format on

public:
    Airplane(QGraphicsItem *parent = nullptr);

    qreal height() { return boundingRect().height(); }
    qreal width() { return boundingRect().width(); }

    void inc_score(int num) { score += num; }
    int get_score() { return score; }

    void move_left(int distance);
    void move_right(int distance);
    void move_up(int distance);
    void move_down(int distance);
    void backto_normal_direction();
    void backto_normal_speed();
    void shoot();
    void switch_weapon();

private:
    QString body_image_url();
    QString speed_image_url();
    void draw();
    void update_flame_cnt();
    void check_hit();

private:
    int score = 0;
    int airplane_id = 0;
    int flame_id = 0;
    int flame_cnt = 0;
    int flame_cnt_total = 3;
    int flame_offset = -16;
    Direction direction = Normal;
    Speed speed = Default;
    CuteSoundPlayer *bullet_sound = nullptr;

    BulletType bullet_type = BULLET_0;
    Bullet *active_bullet_sample;

    /* command from KeyboardController can be too frequently */
    int weapon_switch_interval = 500;
    int64_t previous_weapon_switch_time = 0;
    int64_t previous_shoot_time = 0;
};

#endif