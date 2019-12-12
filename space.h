#ifndef SPACE_H
#define SPACE_H
#define emptyCell QColor(47,60,78)

#include <QWidget>
#include <QList>
#include <QVector>
#include <QColor>
#include "snake.h"

static const uint W=20;
/*Класс "Пространство", содержит информацию об игровом поле(размер, цвет) и местонахождении "Яблока".
 * Отвечает за игру, и прорисовывает результат движения змеи.*/

class Space : public QWidget
{
    Q_OBJECT
    QVector<QVector<QColor>> glass;
    uint m_rows = 15;//Строки поля шириной 20 пикселей
    uint m_columns = 22;//Столбцы поля шириной 20 пикселей
    bool gameOn = false;
    uint idTimer;
    Snake* omnomnom;
    QSize s;
    enum direction{up,down,left,right} direct = right;//Направление движения змейки
    QPoint apple;//Расположение яблока
    QList<QPoint> appleArea;//контейнер заполнен незанятыми ячейками поля, для рандомного расположения яблока
    int score = 0;
    bool pause = false;
    friend class Snake;

    void setApple();

public slots:
    void slotGlassInit();
    void startGame();
    void pauseGame();
    void stopGame();

signals:
    void signalGlassInit();
    void changePause();
    void setScore(int);

public:
    explicit Space(QWidget *parent = nullptr);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
};

#endif // SPACE_H
