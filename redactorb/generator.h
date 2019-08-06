#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QGraphicsScene>
#include <QTextEdit>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include "actionbars.h"
#include "arrow.h"

class Generator : public QTextEdit
{
    Q_OBJECT
public:
    explicit Generator(QGraphicsScene *scene,QWidget *parent = nullptr);
    void Test2();
    void startProgram();
private:
    QGraphicsScene *myScene;
    QString pochcod, kincod;
    bool kinec=false, kinecnepol=false;
    Arrow *ar2;
    ActionBars *oporaif, *oporaif2;
    int kilkistit=0;

    QString getKod(QString s);
    QString getYesArKod(QString s, QString s1);
    QString getNoArKod(QString s);
    QString getCycleString(QString s);
    bool kinecaryes=false;
    QString getGotoveIf(Arrow *ar);
    QString getGotoveIf2(Arrow *ar);
    ActionBars* getOpora(Arrow *ar);
    ActionBars* getCyclOpora(Arrow *ar);
signals:

public slots:

};

#endif // GENERATOR_H
