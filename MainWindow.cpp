#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QPainter>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_butOpen_clicked()
{
    _fileName = QFileDialog::getOpenFileName(this,
                                             tr("Open Bitmap"),
                                             QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                             tr("Bitmap Files (*.bmp)"));
    if (_fileName.isEmpty())
        return;

    QPixmap pixmap(_fileName);
    ui->laImage->setPixmap(pixmap);
}

void MainWindow::on_butSaveAs_clicked()
{
    if (_fileName.isEmpty())
        return;

    QString saveFileName = QFileDialog::getSaveFileName(this,
                                                        tr("Open Bitmap"),
                                                        QStandardPaths::writableLocation(QStandardPaths::PicturesLocation),
                                                        tr("Bitmap Files (*.bmp)"));
    if (saveFileName.isEmpty())
        return;

    QImage image(_fileName);
    QPainter p;
    if (!p.begin(&image))
        return;

    p.setPen(QPen(Qt::white));
    p.setFont(QFont("Times", 12, QFont::Bold));
    p.drawText(image.rect(), Qt::AlignCenter, ui->leText->text());
    p.end();

    image.save(saveFileName);

    QPixmap pixmap(saveFileName);
    ui->laResultImage->setPixmap(pixmap);
}
