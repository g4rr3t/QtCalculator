#include "mainwindow.h"
#include "ui_mainwindow.h"

double calcVal = 0.0;

bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for (int i = 0; i < 10; ++i)
    {
        QString butName = "Button"+QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));

    }

    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Minus, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonPressed()));


    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualButton()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangeNumberSign()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayValue = ui->Display->text();
    if ((displayValue.toDouble() == 0 || displayValue.toDouble() == 0.0))
    {
        ui->Display->setText(butVal);
    } else
    {
        QString newValue = displayValue + butVal;
        double dlbNewVal = newValue.toDouble();
        ui->Display->setText(QString::number(dlbNewVal, 'g', 16));
    }
}

void MainWindow::MathButtonPressed()
{
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if (QString::compare(butVal, "/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    } else if (QString::compare(butVal, "*", Qt::CaseInsensitive) == 0)
    {
        multTrigger = true;
    }else if (QString::compare(butVal, "+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }else if (QString::compare(butVal, "-", Qt::CaseInsensitive) == 0)
    {
        subTrigger = true;
    }
    ui->Display->setText("");

}

void MainWindow::EqualButton()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dlbDisplayVal = displayVal.toDouble();
    if (addTrigger || subTrigger || multTrigger || divTrigger)
    {
        if(addTrigger)
        {
            solution = calcVal + dlbDisplayVal;
        } else if(subTrigger)
        {
            solution = calcVal - dlbDisplayVal;
        } else if(multTrigger)
        {
            solution = calcVal * dlbDisplayVal;
        } else if(divTrigger)
        {
            solution = calcVal / dlbDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void MainWindow::ChangeNumberSign(){
    QString displayVal = ui->Display->text();

    QRegExp reg("[-]?[0-9.]*");
    if (reg.exactMatch(displayVal))
    {
        double dlbDisplayVal = displayVal.toDouble();
        QString res = QString::number(-dlbDisplayVal);
        ui->Display->setText(res);
    }
}

