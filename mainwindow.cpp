#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logic.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CalculatorLogic::getInstance().setEditorFunc([&](const QString &str)
                                                 { ui->display->setText(str); });

    QPushButton *numberButtons[] = {
            ui->button0, ui->button1, ui->button2,
            ui->button3, ui->button4, ui->button5,
            ui->button6, ui->button7, ui->button8,
            ui->button9, ui->buttonDot,
    };
    for (QPushButton *button: numberButtons)
    {
        QObject::connect(button, &QPushButton::clicked, [button]()
        {
            CalculatorLogic::getInstance().append(button->text());
        });
    }

    QPushButton *symbolButtons[] = {
            ui->buttonAdd, ui->buttonSubtract, ui->buttonMultiply, ui->buttonDivide,
            ui->buttonSign, ui->buttonPercent, ui->buttonEquals
    };
    for (QPushButton *button: symbolButtons)
    {
        QObject::connect(button, &QPushButton::clicked, [button]()
        {
            CalculatorLogic::getInstance().calculate(button->text());
        });
    }

    QObject::connect(ui->buttonClear, &QPushButton::clicked, [&]()
    {
        CalculatorLogic::getInstance().clear();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

