#include "customscene.h"
#include <QDebug>
//#include <QRectF>

CustomScene::CustomScene(QObject *parent): QGraphicsScene(parent)
{
}

CustomScene::~CustomScene()
{
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit mousePressed(event);
}
