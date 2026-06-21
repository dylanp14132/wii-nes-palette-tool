#include "mainwindow.h"
#include "ui_mainwindow.h"
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
        "Extracted WAD Files (*.app);;Test Files (*.txt)"
        );

    if (!fileName.isEmpty())
    {
        qDebug() << "Selected file:" << fileName;
    }

    ui->fileText->setText(fileName);
    filePath = fileName;
}


void MainWindow::on_fileText_editingFinished()
{
    filePath = ui->fileText->text();
    qDebug() << "Selected file:" << filePath;
}


void MainWindow::on_patchButton_clicked()
{
    const QByteArray search1 = QByteArray::fromHex("00600000426F6D426C69737300000000425921C80D5341540000000000000000");
    const QByteArray search2 = QByteArray::fromHex("BA7F0000426F6D426C69737300000000425921C80D5341540000000000000000");

    if (filePath.isEmpty())
    {
        QMessageBox::information(this, "Error", "Please specify a file path.");
        return;
    }

    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, "Error", "Failed to open file.");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    int pos = data.indexOf(search1);

    if (pos != -1)
    {
        data.replace(pos + search1.size(), 128, replacement);

        if (!file.open(QIODevice::WriteOnly))
            return;
        file.write(data);
        file.close();

        QMessageBox::information(this, "Success!", "WAD file successfully changed.");

        return;
    }

    pos = data.indexOf(search2);

    if (pos != -1)
    {
        data.replace(pos + search1.size(), 128, replacement);
        if (!file.open(QIODevice::WriteOnly))
            return;
        file.write(data);
        file.close();

        QMessageBox::information(this, "Success!", "Color palette successfully changed.");

        return;
    }

    QMessageBox::information(this, "Error", "Failed to change the color palette.");
}


void MainWindow::on_paletteList_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        replacement = QByteArray::fromHex("B18C80B188549C14AC0FB408B400A86098C08520814081218109800080008000D6B5897BA11FB89FD079D86FD8C4CD20B5A09E008640822681F1800080008000FFFFB2DFCA5FE1DFF9BFFDB9FE0EF664DEE0C760AF86A390A73BA52980008000FFFFE37FEB5FF73FFF1FFF1DFF38FB74F392E7B2DFD5DBD9DBBEDEF780008000");
        break;
    case 1:
        replacement = QByteArray::fromHex("B5AD8092801BB53BC80DD80DD880C920B520912081A482408129800080008000DAD681BB813FC81FD81FFC12FC00EDA0C9A09240824082CD8252908480008000FFFFB6DFCA5FEDBFFC1FFDBFFE40FEC0EF60B76083E0A7FB83FFA52980008000FFFFDB7FEEDFFEDFFE5FFED6FF72FFE9FFEDDBE9CBEDA7FBCB7FCA5280008000");
        break;
    case 2:
        replacement = QByteArray::fromHex("A529800D840C940BA009A400A00094408C8080C280C080A28088800080008000B9CE80D09815A412B00FB407B480ACA0A1208D6089608166812B884280008000D6B5A5D6B17AC15CD155D530D989C9C6BDC5AE009E269A2B9E319CE780008000DAD6C676C635CE37D217D633D651CE2FCE6ECA8FC28FBE70BA51EF7B80008000");
        break;
    }
}

