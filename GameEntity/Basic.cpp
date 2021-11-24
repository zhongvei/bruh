#include "Basic.h"
#include "Bullet.h"

#include <cstdlib>
#include <cmath>

#include <QKeyEvent>
#include <QPointF>
#include <QCursor>
#include <QGraphicsView>
#include <QDebug>

Basic::Basic(QGraphicsView* parent): Tank(50,1,50,100,10,10,0,0.6,0.6,50,1,0,0),
    parent(parent), UP(false), DOWN(false), RIGHT(false), LEFT(false) {
}

void Basic::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_Up:
            UP = true;
            break;
        case Qt::Key::Key_Down:
            DOWN = true;
            break;
        case Qt::Key::Key_Right:
            RIGHT = true;
            break;
        case Qt::Key::Key_Left:
            LEFT = true;
            break;
    }

    if (event->key() == Qt::Key_Space){
        /* Create a bullet */
        //qDebug() << "PEW-PEW";
        Bullet * bullet = new Bullet(this,get_damage(),0,10,get_bullet_speed(),get_bullet_speed());
        bullet->set_degree(this->get_degree());
        //bullet->setPos(x()+(this->get_size()/2),y()+(this->get_size()/2));
        bullet->setPos(x()+(this->get_size()/2*(1+cos(bullet->get_degree()/57))),y()+(this->get_size()/2*(1+sin(bullet->get_degree()/57))));

        scene()->addItem(bullet);
    }

}


double Basic::get_changex() {
    bool diagonalMovement = (double) RIGHT - (double) UP ||
         (double) UP - (double) LEFT  ||
         (double) LEFT - (double) DOWN||
         (double) DOWN - (double) RIGHT;

    double result = 0 ;
    if (this->x() > 0 && this->x() < 2000-(this->get_size())) {
        if (diagonalMovement) {
            return (this->get_vx() * ((double)RIGHT - (double)LEFT) / sqrt(2)) / 2;
        }
        else {
            return this->get_vx() * ((double)RIGHT - (double)LEFT) / 2;
        }
    }
    else if (this->x() > 0) {
        result = this->get_vx()*(-(double) LEFT)/2;
    }
    else {
        result = this->get_vx()*((double) RIGHT)/2;
    }
    return result;

    double result = 0 ;
    if (this->x() > 0 && this->x() < 2000-(this->get_size())) {
        if (diagonalMovement) {
            return (this->get_vx() * ((double)RIGHT - (double)LEFT) / sqrt(2)) / 2;
        }
        else {
            return this->get_vx() * ((double)RIGHT - (double)LEFT) / 2;
        }
    }
    else if (this->x() > 0) {
        result = this->get_vx()*(-(double) LEFT)/2;
    }
    else {
        result = this->get_vx()*((double) RIGHT)/2;
    }
    return result;
}

double Basic::get_changey() {
    bool diagonalMovement = (double) RIGHT - (double) UP ||
         (double) UP - (double) LEFT  ||
         (double) LEFT - (double) DOWN||
         (double) DOWN - (double) RIGHT;

    double result = 0 ;
    if (this->y() > 0 && this->y() < 2000-(this->get_size())) {
        if (diagonalMovement) {
            return (this->get_vy() * ((double)DOWN - (double)UP) / sqrt(2)) / 2;
        }
        else {
            return this->get_vy() * ((double)DOWN - (double)UP) / 2;
        }
    }
    else if (this->y() > 0) {
        result = this->get_vy()*(-(double) UP)/2;

    }
    else {
        result = this->get_vy()*((double) DOWN)/2;
    }
    return result;
}

void Basic::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key::Key_Up:
            UP = false;
            break;
        case Qt::Key::Key_Down:
            DOWN = false;
            break;
        case Qt::Key::Key_Right:
            RIGHT = false;
            break;
        case Qt::Key::Key_Left:
            LEFT = false;
            break;

    }

}
void Basic::advance(int step)
{
    if (!step)
        return;
    facing_cursor(this);
    check_collision();
    setFocus();

    // dont delete
//    QPainter painter(QPaintDevice);
//    //painter.setPen(QPen(Qt::black), 1);
//    painter.drawRect(this->x(), this->y(), 200,200);

    // IF THIS BASIC IS THE USER: THEN CENTER ON. ELSE, DONT CENTER ON
    parent->centerOn(this);

}

void Basic::facing_cursor(Basic* basic) {
    QPointF cursor_position = parent->mapToScene(parent->mapFromGlobal(QCursor::pos()));

    double angle_in_radians = std::atan2((cursor_position.y()-(basic->y()+basic->get_size()/2)),(cursor_position.x()-(basic->x()+basic->get_size()/2)));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;
    set_degree(angle_in_degrees);

    QTransform transform;
//    double dx = 0; double dy = 0;
//    transform.translate(dx,dy);
    transform.translate(basic->get_size()/2,basic->get_size()/2);
    transform.rotate(angle_in_degrees);
    transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
//    transform.translate(-dx,-dy);
    //basic->setTransformOriginPoint(QPoint(basic->x()+(basic->get_size()/2),basic->y()+(basic->get_size()/2)));
    basic->setTransform(transform);

    QPointF tankpos;
    tankpos.setX(basic->x());
    tankpos.setY(basic->y());
    tankpos += QPointF(0,120);

    basic->setPos(basic->x()+basic->get_changex(),basic->y()+basic->get_changey());
}
