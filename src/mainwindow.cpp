#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#include "mainwindow.h"
#include "hexCodes.h"
#include "../ui/ui_mainwindow.h"

QByteArray replacement = QByteArray::fromHex(NESTOPIA_YUV_HEX);

static const QHash<QString, QByteArray> palettes = {
    {"Nestopia Emulator's YUV",                                 QByteArray::fromHex(NESTOPIA_YUV_HEX)},
    {"Nestopia Emulator's RGB",                                 QByteArray::fromHex(NESTOPIA_RGB_HEX)},
    {"FireBrandX's FBX Composite Direct",                       QByteArray::fromHex(COMPOSITE_DIRECT_HEX)},
    {"Wavebeam",                                                QByteArray::fromHex(WAVEBEAM_HEX)},
    {"Wavebeam (Alternative Version)",                          QByteArray::fromHex(WAVEBEAM_ALT_HEX)},
    {"FCEUX NES Emulator's colorful NES",                       QByteArray::fromHex(FCEUX_COLORFUL_HEX)},
    {"Original NES Wii VC",                                     QByteArray::fromHex(ORIGINAL_WII_VC_HEX)},
    {"Restored NES Wii VC",                                     QByteArray::fromHex(RESTORED_WII_VC_HEX)},
    {"Animal Crossing (GameCube) NES Emulator",                 QByteArray::fromHex(ANIMAL_CROSSING_HEX)},
    {"Nintendo 3DS Virtual Console without dark enabled",       QByteArray::fromHex(VC_3DS_HEX)},
    {"NES Classic Mini",                                        QByteArray::fromHex(NES_CLASSIC_MINI_HEX)},
    {"NES Remix U game series (Wii U) NES",                     QByteArray::fromHex(NES_REMIX_HEX)},
    {"Original Mega Man NES",                                   QByteArray::fromHex(ORIGINAL_MEGAMAN_HEX)},
    {"Rockman 9 Modern NES",                                    QByteArray::fromHex(ROCKMAN_9_HEX)},
    {"Mega Man Legacy Collection (Nintendo 3DS) Modern NES",    QByteArray::fromHex(MEGAMAN_LEGACY_COLLECTION_HEX)}
};

static const QHash<QString, QString> images = {
    {"Nestopia Emulator's YUV",                                 ":/images/nestopia_yuv.png"},
    {"Nestopia Emulator's RGB",                                 ":/images/nestopia_rgb.png"},
    {"FireBrandX's FBX Composite Direct",                       ":/images/composite_direct.png"},
    {"Wavebeam",                                                ":/images/wavebeam_1.png"},
    {"Wavebeam (Alternative Version)",                          ":/images/wavebeam_2.png"},
    {"FCEUX NES Emulator's colorful NES",                       ":/images/fceux_colorful.png"},
    {"Original NES Wii VC",                                     ":/images/original_wii_vc.png"},
    {"Restored NES Wii VC",                                     ":/images/restored_wii_vc.png"},
    {"Animal Crossing (GameCube) NES Emulator",                 ":/images/animal_crossing.png"},
    {"Nintendo 3DS Virtual Console without dark enabled",       ":/images/3ds_vc.png"},
    {"NES Classic Mini",                                        ":/images/nes_classic_mini.png"},
    {"NES Remix U game series (Wii U) NES",                     ":/images/nes_remix.png"},
    {"Original Mega Man NES",                                   ":/images/original_megaman.png"},
    {"Rockman 9 Modern NES",                                    ":/images/rockman_9.png"},
    {"Mega Man Legacy Collection (Nintendo 3DS) Modern NES",    ":/images/megaman_legacy_collection.png"}
};

static int getPalettePos(const QByteArray &data); 

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
    int pos = getPalettePos(data);
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
    auto it1 = palettes.find(arg1);

    if (it1 != palettes.end()) {
        replacement = *it1;
    } else {
        QMessageBox::critical(this, "Uh oh... This shouldn't happen", "Unknown palette: " + arg1);
        return;
    }

    auto it2 = images.find(arg1);

    if (it2 != images.end()) {
        QPixmap p(*it2);
        ui->newImage->setPixmap(p);
    } else {
        QPixmap p(":/images/original_wii_vc.png");
        ui->newImage->setPixmap(p);
        QMessageBox::critical(this, "Uh oh... This shouldn't happen", "No palette image: " + arg1);
        return;
    }
}

static int getPalettePos(const QByteArray &data) {
    int pos = data.indexOf(QByteArray::fromHex(SEARCH_HEX_1));

    if (pos == -1)
        pos = data.indexOf(QByteArray::fromHex(SEARCH_HEX_2));

    if (pos != -1)
        return pos + 32;

    return -1;
}
