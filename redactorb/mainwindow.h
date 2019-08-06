#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "actionbars.h"
#include <QImage>
#include <QResizeEvent>
#include "paintevents.h"
#include <QPushButton>
#include "generator.h"
#include <QGraphicsItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    paintEvents *scene;
    QLineEdit *kas;
    QLineEdit *h;
    bool isString(QLineEdit *s);
    bool checkPoch();
    bool checkKinec();
    QLineEdit *w;
    Generator *g;
    QLabel *labe;
    QLineEdit *rozmirsh;
    QDialog *dial;
    QTextEdit *edit;

protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_action_triggered(bool checked);
    void slot1();
    void slot2();
    void slot3();
    void SelectionChan();
    void on_action_2_triggered(bool checked);
    void on_action_3_triggered(bool checked);
    void on_action_4_triggered(bool checked);
    void on_actionNext_triggered(bool checked);
    void on_actionNext_2_triggered(bool checked);
    void on_action_5_triggered(bool checked);
    void on_action_6_triggered(bool checked);
    void on_action_7_triggered(bool checked);
    void on_action_8_triggered(bool checked);
    void on_action_9_triggered(bool checked);
    void on_action_11_triggered(bool checked);
    void on_action_10_triggered(bool checked);
    void on_action1_2_triggered(bool checked);
    void on_action_12_triggered(bool checked);
    void on_action_13_triggered(bool checked);
    void on_action_17_triggered(bool checked);
    void on_action_16_triggered(bool checked);
    void on_action_15_triggered(bool checked);
    void on_action_14_triggered(bool checked);
    void on_action_18_triggered(bool checked);
    void on_action_19_triggered(bool checked);
    void on_action_20_triggered(bool checked);
};

#endif // MAINWINDOW_H
