#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Редактор Блок Схем (Бета Версія)");
    setFixedSize(838, 630);
    scene= new paintEvents();
    ui->graphicsView->setScene(scene);
    connect(scene, SIGNAL(selectionChanged()), this, SLOT(SelectionChan()));
    g = new Generator(scene);
    ui->verticalLayout->addWidget(g);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::SelectionChan(){
    foreach (QGraphicsItem *item, scene->items()) {
        if (item->type()==ActionBars::Type){
        if(qgraphicsitem_cast<ActionBars *>(item)->isSelected()){
            qgraphicsitem_cast<ActionBars *>(item)->setPenWidth(3);
            qgraphicsitem_cast<ActionBars *>(item)->update();
        } else{
            qgraphicsitem_cast<ActionBars *>(item)->setPenWidth(1);
            qgraphicsitem_cast<ActionBars *>(item)->update();
        }
    }
    }
}

bool MainWindow::isString(QLineEdit *s){
    for (int i=0; i<s->text().length(); i++){
        if (!(s->text().at(i).isNumber())){
            return true;
            break;
        }
    }
    return false;
}
bool MainWindow::checkPoch(){
    foreach (QGraphicsItem *item, scene->items()) {
        if(item->type()==ActionBars::Type){
        if(qgraphicsitem_cast<ActionBars *>(item)->getDiagramType()==ActionBars::poch){
            return true;
        }
        }
    }
    return false;
}
bool MainWindow::checkKinec(){
    foreach (QGraphicsItem *item, scene->items()) {
        if(item->type()==ActionBars::Type){
        if(qgraphicsitem_cast<ActionBars *>(item)->getDiagramType()==ActionBars::kinec){
            return true;
        }
        }
    }
    return false;
}
void MainWindow::on_action_triggered(bool checked)
{
    if (checkPoch()){
    dial = new QDialog();
    dial->setWindowTitle("Блок дії");
    QVBoxLayout *v = new QVBoxLayout;
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h3 = new QHBoxLayout;
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
    connect(bt, SIGNAL(clicked()), this, SLOT(slot1()));
    connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
    dial->setLayout(v);
    dial->exec(); }else{
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }  Q_UNUSED(checked);
}
void MainWindow::on_action_2_triggered(bool checked)
{
    if (checkPoch()){
    dial = new QDialog();
    dial->setWindowTitle("Блок дії");
    QVBoxLayout *v = new QVBoxLayout;
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h3 = new QHBoxLayout;
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
    connect(bt, SIGNAL(clicked()), this, SLOT(slot1()));
    connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
    dial->setLayout(v);
    dial->exec(); }else{
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }  Q_UNUSED(checked);
}
void MainWindow::on_action_3_triggered(bool checked)
{
    if(checkPoch()){
    dial = new QDialog();
    dial->setWindowTitle("Блок умови");
    QVBoxLayout *v = new QVBoxLayout;
    QHBoxLayout *h0 = new QHBoxLayout;
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h2 = new QHBoxLayout;
    QHBoxLayout *h3 = new QHBoxLayout;
    QHBoxLayout *h4 = new QHBoxLayout;
    h = new QLineEdit;
    w = new QLineEdit;
    QLabel *labe2 = new QLabel("Введіть висоту і ширину обьєкта (за замовчуванням - 150):");
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
    h->setText("150");
    w->setText("150");
    connect(bt, SIGNAL(clicked()), this, SLOT(slot2()));
    connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
    dial->setLayout(v);
    dial->exec();
    } else {
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }
    Q_UNUSED(checked);
}
void MainWindow::on_action_4_triggered(bool checked)
{
    if(checkPoch()){
    dial = new QDialog();
    dial->setWindowTitle("Блок умови");
    QVBoxLayout *v = new QVBoxLayout;
    QHBoxLayout *h0 = new QHBoxLayout;
    QHBoxLayout *h1 = new QHBoxLayout;
    QHBoxLayout *h2 = new QHBoxLayout;
    QHBoxLayout *h3 = new QHBoxLayout;
    QHBoxLayout *h4 = new QHBoxLayout;
    h = new QLineEdit;
    w = new QLineEdit;
    QLabel *labe2 = new QLabel("Введіть висоту і ширину обьєкта (за замовчуванням - 150):");
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
    h->setText("150");
    w->setText("150");
    connect(bt, SIGNAL(clicked()), this, SLOT(slot2()));
    connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
    dial->setLayout(v);
    dial->exec();
    } else {
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }
    Q_UNUSED(checked);
}

