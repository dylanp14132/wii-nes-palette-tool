#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "helper.h"
#include "hexCodes.h"
#include "../ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    replacement = QByteArray::fromHex(NESTOPIA_YUV_HEX);
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
