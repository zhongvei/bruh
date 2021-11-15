#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void startGame();
public slots:
    void start_button_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void startLocalGame(int nbPlayers, int nbViews);
    void setVisibleWidget(int i);

};

#endif // MAINWINDOW_H
