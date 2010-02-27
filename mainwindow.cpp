#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "state.h"
#include "plot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state = new State;

    connect(ui->sampleFunctionButton, SIGNAL(clicked()),
            state, SLOT(sampleFunction()));
    connect(ui->findCentersButton, SIGNAL(clicked()),
            state, SLOT(findCenters()));
    connect(ui->trainNetworkButton, SIGNAL(clicked()),
            state, SLOT(trainNetwork()));
    connect(ui->resetButton, SIGNAL(clicked()),
            state, SLOT(reset()));
    connect(ui->configButton, SIGNAL(clicked()),
            state, SLOT(newConfig()));

    plot = new Plot(ui->centralWidget, state);
    ui->verticalLayout->insertWidget(0, plot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
