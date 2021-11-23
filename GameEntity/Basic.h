#ifndef BASIC_H
#define BASIC_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "Tank.h"
#include "tankgraphic.h"
class Basic: public Tank
//class Basic: public Tank, public TankGraphic
//class Basic: public TankGraphic
{
    double changex = 0;
    double changey = 0;
    QGraphicsView* parent = nullptr;

    bool UP, DOWN, RIGHT, LEFT;
public:
    Basic(QGraphicsView* parent=nullptr
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level
    );
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent *event);
    void facing_cursor(Basic* basic);
//    double get_changex() const{ return changex/100; }
//    double get_changey() const{ return changey/100; }
    double get_changex() const{ return this->get_vx()*((double) RIGHT - (double) LEFT)/2; }
    double get_changey() const{ return this->get_vy()*((double) DOWN - (double) UP)/2; }

protected:
    void advance(int step) override;
};

#endif // BASIC_H
