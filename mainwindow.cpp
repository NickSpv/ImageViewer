#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  currentAngle = 0;
  timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::on_toolButton_5_clicked);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
  images.clear();
  this->setCurrentComboBoxValue(100);
  QString filePath = QFileDialog::getOpenFileName(this,
                                            tr("Open Image"), "/home/", tr("Image Files (*.png *.jpg *.bmp)"));
  currentPath = filePath.left(filePath.lastIndexOf('/'));
  QDir dir(currentPath);

  foreach(QFileInfo item, dir.entryInfoList() )
  {
    if(item.isFile())
    {
      QString localFilePath = item.absoluteFilePath();
      images.append(localFilePath);
      if (localFilePath == filePath) {
        currentImageIndex = images.size() - 1;
      }
    }
  }
  this->setCurrentImage(filePath);
}

void MainWindow::setCurrentImage(QString path)
{
  QPixmap pixmap(path);
  currentPixmap = pixmap;
  float imageHeight = this->ui->scrollArea->height();
  float imageWidth = this->ui->scrollArea->width();
  float currentHeight = pixmap.height();
  float currentWidth = pixmap.width();
  float scaleCoeff = (imageHeight / currentHeight) * 100 * 0.95;
  float scaleCoeff_1 = (imageWidth / currentWidth) * 100 * 0.95;
  scaleCoeff = (scaleCoeff > scaleCoeff_1 ? scaleCoeff_1 : scaleCoeff);
  std::cout << path.toStdString() << " " << imageHeight << " " << currentHeight << " " << scaleCoeff << " " << currentHeight * scaleCoeff / 100 << '\n';
  this->setCurrentComboBoxValue(scaleCoeff);
  this->on_comboBox_currentTextChanged("");
  this->updatePixmap();
}

void MainWindow::updatePixmap(){
  this->ui->image->setPixmap(currentPixmap);
}

int MainWindow::getCurrentComboBoxValue(){
  QString currentText = this->ui->comboBox->currentText();
  QString filtredCurrentText = "";
  for (auto i : currentText) {
    if (i >= '0' and i <= '9') {
      filtredCurrentText += i;
    }
  }
  return filtredCurrentText.toInt();
}

void MainWindow::setCurrentComboBoxValue(int size) {
  this->ui->comboBox->setCurrentText(QString::number(size) + "%");
}

void MainWindow::on_actionExit_triggered()
{
  this->close();
}


void MainWindow::on_toolButton_clicked()
{
  QTransform transform;
  currentPixmap = currentPixmap.transformed(transform.rotate(-90));
  this->updatePixmap();
  currentAngle -= 90;
  this->setCurrentImage(images[currentImageIndex]);
}


void MainWindow::on_toolButton_1_clicked()
{
  if (images.empty()) return;
  if (currentImageIndex == 0) currentImageIndex = images.size() - 1;
  else currentImageIndex--;
  this->setCurrentImage(images[currentImageIndex]);
}


void MainWindow::on_toolButton_5_clicked()
{
  if (images.empty()) return;
  if (currentImageIndex == images.size() - 1) currentImageIndex = 0;
  else currentImageIndex++;
  this->setCurrentImage(images[currentImageIndex]);
}


void MainWindow::on_toolButton_6_clicked()
{
  QTransform transform;
  currentPixmap = currentPixmap.transformed(transform.rotate(90));
  this->updatePixmap();
  currentAngle += 90;
  this->setCurrentImage(images[currentImageIndex]);
}


void MainWindow::on_toolButton_4_clicked()
{
  this->setCurrentComboBoxValue(this->getCurrentComboBoxValue() + 1);
}


void MainWindow::on_toolButton_3_clicked()
{
  this->setCurrentComboBoxValue(this->getCurrentComboBoxValue() - 1);
}


void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
  int scaleCoeff = this->getCurrentComboBoxValue();
  this->setCurrentComboBoxValue(scaleCoeff);
  if (images.empty()) return;
  currentPixmap = QPixmap(images[currentImageIndex]);
  QTransform transform;
  currentPixmap = currentPixmap.transformed(transform.rotate(currentAngle));
  currentPixmap = currentPixmap.scaled(QPixmap(images[currentImageIndex]).width() * scaleCoeff / 100,
                                       QPixmap(images[currentImageIndex]).height() * scaleCoeff / 100,
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);
  std::cout << "Flag" << '\n';
  this->updatePixmap();
}


void MainWindow::on_toolButton_2_clicked()
{
  if (timer->isActive()) {
    timer->stop();
    this->showNormal();
  } else {
    this->showFullScreen();
    timer->start(3000);
  }
}

