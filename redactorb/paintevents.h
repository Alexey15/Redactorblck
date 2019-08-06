#ifndef PAINTEVENTS_H
#define PAINTEVENTS_H
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "actionbars.h"
#include <QMessageBox>

class paintEvents : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {Move, addArrow, addYesArrow, addNoArrow};
    explicit paintEvents(QObject *parent =0);
    ~paintEvents();
    void addPriam(int w, int h, QTextEdit *edit, int FontS);
    void addCondition(int w, int h, QTextEdit *edit, int FontS);
    void addPoch();
    void setMode(Mode newmode);
    void addKinec();
    void addDanih(int w, int h, QTextEdit *edit, int FontS);
private:
    QGraphicsItemGroup *gr;
    ActionBars *ac;
    ActionBars *con;
    ActionBars *dan;
    Mode myMode;
    QGraphicsLineItem *line;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
};

#endif // PAINTEVENTS_H