void MainWindow::on_actionNext_triggered(bool checked)
{
    if(checkPoch()){
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас уже є добавлений блок початку діаграми!");
        msg->exec();
    }else{
    scene->addPoch();
    }
    Q_UNUSED(checked);
}
void MainWindow::on_actionNext_2_triggered(bool checked)
{
    if(checkPoch()){
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас уже є добавлений блок початку діаграми!");
        msg->exec();
    }else{
    scene->addPoch();
    }
    Q_UNUSED(checked);
}
void MainWindow::slot1(){
    //Добавлення елементу
    scene->addPriam(100, 100, edit, 10);
    dial->close();
}
void MainWindow::slot2(){
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
    scene->addCondition(w->text().toInt(), h->text().toInt(), edit, rozmirsh->text().toInt());
    }
    dial->close();
}
void MainWindow::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event);
}

void MainWindow::on_action_5_triggered(bool checked)
{
    if (checkPoch()){
    dial = new QDialog();
    dial->setWindowTitle("Блок даних");
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
    h->setText("50");
    w->setText("40");
    connect(bt, SIGNAL(clicked()), this, SLOT(slot3()));
    connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
    dial->setLayout(v);
    dial->exec();
    } else {
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }
    Q_UNUSED(checked);
}
void MainWindow::on_action_7_triggered(bool checked)
{
    if (checkPoch()){
    dial = new QDialog();
    dial->setWindowTitle("Блок даних");
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
    h->setText("50");
    w->setText("40");
    connect(bt, SIGNAL(clicked()), this, SLOT(slot3()));
    connect(clos, SIGNAL(clicked()), dial, SLOT(close()));
    dial->setLayout(v);
    dial->exec();
    } else {
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }
    Q_UNUSED(checked);
}
void MainWindow::slot3(){
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
    scene->addDanih(w->text().toInt(), h->text().toInt(), edit, rozmirsh->text().toInt());
    }
    dial->close();
}

void MainWindow::on_action_6_triggered(bool checked)
{
    foreach (QGraphicsItem *item1, scene->selectedItems()) {
        if (qgraphicsitem_cast<ActionBars *>(item1)->getDiagramType()==ActionBars::poch){
            foreach (QGraphicsItem *item2, scene->items()) {
                scene->removeItem(item2);
            }
            break;
        }else {
           scene->removeItem(item1);
        }
        }
    scene->update();
    Q_UNUSED(checked);
}

void MainWindow::on_action_8_triggered(bool checked)
{
    if (checkKinec()){
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка:");
        msg->setInformativeText("У вас уже є присутній елемент кінця!");
        msg->exec();
    } else {
    if(checkPoch()){
        scene->addKinec();
    }else {
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }
    }
    Q_UNUSED(checked);
}

void MainWindow::on_action_9_triggered(bool checked)
{
    if (checkKinec()){
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка:");
        msg->setInformativeText("У вас уже є присутній елемент кінця!");
        msg->exec();
    } else {
    if(checkPoch()){
        scene->addKinec();
    }else {
        QMessageBox *msg = new QMessageBox;
        msg->setText("Помилка добавлення:");
        msg->setInformativeText("У вас немає присутнього блоку початку!");
        msg->exec();
    }
    }
    Q_UNUSED(checked);
}
void MainWindow::on_action_11_triggered(bool checked)
{
    scene->setMode(paintEvents::addArrow);
    Q_UNUSED(checked);
}

void MainWindow::on_action_10_triggered(bool checked)
{
    scene->setMode(paintEvents::Move);
    Q_UNUSED(checked);
}

void MainWindow::on_action1_2_triggered(bool checked)
{
    g->Test2();
    Q_UNUSED(checked);
}

void MainWindow::on_action_12_triggered(bool checked)
{
    scene->setMode(paintEvents::addYesArrow);
    Q_UNUSED(checked);
}
void MainWindow::on_action_13_triggered(bool checked)
{
    scene->setMode(paintEvents::addNoArrow);
    Q_UNUSED(checked);
}

void MainWindow::on_action_17_triggered(bool checked)
{
    scene->setMode(paintEvents::Move);
    Q_UNUSED(checked);
}

void MainWindow::on_action_16_triggered(bool checked)
{
    scene->setMode(paintEvents::addArrow);
    Q_UNUSED(checked);
}

void MainWindow::on_action_15_triggered(bool checked)
{
    scene->setMode(paintEvents::addYesArrow);
    Q_UNUSED(checked);
}

void MainWindow::on_action_14_triggered(bool checked)
{
    scene->setMode(paintEvents::addNoArrow);
    Q_UNUSED(checked);
}
void MainWindow::on_action_18_triggered(bool checked)
{
    g->startProgram();
    Q_UNUSED(checked);
}

void MainWindow::on_action_19_triggered(bool checked)
{
    close();
    Q_UNUSED(checked);
}

void MainWindow::on_action_20_triggered(bool checked)
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Зберегти зображення"), "",
        tr("PNG (*.png)"));
    QImage image(scene->width(), scene->height(), QImage::Format_ARGB32_Premultiplied);
    image.fill(0);
    QPainter painter(&image);
    scene->render(&painter);
    image.save(fileName);
    Q_UNUSED(checked);
}
