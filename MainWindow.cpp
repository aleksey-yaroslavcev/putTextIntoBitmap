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
    _colorMap[0] = Qt::white;
    _colorMap[1] = Qt::black;
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

    updatePreview();
}

void MainWindow::on_spinFontSize_valueChanged(int /*arg1*/)
{
    updatePreview();
}

void MainWindow::on_cobTextColor_currentIndexChanged(int /*index*/)
{
    updatePreview();
}

void MainWindow::updatePreview()
{
    if (_fileName.isEmpty())
        return;

    ui->laResultImage->clear();
    QImage image(_fileName);
    QPainter p;
    if (!p.begin(&image))
        return;

    p.setPen(QPen(_colorMap[ui->cobTextColor->currentIndex()]));
    p.setFont(QFont("Times", ui->spinFontSize->value(),
                    ui->chbIsBold->isChecked() ? QFont::Bold : QFont::Normal));
    p.drawText(image.rect(), Qt::AlignCenter, tr("Simple text"));
    p.end();

    ui->laResultImage->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_chbIsBold_stateChanged(int /*arg1*/)
{
    updatePreview();
}

void MainWindow::on_butSelectDirectory_clicked()
{
    _dstDirectory = QFileDialog::getExistingDirectory(this, tr("Select destination directory"),
                                                      QStandardPaths::writableLocation(QStandardPaths::PicturesLocation));
    ui->leResultDirectory->setText(_dstDirectory);
}

void MainWindow::on_butProcess_clicked()
{

}

void MainWindow::on_butPlus_clicked()
{

}

void MainWindow::on_butMinus_clicked()
{

}
