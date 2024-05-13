#include "pathfinder.h"
#include "math.h"
#include <QList>
#include <QPoint>
#include <QMessageBox>


PathFinder::PathFinder(QPoint start, QPoint end, QHash<QPoint, Node*> grid)
{
    int minX = 0;
    int minY = 0;
    int maxX = 8;
    int maxY = 8;


    for (int i = minX; i <= maxX; i++)
    {
        for (int j = minY; j <= maxY; j++)
        {
            Node* node = grid.value(QPoint(i, j));
            node->connectedTo = nullptr;
            node->gCost = INT32_MAX;
        }
    }

    QPoint min = QPoint(minX, minY);
    QPoint max = QPoint(maxX, maxY);
    QList<Node*> openList;
    QList<Node*> closedList;
    Node* startNode = grid[start];



    startNode->gCost = 0;
    startNode->hCost = CalculateDistance(start, end);

    openList.push_back(startNode);
    while(openList.count() > 0)
    {
        Node* lowestfCostNode = GetLowestfCostNode(openList);
        for (int i = 0; i < openList.count(); i++)
        {
            if (lowestfCostNode == openList.at(i))
            {
                openList.removeAt(i);
            }
        }
        closedList.push_back(lowestfCostNode);


        if (lowestfCostNode->coords.x() == end.x() && lowestfCostNode->coords.y() == end.y())
        {
            ConstructPath(lowestfCostNode);
            return;
        }

        QList<Node*> neighbours = GetNeighbours(lowestfCostNode, min, max, grid);

        foreach(Node* neighbour, neighbours)
        {
            if(closedList.contains(neighbour) || !neighbour->isWalkable) continue;

            int tentativegCost = lowestfCostNode->gCost + CalculateDistance(lowestfCostNode->coords, neighbour->coords);
            if (tentativegCost < neighbour->gCost || !openList.contains(neighbour))
            {
                neighbour->gCost = tentativegCost;
                neighbour->hCost = CalculateDistance(neighbour->coords, end);
                neighbour->connectedTo = lowestfCostNode;

                if (!openList.contains(neighbour)) openList.push_back(neighbour);
            }
        }
    }
}

int PathFinder::CalculateDistance(QPoint a, QPoint b)
{
    int dstX = abs(a.x() - b.x());
    int dstY = abs(a.y() - b.y());

    return fmin(dstX, dstY) * 14 + 10 * abs(dstX - dstY);
}

Node* PathFinder::GetLowestfCostNode(QList<Node*> list)
{
    Node* leastfCostNode = list.at(0);
    for (int i = 1; i < list.count(); i++)
    {
        Node* currentNode = list.at(i);
        if (currentNode->getfCost() < leastfCostNode->getfCost() || (currentNode->getfCost() == leastfCostNode->getfCost() && currentNode->hCost < leastfCostNode->hCost))
        {
            leastfCostNode = currentNode;
        }
    }

    return leastfCostNode;
}

void PathFinder::ConstructPath(Node* end)
{
    QList<Node*> pathReversed;
    pathReversed.push_back(end);

    Node* currentNode = end;
    while(currentNode->connectedTo != nullptr)
    {
        pathReversed.push_back(currentNode->connectedTo);
        currentNode = currentNode->connectedTo;
    }
    for (int i = pathReversed.count() - 1; i >= 0; i--)
    {
        path.push_back(pathReversed.at(i));
    }
}

QList<Node*> PathFinder::GetNeighbours(Node* node, QPoint min, QPoint max, QHash<QPoint, Node*> grid)
{
    QList<Node*> neighbours;
    neighbours.clear();
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0) continue;
            QPoint neighbourCoords = node->coords + QPoint(i, j);
            if (neighbourCoords.x() >= min.x() && neighbourCoords.y() >= min.y() && neighbourCoords.x() <= max.x() && neighbourCoords.y() <= max.y())
            {
                Node* neighbour = grid[neighbourCoords];
                neighbours.push_back(neighbour);
            }
        }
    }

    return neighbours;
}
