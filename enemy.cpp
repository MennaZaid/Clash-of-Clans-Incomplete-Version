#include "enemy.h"
#include <QMessageBox>
#include <QGraphicsScene>
#include<cstdlib>
//s
#include"map.h"
//e

float dotProduct(QPointF a, QPointF b)
{
    return a.x() * b.x() + a.y() * b.y();
}

QPointF lerp(QPointF a, QPointF b, float t)
{
    return (1-t) * a + t * b;
}

float inverseLerp(QPointF a, QPointF b, QPointF v)
{
    QPointF ab = b - a;
    QPointF av = v - a;

    float nominator = dotProduct(ab, av);
    float denominator = dotProduct(ab, ab);
    return (nominator / denominator); // Or you can do it by components (i.e ab.y / av.y
    //  but I like this because it looks more elegant
}

Enemy::Enemy(QPoint coords, QPixmap pixMap) : QObject(nullptr), QGraphicsPixmapItem(nullptr)
{
    setPixmap(pixMap);
    setPos(coords * 100);
}
void Enemy::processPath(QList<Node*> path)
{
    this->currentPath = path;
    currentNodeIndex = 0;
    if (currentNodeIndex != 0) qDebug() << currentNodeIndex;
    currentTimer = new QTimer();
    connect(currentTimer,SIGNAL(timeout()), this, SLOT(moveOnPath()));
    currentTimer->start(10);
}

void Enemy::moveOnPath()
{
    Node* currentNode = currentPath[currentNodeIndex];

    //Here we have an obstacle, it will not move foward unless the obstacle is cleared
    //cannon Node is always unwalkable, meaning it will never be in a path and will be ignored by enemy
    if (currentNode->building != nullptr)
    {
        currentNode->building->TakeDamage();
        if (currentNode->building->CurrentHitPoints() <= 0)
        {
            delete currentNode->building;
            currentNode->building = nullptr;
        }
        return;
    }

    //All paths eventually lead to the castle, they are always the shortest path as well.
    //So the last node in the path is always the castle
    if (currentNodeIndex == currentPath.count() - 1)
    {
        //If we pass the condition, this that we are at the last node, which is castle, and it also means it is destroyed.
        disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(moveOnPath()));
        delete currentTimer;
        qDebug() << "you lost!";
        QMessageBox::information(nullptr, "info", "YOU LOST THE GAME!!");
        exit(0);


        return;
    }

    Node* nextNode = currentPath[currentNodeIndex + 1];

    //This is needed to find where the enemy is its path between 2 nodes
    float currentValue = inverseLerp(QPointF(currentNode->coords) * 100, QPointF(nextNode->coords) * 100, pos());
    //This is the new position, plus a small increment to make it actually move
    QPointF newPoint = lerp(QPointF(currentNode->coords) * 100, QPointF(nextNode->coords) * 100, currentValue + 0.005);
    setPos(newPoint);

    if (currentValue >= 1)
    {
        currentNodeIndex++;
    }
}

//s
void Enemy::DamageBuilding()
{
    /*Node* node = currentPath.last();
    node->building->TakeDamage();
    
    
    
        if (!isCastlePath)
        {
        if (node->building->CurrentHitPoints() < 0)
            disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(DamageBuilding()));
            delete currentTimer;
            delete node->building;
            emit needNewPath();
        }
        else
        {
            disconnect(currentTimer, SIGNAL(timeout()), this, SLOT(DamageBuilding()));
            
            delete currentTimer;
            delete node->building;
            QMessageBox::information(nullptr, "info", "YOU LOST THE GAME!!");
            
        }*/
    
}

//e


