#include "Bullet.h"
#include "Block.h"
#include "Enemy.h"
#include "Basic.h"
#include "Wall.h"
#include "Turret.h"

#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

//bullet has no health, max health, health_regen and xp
Bullet::Bullet(Tank* tank, const double& damage, const double& degree, const int& size, const double& vx, const double& vy):
    GameEntity(0,0,0,size,vx,vy,0,0), damage(damage), degree(degree), tank(tank)
{
    setRect(0,0,size,size);
    QTimer* timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(1000/60);
}

GameEntity::CATEGORY Bullet::get_category() const {return GameEntity::CATEGORY::BULLET;}

double Bullet::get_damage() const { return damage; }
Tank* Bullet::get_tank() const {return tank;}

void Bullet::move(){
        QList<QGraphicsItem *> colliding_items = collidingItems();
            for (int i = 0, n = colliding_items.size(); i < n; ++i){
                GameEntity* the_thing =  dynamic_cast<GameEntity*>(colliding_items[i]);
                if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::BLOCK && tank->get_class() == GameEntity::CLASS::TURRET){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Block *the_block = dynamic_cast<Block*>(colliding_items[i]);
                    the_block->set_health(the_block->get_health()-get_damage());

                    /* Delete the Block if the heath is less than or equal to zero */
                    if(the_block->get_health() <= 0){
                       Turret* the_turret = dynamic_cast<Turret*>(tank);
                       the_turret->get_creator()->set_xp(the_turret->get_creator()->get_xp()+the_block->get_xp());
                       delete colliding_items[i];
                    }

                    /* Deleting both the Bullet */
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::ENEMY && this->tank->get_class() == GameEntity::CLASS::TURRET){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Enemy *the_enemy = dynamic_cast<Enemy*>(colliding_items[i]);
                    Turret* the_turret = dynamic_cast<Turret*>(tank);
                    the_enemy->set_health(the_enemy->get_health()-get_damage());

                    /* Delete the Enemy if its health is less than or equal to zero */
                    if(the_enemy->get_health() <= 0){
                       the_turret->get_creator()->set_xp(the_turret->get_creator()->get_xp()+the_enemy->get_xp());
                       delete the_enemy;
                    }

                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::BLOCK){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Block *the_block = dynamic_cast<Block*>(colliding_items[i]);
                    the_block->set_health(the_block->get_health()-get_damage());
                    /* Delete the Block if the heath is less than or equal to zero */
                    if(the_block->get_health() <= 0){
                       tank->set_xp(tank->get_xp()+the_block->get_xp());
                       delete colliding_items[i];
                    }

                    /* Deleting both the Bullet */
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::ENEMY && tank->get_class() == GameEntity::CLASS::BASIC){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Enemy *the_enemy = dynamic_cast<Enemy*>(colliding_items[i]);
                    the_enemy->set_health(the_enemy->get_health()-get_damage());

                    /* Delete the Enemy if its health is less than or equal to zero */
                    if(the_enemy->get_health() <= 0){
                       tank->set_xp(tank->get_xp()+the_enemy->get_xp());
                       delete colliding_items[i];
                    }

                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
                else if (the_thing != nullptr && the_thing->get_class() == GameEntity::CLASS::BASIC && this->tank->get_class() == GameEntity::CLASS::ENEMY){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Basic *player = dynamic_cast<Basic*>(colliding_items[i]);
                    player->set_health(player->get_health()-get_damage());
                    // qDebug()<<"HIT THE PLAYER";
                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                } else if (the_thing != nullptr && the_thing->get_category() == GameEntity::CATEGORY::WALL && tank->get_class() == GameEntity::CLASS::ENEMY){
                    /* Removing both the bullet and the block from the screen when colliding */
                    Wall* the_wall = dynamic_cast<Wall*>(colliding_items[i]);
                    the_wall->set_health(the_wall->get_health()-get_damage());

                    /* Delete the Enemy if its health is less than or equal to zero */
                    if(the_wall->get_health() <= 0){
                       scene()->removeItem(colliding_items[i]);
                       delete colliding_items[i];
                    }

                    /* Deleting both the Bullet */
                    scene()->removeItem(this);
                    delete this;
                    return;
                }
            }

            /* Set The Movement of the Bullet */
            setPos(x()+(this->get_vx()*10*cos(this->degree/57)),y()+(this->get_vy()*10*sin(this->degree/57)));
            if (pos().y() + rect().height() < 0){
                qDebug() << "DELETED A BULLET";
                scene()->removeItem(this);
                delete this;
                return;
            }
            if (pos().x() + rect().height() < 0){
                qDebug() << "DELETED A BULLET";
                scene()->removeItem(this);
                delete this;
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(Enemy) && typeid(*tank) == typeid(Basic)){
                /* Removing both the bullet and the block from the screen when colliding */
                Enemy *the_enemy = dynamic_cast<Enemy*>(colliding_items[i]);
                the_enemy->set_health(the_enemy->get_health()-get_damage());

                /* Delete the Enemy if its health is less than or equal to zero */
                if(the_enemy->get_health() <= 0){
                   scene()->removeItem(colliding_items[i]);
                   scene()->removeItem(the_enemy->get_health_bar());
                   tank->set_xp(tank->get_xp()+the_enemy->get_xp());
                   delete colliding_items[i];
                   colliding_items[i] = nullptr;
                }

                /* Deleting both the Bullet */
                scene()->removeItem(this);
                delete this;
                return;
            }
            else if (typeid(*(colliding_items[i])) == typeid(Basic) && typeid(*tank) == typeid(Enemy)){
                /* Removing both the bullet and the block from the screen when colliding */
                Basic *player = dynamic_cast<Basic*>(colliding_items[i]);
                player->set_health(player->get_health()-get_damage());

                /* Deleting both the Bullet */
                scene()->removeItem(this);
                delete this;
                return;
            }

        }

        /* Set The Movement of the Bullet */
        setPos(x()+(this->get_vx()*10*cos(this->degree/57)),y()+(this->get_vy()*10*sin(this->degree/57)));
        if (pos().y() + rect().height() < 0){
            scene()->removeItem(this);
            delete this;
            return;
        }
        if (pos().x() + rect().height() < 0){
            scene()->removeItem(this);
            delete this;
            return;
        }
        if (pos().y() + rect().height() > 2000){
            scene()->removeItem(this);
            delete this;
            return;
        }
        if (pos().x() + rect().height() > 2000){
            scene()->removeItem(this);
            delete this;
            return;
        }
}
