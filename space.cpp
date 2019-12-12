#include "space.h"
#include <QPainter>
#include <QColor>
#include <QKeyEvent>
#include <qDebug>
#include <QMessageBox>
#include <QList>
#include <iterator>

Space::Space(QWidget *parent) : QWidget(parent)
{
    QObject::connect(this,SIGNAL(signalGlassInit()), this, SLOT(slotGlassInit()),Qt::QueuedConnection);
    emit signalGlassInit();
    omnomnom = new Snake();
    for(uint i = 0; i < m_rows;i++){
        for(uint j = 0; j < m_columns; j++){
            appleArea.push_back(QPoint(j*W,i*W));
        }
    }
}



void Space::slotGlassInit()
{
    glass.resize(m_rows);
    for(auto&x:glass){
        x.resize(m_columns);
        x.fill(emptyCell);
    }
    s.setWidth(W*m_columns);
    s.setHeight(W*m_rows);
    setFixedSize(s);
}

void Space::startGame()
{
    if(gameOn){             //Проверяем, если игра уже идет, то обнуляем текущий результат
        if(pause==true){    //Проверяем, если стоит пуза, то обнуляем текущий результат
            pause = false;
            emit changePause();
        }
        else{
           killTimer(idTimer);
        }
        omnomnom->restartSnake();//Метод класса Змеи, возвращает дефолтный размер и положение змеи на поле
    }
    gameOn = true;
    idTimer = startTimer(200);
    setApple(); //Метод, устанавливает яблоко в свободных ячейках игрового поля
    this->setFocus(); //Фокус на поле, иначе останется на кнопке "Start" и сигналы от стрелок будут игнорироваться
    direct = right; //Устанавливаем дефолтное направление для начала игры
    score = 0;
    emit setScore(score); //Выводим счет в LCDпанель
}

void Space::pauseGame()
{
    /*Метод, останавливающий игру. Проверяем, если игра идет, то ставим на паузу и передаем сигнал кнопке для её изменения с "Pause" на "Continue".
     * Если стоит пауза, то продолжаем игру и передаем сигнал кнопке для её изменения с "Continue" на "Pause".
     * Если игра не идет, то не реагируем.*/
    if(gameOn){
        if(pause==false){
            killTimer(idTimer);
            pause = true;
        }
        else{
            idTimer = startTimer(200);
            pause = false;
            this->setFocus();
        }
        emit changePause();
    }
}

void Space::stopGame()
{
    /*Метод обнуляющий игру. Проверяем, если игра идет, то обнуляем результат игры и передаем сигнал на табло для обнуления счетчика.
     * Если игра идет и стоит пауза, то обнуляем игру, меняем счет на табло и передаем сигнал кнопке для её изменения с "Continue" на "Pause".
     * Если игра не идет, то не реагируем.*/
    if(gameOn){
        if(pause==true){
            pause = false;
            emit changePause();

        }
        else {
            killTimer(idTimer);
        }
        gameOn = false;
        score = 0;
        emit setScore(score);
        omnomnom->restartSnake();
        repaint();
    }
}

void Space::paintEvent(QPaintEvent *event)
{
    //Рисуем поле
    QPainter p_pen(this);
    for(uint i = 0; i < m_rows;i++){
        for(uint j = 0; j < m_columns; j++){
            p_pen.fillRect(j*W, i*W, W,W, glass[i][j]);
        }
    }
    if(gameOn){
        p_pen.fillRect(apple.x(),apple.y(),W-1,W-1,QColor(68,145,56)); //Рисуем яблоко
        for(auto&X:omnomnom->my_snake){
            p_pen.fillRect(X.x(), X.y(), W-1, W-1, QColor(223,111,60)); //Рисуем змейку
        }
    }
}

