#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_butOpen_clicked();

    void on_spinFontSize_valueChanged(int arg1);

    void on_cobTextColor_currentIndexChanged(int index);

    void on_chbIsBold_stateChanged(int arg1);

    void on_butSelectDirectory_clicked();

    void on_butProcess_clicked();

    void on_butPlus_clicked();

    void on_butMinus_clicked();

private:
    void updatePreview();
    QImage getImage(const QString& title);

    Ui::MainWindow* ui;
    QString _fileName;
    QString _dstDirectory;
    QMap<int, QColor> _colorMap;
    QStandardItemModel _batchJobModel;
};

#endif // MAINWINDOW_H
