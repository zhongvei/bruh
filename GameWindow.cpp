#include "GameWindow.h"
#include <QGraphicsRectItem>
#include "GameEntity/Block.h"
#include <cstdlib>
#include <QIcon>
#include <QPointF>
#include "Hud.h"

Basic* health_bar = new Basic();
GameWindow::GameWindow(QWidget* parent)
{
    this->setWindowTitle("TankOOP");
    //this->setWindowIcon(QIcon(R"(C:\Users\zhong\Desktop\Uni\Academic Semester\Fall 2021\COMP 2012H\Tankoop\resource\gameIcon.jpeg)"));
    scene = new QGraphicsScene();

    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* Set size of view (game window) and scene (entire map) as maximum to draw the background */

    setFixedSize(2000,2000);
    setSceneRect(0,0,2000,2000);

    /* Set the background color and draw the background grid */

    this->setStyleSheet("background:rgb(204,204,204)");
    QPen lineColor(QColor(196, 196, 196));
    for(int x = -1; x <= this->width(); x += 28){
        scene->addLine(x,0,x,this->height(),lineColor);
    }
    for(int y = -2; y <= this->height(); y += 28){
        scene->addLine(0,y,this->width(),y,lineColor);
    }

    /* reduce size of view (game window) to appropriate size */
    setFixedSize(1200,600);

    //spawn the block
    spawn_loop();

    //create and set up the tank
    basic = new Basic();
    basic->setRect(0,0,basic->get_size(),basic->get_size());
    basic->setPos(350,250);
    scene->addItem(basic);
    centerOn(QPoint(100,100));
    basic->setFlag(QGraphicsItem::ItemIsFocusable);
    basic->setFocus();

    /* Main Loop */
    loop_timer = new QTimer{this};
    connect(loop_timer, &QTimer::timeout, this, &GameWindow::main_loop);
    loop_timer->start();

    /* Health Bar Settings */
    health_bar->setRect(0,0,100,20);
    health_bar->setPos(100,200);
    scene->addItem(health_bar);

    hud = new Hud(nullptr,basic);
    scene->addWidget(hud);

    show();

}

void GameWindow::main_loop() {
    centerOn(basic);
//    basic->setFocus();
    //health bar as well
    facing_cursor(basic);
}

void GameWindow::facing_cursor(Basic* basic) {
    //calculate degrees
    QPointF cursor_position = mapToScene(QWidget::mapFromGlobal(QCursor::pos()));
    double angle_in_radians = std::atan2((cursor_position.y()-basic->y()),(cursor_position.x()-basic->x()));
    double angle_in_degrees = (angle_in_radians / M_PI) * 180;

    basic->set_degree(angle_in_degrees);
    //change tank direction
    QTransform transform;
    transform.translate(basic->get_size()/2,basic->get_size()/2);
    transform.rotate(angle_in_degrees);
    transform.translate(-(basic->get_size()/2),-(basic->get_size()/2));
    basic->setTransform(transform);

    QPointF tankpos;
    tankpos.setX(basic->x());
    tankpos.setY(basic->y());
    tankpos += QPointF(0,120);

    health_bar->setPos(tankpos);

    basic->setPos(basic->x()+basic->get_changex(),basic->y()+basic->get_changey());
//    QPointF pos = health_bar->mapToItem(basic, 0, 100);
//    health_bar->setPos(pos);
    hud->update_value();
}

void GameWindow::spawn_loop() {
    for(int i = 0; i < 10000; i++) {
        Block* block = new Block(100,100,30,0,0,10,1,0);

        block->setRect(0,0,block->get_size(),block->get_size());
        block->setPos(rand()%30000,rand()%30000);

        scene->addItem(block);
    }
}