void Space::timerEvent(QTimerEvent *event)
{
    /*Проверяем, если идет игра:
     * 1.Если голова змеи и любой участок тела(за исключением первых двух) совпадают, тоесть змея пересекает себя - игра закончена.
     * 2.Определяем текущее направление движения змеи(право, лево, верх, низ). Змея движется путем переноса последней ячейки(хвоста) в начало змеи(становится головой):
     *  a)Если змея пересекает границу поля - то перенести голову, на противоположную сторону поля.
     *  b)Если голова змеи и яблоко совпадают, то вызываем метод класса Snake, где не удаляем хвост змеи при переносе его в начало, и увеличиваем счет.*/
    if(gameOn){
        for(auto x = omnomnom->my_snake.begin()+2; x!=omnomnom->my_snake.end(); x++){
            if (omnomnom->my_snake.at(0)==*x){
                QMessageBox::information(this,"Message", "GAME OVER");
                gameOn = false;
                killTimer(idTimer);
                omnomnom->restartSnake();
                qDebug() << "А может тут";
                return;
            }
        }
        switch (direct){
        case right:
            if(omnomnom->my_snake.at(0).x()==m_columns*W-W){
                if(omnomnom->my_snake.at(0)==apple){
                    omnomnom->moveSnake(0,omnomnom->my_snake.at(0).y(), true);
                    score+=10;
                    emit setScore(score);
                    setApple();
                }
                else{
                    omnomnom->moveSnake(0,omnomnom->my_snake.at(0).y());
                }
            }
            else if(omnomnom->my_snake.at(0)==apple){
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x()+W,omnomnom->my_snake.at(0).y(), true);
                score+=10;
                emit setScore(score);
                setApple();
            }
            else{
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x()+W,omnomnom->my_snake.at(0).y());
            }
            break;
        case left:
            if(omnomnom->my_snake.at(0).x()==0){
                if(omnomnom->my_snake.at(0)==apple){
                    omnomnom->moveSnake(m_columns*W-W,omnomnom->my_snake.at(0).y(),true);
                    score+=10;
                    emit setScore(score);
                    setApple();
                }
                else{
                    omnomnom->moveSnake(m_columns*W-W,omnomnom->my_snake.at(0).y());
                }
            }
            else if(omnomnom->my_snake.at(0)==apple){
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x()-W,omnomnom->my_snake.at(0).y(), true);
                score+=10;
                emit setScore(score);
                setApple();
            }
            else{
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x()-W,omnomnom->my_snake.at(0).y());
            }
            break;
        case up:
            if(omnomnom->my_snake.at(0).y()==0){
                if(omnomnom->my_snake.at(0)==apple){
                    omnomnom->moveSnake(omnomnom->my_snake.at(0).x(),m_rows*W-W,true);
                    score+=10;
                    emit setScore(score);
                    setApple();
                }
                else {
                    omnomnom->moveSnake(omnomnom->my_snake.at(0).x(),m_rows*W-W);
                }
            }
            else if(omnomnom->my_snake.at(0)==apple){
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x(),omnomnom->my_snake.at(0).y()-W, true);
                score+=10;
                emit setScore(score);
                setApple();
            }
            else{
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x(),omnomnom->my_snake.at(0).y()-W);
            }
            break;
        case down:
            if(omnomnom->my_snake.at(0).y()==m_rows*W-W){
                if(omnomnom->my_snake.at(0)==apple){
                    omnomnom->moveSnake(omnomnom->my_snake.at(0).x(), 0, true);
                    score+=10;
                    emit setScore(score);
                    setApple();
                }
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x(), 0);
            }
            else if(omnomnom->my_snake.at(0)==apple){
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x(),omnomnom->my_snake.at(0).y()+W, true);
                score+=10;
                emit setScore(score);
                setApple();
            }
            else{
                omnomnom->moveSnake(omnomnom->my_snake.at(0).x(),omnomnom->my_snake.at(0).y()+W);
            }
            break;
        default:
            break;
        }
        repaint();
    }
}


void Space::keyPressEvent(QKeyEvent *event)
{
    /*Определяем текущее направление движения змеи.
     * Далее исключаем реакцию на движение в обратном направлении.
     * Если змея движется вверх, то можем повернуть либо вправо, либо влево. Поворот вниз исключен.*/
    if(gameOn)
    {
        switch (direct){
        case right:
            if(event->key() == Qt::Key_Up){direct = up;}
            else if(event->key() == Qt::Key_Down){direct = down;}
            break;
        case left:
            if(event->key() == Qt::Key_Up){direct = up;}
            else if(event->key() == Qt::Key_Down){direct = down;}
            break;
        case up:
            if(event->key() == Qt::Key_Left){direct = left;}
            else if(event->key() == Qt::Key_Right){direct = right;}
            break;
        case down:
            if(event->key() == Qt::Key_Left){direct = left;}
            else if(event->key() == Qt::Key_Right){direct = right;}
            break;
        default:
            break;
        }
    }
}

void Space::setApple()
{
    /*Создаем копию контейнера, содержащего все ячейки поля и исплючаем из него текущее ячейки, занятые змеей.
     *Функцией qrand - рандомно в поле, содердащем только свободные ячейки, устанавливаем яблоко.*/
   QList<QPoint> actualArea = appleArea;
   for(auto&x:omnomnom->my_snake){
       actualArea.removeAt(std::find(actualArea.begin(),actualArea.end(), x)-actualArea.begin());
   }
   apple = actualArea.at(qrand()%actualArea.size());
}
