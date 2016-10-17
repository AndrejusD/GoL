#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H


#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
private:

public:
    explicit CustomScene(QObject *parent = 0);
    virtual ~CustomScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    //void resizeEvent (QResizeEvent * event);

signals:
    void mousePressed(QGraphicsSceneMouseEvent *event);

};

#endif // CUSTOMSCENE_H
