#include "dialog.h"
#include <stdio.h>
#include <iostream>
#include "ui_dialog.h"
#include "utils/npm_runner.h"

void MyQtMessageHandler(QtMsgType,
                        const QMessageLogContext&,
                        const QString& content) {
  int a = 0;
}

Dialog::Dialog(QWidget* parent) : QDialog(parent), ui(new Ui::Dialog) {
  //qInstallMessageHandler(MyQtMessageHandler);
  ui->setupUi(this);
}

Dialog::~Dialog() {
  delete ui;
}

void Dialog::on_pushButton_clicked() {
    QString ab = NpmRunner::Init("e:\\t11es t121");
    qDebug() << ab;
    ab = NpmRunner::Install("fse", "e:\\t11es t121");
    qDebug() << ab;
    ab = NpmRunner::UnInstall("fse", "e:\\t11es t121");
    qDebug() << ab;
	ab = NpmRunner::Update("e:\\t11es t121");
	qDebug() << ab;
  std::cout << "aa";
}
