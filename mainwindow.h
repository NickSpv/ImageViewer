#pragma once

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <QTransform>
#include <QPixmap>
#include <QTimer>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionOpen_triggered();
  void setCurrentImage(QString path);
  void updatePixmap();
  int getCurrentComboBoxValue();
  void setCurrentComboBoxValue(int text);

  void on_actionExit_triggered();

  void on_toolButton_clicked();

  void on_toolButton_1_clicked();

  void on_toolButton_5_clicked();

  void on_toolButton_6_clicked();

  void on_toolButton_4_clicked();

  void on_toolButton_3_clicked();

  void on_comboBox_currentTextChanged(const QString &arg1);

  void on_toolButton_2_clicked();

private:
  Ui::MainWindow *ui;
  QString currentPath;
  QList<QString> images;
  int currentImageIndex;
  QPixmap currentPixmap;
  int currentAngle;
  QTimer* timer;
};
