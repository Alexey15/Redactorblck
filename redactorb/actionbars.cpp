#include "actionbars.h"
#include "arrow.h"
#include <QMessageBox>
#include <QGraphicsScene>

ActionBars::ActionBars(DiagramType DiagramType, int width, int height, QTextEdit *edit, int FontS, QObject *parent)
    : QObject(parent), QGraphicsPolygonItem()
{
    installEventFilter(this);
    myDiagramType=DiagramType;
    my_height=height;
    my_width=width;
    st=edit->toPlainText();
    FontSize=FontS;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
}

ActionBars::~ActionBars()
{
    pocharrows.clear();
    kinarrows.clear();
}

bool ActionBars::isString(QLineEdit *s){
    for (int i=0; i<s->text().length(); i++){
        if (!(s->text().at(i).isNumber())){
            return true;
            break;
        }
    }
    return false;
}

/*QRectF ActionBars::boundingRect() const
{
    switch (myDiagramType) {
    case Priam:{
        return QRectF(0, 0, my_width+1, (my_height/2)+2);
        break;}
    case Conditions:
    {
        return QRectF(-my_width / 2, -my_height / 2, my_width, my_height);
        break;
    }
    case poch:
    {
        return QRectF(10, 0, m_width, m_height+52);
        break;
    }
    case danih:
    {
        return QRectF(-my_width, 0, my_width*5, my_height);
        break;
    }
    case kinec:
    {
        return QRectF(10, 0, m_width, m_height+52);
        break;
    }
    }
    return QRectF(0, 0, m_width, m_height);
}
*/
QList<Arrow*> ActionBars::getPochArrows(){
    return pocharrows;
}
QList<Arrow*> ActionBars::getKinArrows(){
    return kinarrows;
}
void ActionBars::setPenWidth(int w){
    pen.setWidth(w);
}
void ActionBars::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    switch (myDiagramType) {
    case Priam:{
        painter->setBrush(Qt::white);
        painter->setPen(pen);
        pol.clear();
        pol << QPoint(0, 0);
        pol << QPoint(0, my_height / 2);
        pol << QPoint(my_width, my_height / 2);
        pol << QPoint(my_width, 0);
        painter->drawPolygon(pol);
        painter->setFont(QFont("Arial", FontSize));
        painter->drawText(ActionBars::boundingRect(), Qt::AlignCenter, st);
        break;
    }
    case Conditions:
    {
        painter->setBrush(Qt::white);
        painter->setPen(pen);
          QPoint
            p0(0, -my_height / 2), p1(my_width / 2, 0),
            p2(0, my_height / 2), p3(-my_width / 2, 0);
        pol.clear();
        pol << p0;
        pol << p1;
        pol << p2;
        pol << p3;
        painter->drawPolygon(pol);
        painter->setFont(QFont("Arial", FontSize));
        painter->drawText(ActionBars::boundingRect(), Qt::AlignCenter, st);
        break;
    }
    case poch:
    {
        painter->setBrush(Qt::white);
        painter->setPen(pen);
        path.moveTo(m_width, 50);
                     path.arcTo(m_width-50, 0, 50, 50, 0, 90);
                     path.arcTo(m_height, 0, 50, 50, 90, 90);
                     path.arcTo(m_height, m_height, 50, 50, 180, 90);
                     path.arcTo(m_width-50, m_height, 50, 50, 270, 90);
                     path.lineTo(m_width, 25);
        pol.clear();
        pol.append(path.toFillPolygon());
        painter->drawPolygon(pol);
        painter->setFont(QFont("Arial", 12));
        painter->drawText(ActionBars::boundingRect(), Qt::AlignCenter, "Початок");
        break;
    }
    case danih:
    {
        painter->setBrush(Qt::white);
        painter->setPen(pen);
        QPoint
          p0(my_width, 0), p1(-my_width, my_height),
          p2(my_width*2, my_height), p3(my_width*4, 0);
        pol.clear();
        pol << p0;
        pol << p1;
        pol << p2;
        pol << p3;
        painter->drawPolygon(pol);
        painter->setFont(QFont("Arial", FontSize));
        painter->drawText(ActionBars::boundingRect(), Qt::AlignCenter, st);
        break;
    }
    case kinec:
    {
        painter->setBrush(Qt::white);
        painter->setPen(pen);
        path.moveTo(m_width, 50);
                     path.arcTo(m_width-50, 0, 50, 50, 0, 90);
                     path.arcTo(m_height, 0, 50, 50, 90, 90);
                     path.arcTo(m_height, m_height, 50, 50, 180, 90);
                     path.arcTo(m_width-50, m_height, 50, 50, 270, 90);
                     path.lineTo(m_width, 25);
        pol.clear();
        pol.append(path.toFillPolygon());
        painter->drawPolygon(pol);
        painter->setFont(QFont("Arial", 12));
        painter->drawText(ActionBars::boundingRect(), Qt::AlignCenter, "Кінець");
        break;
    }
    }
    setPolygon(pol);
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
QVariant ActionBars::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (Arrow *arrow1, pocharrows) {
            arrow1->updatePosition();
        }
        foreach (Arrow *arrow2, kinarrows) {
            arrow2->updatePosition();
        }
    }
    update();
    return value;
}
void ActionBars::addPochArrow(Arrow *arrow)
{
    pocharrows.append(arrow);
}
void ActionBars::addKinArrow(Arrow *arrow){
    kinarrows.append(arrow);
}
void ActionBars::removePochArrow(Arrow *arrow)
{
    int index = pocharrows.indexOf(arrow);

    if (index != -1)
        pocharrows.removeAt(index);
}
void ActionBars::removeKinArrow(Arrow *arrow)
{
    int index = kinarrows.indexOf(arrow);

    if (index != -1)
        kinarrows.removeAt(index);
}
void ActionBars::removeArrows()
{
    foreach (Arrow *arrow, pocharrows) {
        arrow->startItem()->removePochArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
    foreach (Arrow *arrow, kinarrows) {
        arrow->endItem()->removeKinArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}
void ActionBars::setNewTextEdit(QTextEdit *newst){
    st.clear();
    st = newst->toPlainText();
}
QString ActionBars::getString(){
    return st;
}
void ActionBars::setFontSize(int size){
    FontSize=size;
}
/*QPolygonF ActionBars::polygon(){
    return pol;
}
*/
void ActionBars::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit signal1();
    switch (myDiagramType) {
    case Priam:{
        dial = new QDialog();
        dial->setWindowTitle("Редагування блоку дії");
        QVBoxLayout *v = new QVBoxLayout;
        QHBoxLayout *h0 = new QHBoxLayout;
        QHBoxLayout *h2 = new QHBoxLayout;
        QHBoxLayout *h1 = new QHBoxLayout;
        QHBoxLayout *h3 = new QHBoxLayout;
        kas = new QLineEdit;
        QLabel *labe = new QLabel("Розмір елементу: ");
        QLabel *labe1 = new QLabel("Розмір шрифту: ");
        h0->addWidget(labe);
        h0->addWidget(kas);
        v->addLayout(h0);
        h2->addWidget(labe1);
        rozmirsh = new QLineEdit;
        h2->addWidget(rozmirsh);
        v->addLayout(h2);
        QLabel *labe2 = new QLabel("Текст об'єкту: ");
        h3->addWidget(labe2);
        edit = new QTextEdit;
        h3->addWidget(edit);
        v->addLayout(h3);
        QPushButton *bt = new QPushButton("Ok");
        QPushButton *clos = new QPushButton("Відмінити");
        h1->addWidget(bt);
        h1->addWidget(clos);
        v->addLayout(h1);
        rozmirsh->setText(""+QString::number(FontSize));
        kas->setText(""+QString::number(my_width));
        edit->setPlainText(getString());
        connect(bt, SIGNAL(clicked()), this, SLOT(btpriamclick()));
        connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
        dial->setLayout(v);
        dial->exec();
        break;
    }
    case danih:
    {
        dial = new QDialog();
        dial->setWindowTitle("Редагування блоку даних");
        QVBoxLayout *v = new QVBoxLayout;
        QHBoxLayout *h0 = new QHBoxLayout;
        QHBoxLayout *h1 = new QHBoxLayout;
        QHBoxLayout *h2 = new QHBoxLayout;
        QHBoxLayout *h3 = new QHBoxLayout;
        QHBoxLayout *h4 = new QHBoxLayout;
        h = new QLineEdit;
        w = new QLineEdit;
        QLabel *labe2 = new QLabel("Введіть висоту і ширину обьєкта (за замовчуванням - 50 і 40):");
        v->addWidget(labe2);
        QLabel *labe3 = new QLabel("Висота: ");
        QLabel *labe4 = new QLabel("Ширина: ");
        h0->addWidget(labe3);
        h0->addWidget(h);
        h1->addWidget(labe4);
        h1->addWidget(w);
        QLabel *labe5= new QLabel("Розмір шрифту: ");
        rozmirsh = new QLineEdit;
        h3->addWidget(labe5);
        h3->addWidget(rozmirsh);
        QLabel *labe6 = new QLabel("Текст об'єкту: ");
        edit = new QTextEdit;
        h4->addWidget(labe6);
        h4->addWidget(edit);
        QPushButton *bt = new QPushButton("Ok");
        QPushButton *clos = new QPushButton("Відмінити");
        h2->addWidget(bt);
        h2->addWidget(clos);
        v->addLayout(h0);
        v->addLayout(h1);
        v->addLayout(h3);
        v->addLayout(h4);
        v->addLayout(h2);
        h->setText(""+QString::number(my_height));
        w->setText(""+QString::number(my_width));
        rozmirsh->setText(""+QString::number(FontSize));
        edit->setPlainText(st);
        connect(bt, SIGNAL(clicked()), this, SLOT(btdanclick()));
        connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
        dial->setLayout(v);
        dial->exec();
        break;
    }
    case Conditions:
    {
        dial = new QDialog();
        dial->setWindowTitle("Редагування блоку умови");
        QVBoxLayout *v = new QVBoxLayout;
        QHBoxLayout *h0 = new QHBoxLayout;
        QHBoxLayout *h1 = new QHBoxLayout;
        QHBoxLayout *h2 = new QHBoxLayout;
        QHBoxLayout *h3 = new QHBoxLayout;
        QHBoxLayout *h4 = new QHBoxLayout;
        h = new QLineEdit;
        w = new QLineEdit;
        QLabel *labe2 = new QLabel("Введіть висоту і ширину обьєкта:");
        v->addWidget(labe2);
        QLabel *labe3 = new QLabel("Висота: ");
        QLabel *labe4 = new QLabel("Ширина: ");
        h0->addWidget(labe3);
        h0->addWidget(h);
        h1->addWidget(labe4);
        h1->addWidget(w);
        QLabel *labe5= new QLabel("Розмір шрифту: ");
        rozmirsh = new QLineEdit;
        h3->addWidget(labe5);
        h3->addWidget(rozmirsh);
        QLabel *labe6 = new QLabel("Текст об'єкту: ");
        edit = new QTextEdit;
        h4->addWidget(labe6);
        h4->addWidget(edit);
        QPushButton *bt = new QPushButton("Ok");
        QPushButton *clos = new QPushButton("Відмінити");
        h2->addWidget(bt);
        h2->addWidget(clos);
        v->addLayout(h0);
        v->addLayout(h1);
        v->addLayout(h3);
        v->addLayout(h4);
        v->addLayout(h2);
        rozmirsh->setText(""+QString::number(FontSize));
        w->setText(""+QString::number(my_width));
        h->setText(""+QString::number(my_height));
        edit->setPlainText(st);
        connect(bt, SIGNAL(clicked()), this, SLOT(btcondclick()));
        connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
        dial->setLayout(v);
        dial->exec();
        break;
    }
    case poch:
    {
        break;
    }
    case kinec:
    {
        break;
    }
    }
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void ActionBars::btpriamclick(){
    if (kas->text().isEmpty() || rozmirsh->text().isEmpty()){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("Деякі важливі поля пусті!");
        msg->exec();
        dial->close();
    } else {
    if (isString(kas) || isString(rozmirsh)){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("Ви ввели не число!");
        msg->exec();
        dial->close();
    }
    setWidth(kas->text().toInt());
    setHeight(kas->text().toInt());
    setFontSize(rozmirsh->text().toInt());
    setNewTextEdit(edit);
    update();
    }
    dial->close();
}
void ActionBars::btdanclick(){
    if (h->text().isEmpty() || w->text().isEmpty() || rozmirsh->text().isEmpty()){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("Деякі важливі поля пусті!");
        msg->exec();
        dial->close();
    } else{
    if (isString(h)){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("В полі висота ви ввели не число!");
        msg->exec();
        dial->close();
    }
    if (isString(w)){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("В полі ширина ви ввели не число!");
        msg->exec();
        dial->close();
    }
    if(isString(rozmirsh)){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("В полі розмір шрифту ви ввели не число!");
        msg->exec();
        dial->close();
    }
    setWidth(w->text().toInt());
    setHeight(h->text().toInt());
    setFontSize(rozmirsh->text().toInt());
    setNewTextEdit(edit);
    update();
    }
    dial->close();
}
void ActionBars::btcondclick(){
    if (h->text().isEmpty() || w->text().isEmpty() || rozmirsh->text().isEmpty()){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("Деякі важливі поля пусті!");
        msg->exec();
        dial->close();
    } else {
    if (isString(h)){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("В полі висота ви ввели не число!");
        msg->exec();
        dial->close();
    }
    if (isString(w)){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("В полі ширина ви ввели не число!");
        msg->exec();
        dial->close();
    }
    if(isString(rozmirsh)){
        QMessageBox *msg = new QMessageBox();
        msg->setText("Помилка!");
        msg->setInformativeText("В полі розмір шрифту ви ввели не число!");
        msg->exec();
        dial->close();
    }
    setWidth(w->text().toInt());
    setHeight(h->text().toInt());
    setFontSize(rozmirsh->text().toInt());
    setNewTextEdit(edit);
    update();
    }
    dial->close();
}

void ActionBars::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsItem::mouseReleaseEvent(event);
}
void ActionBars::setWidth(int w){
    my_width=w;
}
void ActionBars::setHeight(int h){
    my_height=h;

}
int ActionBars::getDiagramType(){
    return myDiagramType;
}
