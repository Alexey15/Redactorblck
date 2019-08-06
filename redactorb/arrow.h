#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include "actionbars.h"

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

//! [0]
class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 4 };
    enum Mode {DefArrow, YesArrow, NoArrow};
    Arrow(ActionBars *startItem, ActionBars *endItem, Mode mode,
      QGraphicsItem *parent = 0);

    int type() const override { return Type; }
    int getType() const { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void setColor(const QColor &color) { myColor = color; }
    ActionBars *startItem() const { return myStartItem; }
    ActionBars *endItem() const { return myEndItem; }
    int getMode() const {return myMode;}

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;

private:
    ActionBars *myStartItem;
    ActionBars *myEndItem;
    Mode myMode;
    QColor myColor;
    QPolygonF arrowHead;
};
//! [0]

#endif // ARROW_H
