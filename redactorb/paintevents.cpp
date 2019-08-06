#include "paintevents.h"
#include "arrow.h"
paintEvents::paintEvents(QObject *parent) : QGraphicsScene(parent)
{
    gr = new QGraphicsItemGroup();
    myMode=paintEvents::Move;
    line=0;
}
paintEvents::~paintEvents(){

}

void paintEvents::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    switch (myMode) {
        case addArrow:{
            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(Qt::black, 1));
            addItem(line);
            break;
            }
    case addYesArrow:
    {
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                    mouseEvent->scenePos()));
        line->setPen(QPen(Qt::black, 1));
        addItem(line);
        break;
    }
    case addNoArrow:{
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                    mouseEvent->scenePos()));
        line->setPen(QPen(Qt::black, 1));
        addItem(line);
        break;
    }
    case Move:{
        break;
    }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void paintEvents::addPriam(int w, int h, QTextEdit *edit, int FontS){
    ac = new ActionBars(ActionBars::Priam, w, h, edit, FontS);
    ac->setFlag(QGraphicsItem::ItemIsMovable, true);
    ac->setFlag(QGraphicsItem::ItemIsSelectable, true);
    addItem(ac);
}
void paintEvents::addCondition(int w, int h, QTextEdit *edit, int FontS){
    con = new ActionBars(ActionBars::Conditions, w, h, edit, FontS);
    con->setFlag(QGraphicsItem::ItemIsMovable, true);
    con->setFlag(QGraphicsItem::ItemIsSelectable, true);
    addItem(con);
}
void paintEvents::addPoch(){
    ActionBars *next = new ActionBars(ActionBars::poch, 20, 150, new QTextEdit(), 12);
    next->setFlag(QGraphicsItem::ItemIsMovable, true);
    next->setFlag(QGraphicsItem::ItemIsSelectable, true);
    addItem(next);
}
void paintEvents::addDanih(int w, int h, QTextEdit *edit, int FontS){
    dan = new ActionBars(ActionBars::danih, w, h, edit, FontS);
    dan->setFlag(QGraphicsItem::ItemIsMovable, true);
    dan->setFlag(QGraphicsItem::ItemIsSelectable, true);
    addItem(dan);
}
void paintEvents::addKinec(){
    ActionBars *kin = new ActionBars(ActionBars::kinec, 20, 150, new QTextEdit(), 12);
    kin->setFlag(QGraphicsItem::ItemIsMovable, true);
    kin->setFlag(QGraphicsItem::ItemIsSelectable, true);
    addItem(kin);
}
void paintEvents::setMode(Mode newmode){
    myMode=newmode;
}

