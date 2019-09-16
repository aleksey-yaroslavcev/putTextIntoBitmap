#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QPainter>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _colorMap[0] = Qt::white;
    _colorMap[1] = Qt::black;

    _batchJobModel.setColumnCount(2);
    _batchJobModel.setHeaderData(0, Qt::Horizontal, tr("Title"));
    _batchJobModel.setHeaderData(1, Qt::Horizontal, tr("File name base(without extension)"));
    ui->tableView->setModel(&_batchJobModel);
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

    ui->laResultImage->setPixmap(QPixmap::fromImage(getImage(tr("Simple text"))));
}

QImage MainWindow::getImage(const QString& title)
{
    QImage image(_fileName);
    QPainter p;
    if (!p.begin(&image))
        return image;

    p.setPen(QPen(_colorMap[ui->cobTextColor->currentIndex()]));
    p.setFont(QFont("Times", ui->spinFontSize->value(),
                    ui->chbIsBold->isChecked() ? QFont::Bold : QFont::Normal));
    p.drawText(image.rect(), Qt::AlignCenter, title);
    p.end();
    return image;
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
    QString title;
    QString fileName;
    for (int i = 0; i < _batchJobModel.rowCount(); ++i) {
        title = _batchJobModel.data(_batchJobModel.index(i, 0)).toString();
        fileName = _dstDirectory + "/" +
                   _batchJobModel.data(_batchJobModel.index(i, 1)).toString() + ".bmp";
        getImage(title).save(fileName);
    }
    QMessageBox::information(this, tr("Information"), tr("Done"));
}

void MainWindow::on_butPlus_clicked()
{
    int rowCount = _batchJobModel.rowCount();
    _batchJobModel.insertRow(rowCount);
    _batchJobModel.setData(_batchJobModel.index(rowCount, 0),
                           "SomeTitle" + QString::number(rowCount));
    _batchJobModel.setData(_batchJobModel.index(rowCount, 1),
                           "SomeFileName" + QString::number(rowCount));
}

void MainWindow::on_butMinus_clicked()
{
    int rowCount = _batchJobModel.rowCount();
    if (rowCount < 1)
        return;
    _batchJobModel.removeRow(_batchJobModel.rowCount() - 1);
}
