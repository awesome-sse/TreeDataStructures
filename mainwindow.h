#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include <QSignalMapper>
#include <QFileDialog>
#include <QComboBox>
#include <QThread>
#include <QMovie>
#include <QLabel>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "TreeTesting.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    bool BinButtonPressed = false;
    bool CartButtonPressed = false;
    bool AvlButtonPressed = false;
    bool RBButtonPressed = false;

    Ui::MainWindow *ui;
    QPushButton *BinTreeButton;
    QPushButton *CartTreeButton;
    QPushButton *AvlTreeButton;
    QPushButton *RBTreeButton;
    QPushButton *LoadFileButton;
    QPushButton *RandomGenerateButton;
    QPushButton *ClearButton;
    QComboBox *functype;
    QComboBox *datatype;
    QMovie * loading;

signals:
    void start_load();
    void end_load();

private slots:
    void handleButton();
    void showFileBrowser();
    void generateRandomData();
    void clear();
    void testing();
    void test();
};



#endif // MAINWINDOW_H
