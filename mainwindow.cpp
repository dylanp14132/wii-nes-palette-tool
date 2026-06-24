#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helper.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    replacement = QByteArray::fromHex("B18C80B188549C14AC0FB408B400A86098C08520814081218109800080008000D6B5897BA11FB89FD079D86FD8C4CD20B5A09E008640822681F1800080008000FFFFB2DFCA5FE1DFF9BFFDB9FE0EF664DEE0C760AF86A390A73BA52980008000FFFFE37FEB5FF73FFF1FFF1DFF38FB74F392E7B2DFD5DBD9DBBEDEF780008000");
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
        "Extracted WAD Files (00000001.app);;All Files (*.*)"
        );

    if (fileName.isEmpty())
        return;

    ui->fileText->setText(fileName);
    filePath = fileName;
}


void MainWindow::on_fileText_editingFinished()
{
    filePath = ui->fileText->text();
}


void MainWindow::on_patchButton_clicked()
{
    if (filePath.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Please specify a file path.");
        return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", "Failed to open file.");
        return;
    }

    QByteArray data = file.readAll();
    int pos = Helper::getPalettePos(data);
    file.close();

    if (pos != -1)
    {
        data.replace(pos, 128, replacement);

        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, "Error", "Failed to write to file.");
            return;
        }

        file.write(data);
        file.close();

        QMessageBox::information(this, "Success!", "New color palette applied.");

        return;
    }

    QMessageBox::critical(this, "Error", "Failed to apply new color palette.");
}

void MainWindow::on_paletteList_currentTextChanged(const QString &arg1)
{
    auto it1 = Helper::palettes.find(arg1);

    if (it1 != Helper::palettes.end()) {
        replacement = *it1;
    } else {
        QMessageBox::critical(this, "Uh oh... This shouldn't happen", "Unknown palette: " + arg1);
        return;
    }

    auto it2 = Helper::images.find(arg1);

    if (it2 != Helper::images.end()) {
        QPixmap p(*it2);
        ui->newImage->setPixmap(p);
    } else {
        QPixmap p(":/images/original_wii_vc.png");
        ui->newImage->setPixmap(p);
        QMessageBox::critical(this, "Uh oh... This shouldn't happen", "No palette image: " + arg1);
        return;
    }
}

