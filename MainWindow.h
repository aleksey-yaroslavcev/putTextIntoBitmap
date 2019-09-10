#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_butSaveAs_clicked();

private:
    Ui::MainWindow* ui;
    QString _fileName;
};

#endif // MAINWINDOW_H
