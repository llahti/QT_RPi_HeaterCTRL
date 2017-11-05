#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "dialog_settings.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    //dialog_settings *diag = new dialog_settings(this);
    //diag->show();


    //QMessageBox::warning(this,"..","Pressed a \"Asetukset\" Button");
}

void MainWindow::on_toolButton_2_clicked()
{
    QMessageBox::warning(this,"..","Pressed a \"Lisätiedot\" Button");
}
