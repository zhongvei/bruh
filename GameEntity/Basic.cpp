#include "Basic.h"
#include <QKeyEvent>
#include "Bullet.h"
#include <QGraphicsScene>
#include <QDebug>

Basic::Basic(
        // const double& health, const double& health_regen, const double& max_health, 
        // const int& size, const int& vx, const int& vy,const double& xp,
        // const double& attack_speed,
        // const double& bullet_speed,
        // const double& damage,
        // const int& level
        ): Tank(50,1,50,100,10,10,0,0.6,0.6,7,1,0) {}

void Basic::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Left && (get_pressed_key_x() == KEY::NONE || get_pressed_key_x() != KEY::LEFT)){
        qDebug() << "LEFT";
        if(get_pressed_key_x() == KEY::NONE){
            set_released_key_x(KEY::LEFT);
        }
        set_pressed_key_x(KEY::LEFT);
        changex += -this->get_vx();

    }
    if (event->key() == Qt::Key_Right && (get_pressed_key_x() == KEY::NONE || get_pressed_key_x() != KEY::RIGHT)){
        qDebug() << "RIGHT";
        if(get_pressed_key_x() == KEY::NONE){
            set_released_key_x(KEY::RIGHT);
        }
        set_pressed_key_x(KEY::RIGHT);
        changex += this->get_vx();
\
    }
    if (event->key() == Qt::Key_Up && (get_pressed_key_y() == KEY::NONE || get_pressed_key_y() != KEY::UP)){
        if(get_pressed_key_y() == KEY::NONE){
            set_released_key_y(KEY::UP);
        }
        set_pressed_key_y(KEY::UP);
        changey += -this->get_vx();

    }
    if (event->key() == Qt::Key_Down && (get_pressed_key_y() == KEY::NONE || get_pressed_key_y() != KEY::DOWN)){
        if(get_pressed_key_y() == KEY::NONE){
            set_released_key_y(KEY::DOWN);
        }
        set_pressed_key_y(KEY::DOWN);
        changey += this->get_vx();

    }

    if (event->key() == Qt::Key_Space){
        /* Create a bullet */
        qDebug() << "ASJHBDHKBJASDJKHBBHKJ";
        Bullet * bullet = new Bullet(*this,50,0,0,0);
        bullet->setPos(x()+20,y()-10);
        scene()->addItem(bullet);
    }

    //setPos(x()+changex,y()+changey);
}

void Basic::keyReleaseEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        if(get_released_key_x() == KEY::RIGHT){
            set_pressed_key_x(KEY::RIGHT);
        }
        else if(get_released_key_x() == KEY::LEFT && get_pressed_key_x() == KEY::RIGHT){
            set_pressed_key_x(KEY::RIGHT);
            set_released_key_x(KEY::RIGHT);
        }
        else{
            set_pressed_key_x(KEY::NONE);
        }
        changex += this->get_vx();

    }
    if (event->key() == Qt::Key_Right){
        if(get_released_key_x() == KEY::LEFT){
            set_pressed_key_x(KEY::LEFT);
        }
        else if(get_released_key_x() == KEY::RIGHT && get_pressed_key_x() == KEY::LEFT){
            set_pressed_key_x(KEY::LEFT);
            set_released_key_x(KEY::LEFT);
        }
        else{
            set_pressed_key_x(KEY::NONE);
        }
        changex += -this->get_vx();
\
    }
    if (event->key() == Qt::Key_Up){
        if(get_released_key_y() == KEY::DOWN){
            set_pressed_key_y(KEY::DOWN);
        }
        else if(get_released_key_y() == KEY::UP && get_pressed_key_y() == KEY::DOWN){
            set_pressed_key_y(KEY::DOWN);
            set_released_key_y(KEY::DOWN);
        }
        else{
            set_pressed_key_y(KEY::NONE);
        }
        changey += this->get_vx();

    }
    if (event->key() == Qt::Key_Down){
        if(get_released_key_y() == KEY::UP){
            set_pressed_key_y(KEY::UP);
        }
        else if(get_released_key_y() == KEY::DOWN && get_pressed_key_y() == KEY::UP){
            set_pressed_key_y(KEY::UP);
            set_released_key_y(KEY::UP);
        }
        else{
            set_pressed_key_y(KEY::NONE);
        }
        changey += -this->get_vx();

    }
}
