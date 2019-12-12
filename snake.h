#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
class Snake
{
public:
    QList<QPoint> my_snake = {QPoint(60,140),QPoint(40,140),QPoint(20,140),QPoint(0,140)};
public:
    Snake();
    void moveSnake(uint, uint, bool eat = false);
    void restartSnake();
};

#endif // SNAKE_H
