 #ifndef BASIC_H
#define BASIC_H

#include "Tank.h"
#include "../GameEngine.h"

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsRotation>
#include <QTransform>

class GameEngine;

class Basic: public Tank, public QGraphicsRotation, public QTransform
{
private:
    double changex = 0;
    double changey = 0;

    int skill_cooldown;
    bool cooldown_status;

    bool UP, DOWN, RIGHT, LEFT;

    QGraphicsView* parent = nullptr;
    GameEngine* const game_engine;

public:

    Basic(QGraphicsView* parent=nullptr, GameEngine* const game_engine=nullptr,
          const double& health = 300, const double& health_regen = 1, const double& max_health = 300,
          const int& size = 100, const double& vx = 10, const double& vy = 10,const double& xp = 0,
          const double& reload_speed = 0.8,
          const double& bullet_speed = 0.6,
          const double& damage = 50,
          const int& level = 1,
          const int& skill_point = 0,
          const int& degree = 0
    );

    Basic(const Basic &basic, QGraphicsView *parent = nullptr, GameEngine* const game_engine=nullptr);

    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void facing_cursor(Basic* basic);

    double get_changex();
    double get_changey();

    void set_parent(QGraphicsView* window){parent = window;}

    GameEntity::CLASS get_class() const override;

protected:
    void advance(int step) override;

};

#endif // BASIC_H
