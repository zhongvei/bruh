#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"
#include "Block.h"
#include "Basic.h"

#include <QObject>
#include <QGraphicsRotation>
#include <QTransform>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>


class Enemy: public QObject, public QTransform, public Tank
{
    Q_OBJECT
    enum class STATE{HUNTING, RUNNING};
public:
    Enemy(double attack_range,const int& size);
    QGraphicsEllipseItem* get_attack_area(){ return attack_area; }
    QGraphicsEllipseItem* get_sight_area(){ return sight_area; }
    int get_range() const { return attack_range; }
    double get_attack_scale() const { return attack_scale; }
    double get_sight_scale() const { return sight_scale; }

    void fire();
    void detecting(QList <QGraphicsItem *> items, int &detected_blocks);

    double distanceTo(GameEntity * the_target);

    ~Enemy();

public slots:
    void move();

private:
    int num_target;

    double attack_range;
    double attack_scale;
    double sight_scale;
    bool player_detected {false};
    QPointF player_location;

    STATE current_state = STATE::HUNTING;
    QGraphicsEllipseItem *attack_area;
    QGraphicsEllipseItem *sight_area;

    void stateHunting();
    //void stateRunning(QPointF *blocks_coordinate, const int &detected_blocks);

};

#endif // ENEMY_H



