#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_fileSelectButton_clicked();
    void on_fileText_editingFinished();
    void on_patchButton_clicked();
    void on_paletteList_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    QString filePath;
    QByteArray replacement;
};
#endif // MAINWINDOW_H
