#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fileSelectButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Select a File",
        "",
        "Extracted WAD Files (*.app);;All Files (*.*)"
        );

    if (!fileName.isEmpty())
    {
        qDebug() << "Selected file:" << fileName;
    }
}

