#include "arrow.h"

#include <math.h>

#include <QPen>
#include <QPainter>

const qreal Pi = 3.14;

Arrow::Arrow(ActionBars *startItem, ActionBars *endItem, Mode mode, QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    myMode=mode;
    myStartItem = startItem;
    myEndItem = endItem;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void Arrow::updatePosition()
{
    QLineF line(mapFromItem(myStartItem, 0, 0), mapFromItem(myEndItem, 0, 0));
    setLine(line);
    update();
}

void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
          QWidget *)
{
    if (myStartItem->collidesWithItem(myEndItem))
      return;

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 10;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QPointF p = myEndItem->pos();
    QPointF p1 = myStartItem->pos();
    switch (myMode) {
    case DefArrow:
    {
        if (myEndItem->getDiagramType()==ActionBars::Conditions){
            p.setY(myEndItem->pos().y()-myEndItem->getHeight()/2);
        } else if (myEndItem->getDiagramType()==ActionBars::poch || myEndItem->getDiagramType()==ActionBars::kinec){
            p.setX(myEndItem->pos().x()+myEndItem->getHeight()/1.8);
        } else if (myEndItem->getDiagramType()==ActionBars::Priam){
            p.setX(myEndItem->pos().x()+myEndItem->getWidth()/2);
        } else if (myEndItem->getDiagramType()==ActionBars::danih){
            p.setX(myEndItem->pos().x()+myEndItem->getWidth()*2);
        }
        if (myStartItem->getDiagramType()==ActionBars::poch || myStartItem->getDiagramType()==ActionBars::kinec){
            p1.setY(myStartItem->pos().y()+72);
            p1.setX(myStartItem->pos().x()+myStartItem->getHeight()/1.8);
        } else if (myStartItem->getDiagramType()==ActionBars::Priam){
            p1.setX(myStartItem->pos().x()+myStartItem->getWidth()/2);
            p1.setY(myStartItem->pos().y()+(myStartItem->getHeight()/2)+2);
        } else if (myStartItem->getDiagramType()==ActionBars::danih){
            p1.setX(myStartItem->pos().x()+myStartItem->getWidth()*2);
            p1.setY(myStartItem->pos().y()+myStartItem->getHeight());
        }
        break;
    }
    case YesArrow:
    {
        if (myStartItem->getDiagramType()==ActionBars::Conditions){
            p1.setX(myStartItem->pos().x()-myStartItem->getWidth()/2);
        }
        if (myEndItem->getDiagramType()==ActionBars::Conditions){
            p.setY(myEndItem->pos().y()-myEndItem->getHeight()/2);
        } else if (myEndItem->getDiagramType()==ActionBars::poch || myEndItem->getDiagramType()==ActionBars::kinec){
            p.setX(myEndItem->pos().x()+myEndItem->getHeight()/1.8);
        } else if (myEndItem->getDiagramType()==ActionBars::Priam){
            p.setX(myEndItem->pos().x()+myEndItem->getWidth()/2);
        } else if (myEndItem->getDiagramType()==ActionBars::danih){
            p.setX(myEndItem->pos().x()+myEndItem->getWidth()*2);
        }
        break;
    }
    case NoArrow:
    {
        if (myStartItem->getDiagramType()==ActionBars::Conditions){
            p1.setX(myStartItem->pos().x()+myStartItem->getWidth()/2);
        }
        if (myEndItem->getDiagramType()==ActionBars::Conditions){
            p.setY(myEndItem->pos().y()-myEndItem->getHeight()/2);
        } else if (myEndItem->getDiagramType()==ActionBars::poch || myEndItem->getDiagramType()==ActionBars::kinec){
            p.setX(myEndItem->pos().x()+myEndItem->getHeight()/1.8);
        } else if (myEndItem->getDiagramType()==ActionBars::Priam){
            p.setX(myEndItem->pos().x()+myEndItem->getWidth()/2);
        } else if (myEndItem->getDiagramType()==ActionBars::danih){
            p.setX(myEndItem->pos().x()+myEndItem->getWidth()*2);
        }
        break;
    }
    }

    setLine(QLineF(p, p1));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                    cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                    cos(angle + Pi - Pi / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (myMode==YesArrow){
        painter->setFont(QFont("Arial", 13));
        painter->drawText(Arrow::boundingRect(), Qt::AlignCenter, "Так");
    } else if (myMode==NoArrow){
        painter->setFont(QFont("Arial", 13));
        painter->drawText(Arrow::boundingRect(), Qt::AlignCenter, "Ні");
    }
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }
}