void paintEvents::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == addArrow && line!=0) {
        line->setPen(QPen(Qt::black, 2));
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
        if (items(line->line().p1()).last()->type()==ActionBars::Type){
        QList<QGraphicsItem *> startItems = items(line->line().p1());

        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        if (qgraphicsitem_cast<ActionBars *>(startItems.first())->getDiagramType()==ActionBars::kinec){
            line->setPen(QPen(Qt::red, 2));
        }
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.last()->type()==ActionBars::Type){
           if (qgraphicsitem_cast<ActionBars *>(endItems.last())->getDiagramType()==ActionBars::poch){
               line->setPen(QPen(Qt::red, 2));
           } else if (qgraphicsitem_cast<ActionBars *>(startItems.first())->getKinArrows().count()>0){
               line->setPen(QPen(Qt::red, 2));
           }
        }
        }
    } else if(myMode == addYesArrow && line!=0){
        line->setPen(QPen(Qt::black, 2));
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
        if (items(line->line().p1()).last()->type()==ActionBars::Type){
        QList<QGraphicsItem *> startItems = items(line->line().p1());

        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        if (!(qgraphicsitem_cast<ActionBars *>(startItems.first())->getDiagramType()==ActionBars::Conditions)){
            line->setPen(QPen(Qt::red, 2));
        }
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.last()->type()==ActionBars::Type){
           if (qgraphicsitem_cast<ActionBars *>(endItems.last())->getDiagramType()==ActionBars::poch){
               line->setPen(QPen(Qt::red, 2));
            }
        }
        }
    } else if(myMode == addNoArrow && line!=0){
        line->setPen(QPen(Qt::black, 2));
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
        if (items(line->line().p1()).last()->type()==ActionBars::Type){
        QList<QGraphicsItem *> startItems = items(line->line().p1());

        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        if (!(qgraphicsitem_cast<ActionBars *>(startItems.first())->getDiagramType()==ActionBars::Conditions)){
            line->setPen(QPen(Qt::red, 2));
        }
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.last()->type()==ActionBars::Type){
           if (qgraphicsitem_cast<ActionBars *>(endItems.last())->getDiagramType()==ActionBars::poch){
               line->setPen(QPen(Qt::red, 2));
            }
        }
        }
    } else{
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void paintEvents::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == addArrow) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == ActionBars::Type &&
                endItems.first()->type() == ActionBars::Type &&
                startItems.first() != endItems.first()) {
            ActionBars *startItem = qgraphicsitem_cast<ActionBars *>(startItems.first());
            ActionBars *endItem = qgraphicsitem_cast<ActionBars *>(endItems.first());
            if (startItem->getDiagramType()==ActionBars::kinec){
                QMessageBox *msg = new QMessageBox;
                msg->setText("Помилка:");
                msg->setInformativeText("Лінія не може починатися кінцем!");
                msg->exec();
            } else if (endItem->getDiagramType()==ActionBars::poch){
                QMessageBox *msg = new QMessageBox;
                msg->setText("Помилка:");
                msg->setInformativeText("Лінія не може кінчатися початком!");
                msg->exec();
            } else if(startItem->getKinArrows().count()>0){
                QMessageBox *msg = new QMessageBox;
                msg->setText("Помилка:");
                msg->setInformativeText("Не може бути більше 1-ї ліній з одного елементу!");
                msg->exec();
            } else {
            Arrow *arrow = new Arrow(startItem, endItem, Arrow::DefArrow);
            arrow->setColor(Qt::black);
            startItem->addKinArrow(arrow);
            endItem->addPochArrow(arrow);
            addItem(arrow);
            arrow->updatePosition();
            }
        }
    } else if (line != 0 && myMode == addYesArrow){
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == ActionBars::Type &&
                endItems.first()->type() == ActionBars::Type &&
                startItems.first() != endItems.first()) {
            ActionBars *startItem = qgraphicsitem_cast<ActionBars *>(startItems.first());
            ActionBars *endItem = qgraphicsitem_cast<ActionBars *>(endItems.first());
            if (!(startItem->getDiagramType()==ActionBars::Conditions)){
                QMessageBox *msg = new QMessageBox;
                msg->setText("Помилка:");
                msg->setInformativeText("Лінія 'Так' не може починатися не з блоку умови!");
                msg->exec();
            } else if (endItem->getDiagramType()==ActionBars::poch){
                QMessageBox *msg = new QMessageBox;
                msg->setText("Помилка:");
                msg->setInformativeText("Лінія не може кінчатися початком!");
                msg->exec();
            } else {
            Arrow *arrow = new Arrow(startItem, endItem, Arrow::YesArrow);
            arrow->setColor(Qt::black);
            startItem->addKinArrow(arrow);
            endItem->addPochArrow(arrow);
            addItem(arrow);
            arrow->updatePosition();
            }
        }
    } else if(line != 0 && myMode == addNoArrow){
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == ActionBars::Type &&
                endItems.first()->type() == ActionBars::Type &&
                startItems.first() != endItems.first()) {
            ActionBars *startItem = qgraphicsitem_cast<ActionBars *>(startItems.first());
            ActionBars *endItem = qgraphicsitem_cast<ActionBars *>(endItems.first());
            if (!(startItem->getDiagramType()==ActionBars::Conditions)){
                QMessageBox *msg = new QMessageBox;
                msg->setText("Помилка:");
                msg->setInformativeText("Лінія 'Ні' не може починатися не з блоку умови!");
                msg->exec();
            } else if (endItem->getDiagramType()==ActionBars::poch){
                QMessageBox *msg = new QMessageBox;
                msg->setText("Помилка:");
                msg->setInformativeText("Лінія не може кінчатися початком!");
                msg->exec();
            } else {
            Arrow *arrow = new Arrow(startItem, endItem, Arrow::NoArrow);
            arrow->setColor(Qt::black);
            startItem->addKinArrow(arrow);
            endItem->addPochArrow(arrow);
            addItem(arrow);
            arrow->updatePosition();
            }
        }
    }
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

