#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Block.h"

//bullet has no health, max health, health_regen and xp
Bullet::Bullet(Tank& tank, const double& damage,const int& size, const int& vx, const int& vy): tank(tank), damage(damage),GameEntity(0,0,0,size,vx,vy,0,0)
{
    setRect(0,0,10,10);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

double Bullet::get_damage() const { return damage; }

void Bullet::move(){
    QList<QGraphicsItem *> colliding_items = collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Block)){
                /* Removing both the bullet and the block from the screen when colliding */
                Block *the_block = dynamic_cast<Block*>(colliding_items[i]);
                the_block->set_health(the_block->get_health()-get_damage());

                /* Delete the Block if the heath is less than or equal to zero */
                if(the_block->get_health() <= 0){
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
        setPos(x(),y()-10);
        if (pos().y() + rect().height() < 0){
            scene()->removeItem(this);
            delete this;
        }
}
