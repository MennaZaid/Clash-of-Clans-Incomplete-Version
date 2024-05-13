#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "node.h"
#include <QHash>

class PathFinder
{
public:
    Node* GetLowestfCostNode(QList<Node*>);

    int CalculateDistance(QPoint, QPoint);

    void ConstructPath(Node*);

    QList<Node*> GetNeighbours(Node*, QPoint, QPoint, QHash<QPoint, Node*>);

    QList<Node*> path;
    PathFinder(QPoint, QPoint, QHash<QPoint, Node*>);
};

#endif // PATHFINDER_H
