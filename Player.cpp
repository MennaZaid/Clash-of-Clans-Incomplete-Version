#include"Player.h"
#include <QObject>
#include <QKeyEvent>


Player::Player(Map1* parent) : QObject(nullptr)
{
    map = parent;
}
