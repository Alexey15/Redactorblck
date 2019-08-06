#ifndef ACTIONBARS_H
#define ACTIONBARS_H

#include <QObject>
#include <QGraphicsItem>
#include <QTextEdit>
#include <QPainter>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class Arrow;

class ActionBars : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 15 };
    enum DiagramType {Priam, Conditions, poch, danih, kinec};
    explicit ActionBars(DiagramType dt,int width, int height, QTextEdit *edit, int FontS, QObject *parent = 0);
    void setWidth(int w);
    void setHeight(int h);
    void setFontSize(int size);
    void setNewTextEdit(QTextEdit *newst);
    void setPenWidth(int w);
    void removePochArrow(Arrow *arrow);
    void removeKinArrow(Arrow *arrow);
    int getWidth() {return my_width;}
    QList<Arrow*> getKinArrows();
    QList<Arrow*> getPochArrows();
    int getHeight() {return my_height;}
    void removeArrows();
    void addPochArrow(Arrow *arrow);
    void addKinArrow(Arrow *arrow);
    QPolygonF polygon() const { return pol;}
    int type() const override { return Type;}
    QString getString();
    int getDiagramType();
    ~ActionBars();
signals:
    void signal1();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
private:
   // QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    DiagramType myDiagramType;
    QPen pen;
    QString st;
    QDialog *dial;
    QLineEdit *kas;
    QLineEdit *h;
    QLineEdit *w;
    QList<Arrow *> pocharrows;
    QList<Arrow *> kinarrows;
    QLineEdit *rozmirsh;
    QTextEdit *edit;
    QPolygonF pol;
    bool isString(QLineEdit *s);
    int FontSize;
    int m_height=20, m_width=150;
    int my_height, my_width;
private slots:
    void btpriamclick();
    void btdanclick();
    void btcondclick();
};

#endif // ACTIONBARS_H
