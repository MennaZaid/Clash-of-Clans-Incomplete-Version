#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <map1.h>

class Player : public QObject {

    Q_OBJECT

    Map1* map;

public:
    explicit Player(Map1* = nullptr);
    void keyPressEvent(QKeyEvent* event);
};




#endif // PLAYER_H
