#include "snake.h"
#include <qDebug>
Snake::Snake()
{
}

void Snake::moveSnake(uint x, uint y, bool eat)
{
    /*Переносим хвост змеи в начало(становится головой) - создается иллюзия движения змейки.
     *Если змейка поедает яблоко, то при переносе хвоста - хвост из конца контейнера не удаляем.*/
    my_snake.push_front(QPoint(x,y));
    if (!eat){
        my_snake.pop_back();
    }
}

void Snake::restartSnake()
{
    //Очищаем контейнер и заполняем его дефолтными значениями
    my_snake.clear();
    my_snake.push_back(QPoint(60,140));
    my_snake.push_back(QPoint(40,140));
    my_snake.push_back(QPoint(20,140));
    my_snake.push_back(QPoint(0,140));
}
