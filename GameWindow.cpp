#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/myRect.h"
#include "GameEntity/View.h"
#include "GameEntity/Block.h"
#include <cstdlib>
#include <QIcon>
#include <QPointF>
#include <QDebug>

Basic* health_bar = new Basic();
GameWindow::GameWindow(QWidget* parent)
{
    this->setWindowTitle("TankOOP");
    //this->setWindowIcon(QIcon(R"(C:\Users\zhong\Desktop\Uni\Academic Semester\Fall 2021\COMP 2012H\Tankoop\resource\gameIcon.jpeg)"));
    scene = new QGraphicsScene();

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // set size of view (game window) and scene (entire map) as maximum to draw background
    setFixedSize(2000,2000);
    setSceneRect(0,0,2000,2000);

    // set background color and draw background grid
    this->setStyleSheet("background:rgb(204,204,204)");
    QPen lineColor(QColor(196, 196, 196));
    for(int x = -1; x <= this->width(); x += 28){
        scene->addLine(x,0,x,this->height(),lineColor);
    }
    for(int y = -2; y <= this->height(); y += 28){
        scene->addLine(0,y,this->width(),y,lineColor);
    }
    // reduce size of view (game window) to appropriate size
    setFixedSize(1200,600);

    spawn_loop();
//    MyRect* enemy = new MyRect();
//    enemy->setRect(0,0,100,100);
//    enemy->setPos(100,100);
//    scene->addItem(enemy);

    basic = new Basic();
    basic->setRect(0,0,basic->get_size(),basic->get_size());
    basic->setPos(0,0);
//    basic->setPos(350,250);
    scene->addItem(basic);

    centerOn(QPoint(100,100));
    basic->setFlag(QGraphicsItem::ItemIsFocusable);
    basic->setFocus();

    //mainloop
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    loop_timer->start(25);


    health_bar->setRect(0,0,100,20);
    health_bar->setPos(100,200);
    scene->addItem(health_bar);

    show();

}

void GameWindow::main_loop() {
//    float x = rect->x();
//    float y = rect->y();
    centerOn(basic);

    QPointF tankpos;
    tankpos.setX(basic->x());
    tankpos.setY(basic->y());
    QPointF healthpos;
    healthpos.setX(health_bar->x());
    healthpos.setY(health_bar->y());
    //qDebug() << basic->mapFromScene(healthpos);
    health_bar->setPos(healthpos + QPointF(0,120) - basic->mapFromScene(healthpos) );
}

void GameWindow::spawn_loop() {
    for(int i = 0; i < 10000; i++) {
        Block* block = new Block(100,100,30,0,0,1,1,0);
        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(rand()%1000000,rand()%1000000);
        scene->addItem(block);
    }
}
