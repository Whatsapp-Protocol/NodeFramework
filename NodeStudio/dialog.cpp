#include "dialog.h"
#include <stdio.h>
#include <windows.h>
#include <QFile>
#include <QMutex>
#include <QWaitCondition>
#include <iostream>
#include <thread>
#include "ui_dialog.h"
#include "utils/npm_runner.h"

Dialog::Dialog(QWidget* parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  StdoutManager::Instance().AddDelegate(this);
}

Dialog::~Dialog() {
  delete ui;
}

void Dialog::OnOutput(const QString& outpu) {
  qDebug() << outpu;
}

void Dialog::on_pushButton_clicked() {
  /*{
                  QStringList cmds;
                  cmds.push_back("init");
                  cmds.push_back("-y");
                  QString ab = NpmRunner::Run(cmds, "e:\\t11es t121", [](const
  QString& output) { qDebug() << output;

                                  });
                  qDebug() << ab;
  }*/

  /*{
                  QStringList cmds;
                  cmds.push_back("install");
                  cmds.push_back("vue-cli");
                  NpmRunner::Run(cmds, "e:\\t11es t121", [](const QString&
  output) { qDebug() << output;

                                  });

  }*/
  // printf("aaa\r\n");
  std::cout << "aa" << std::endl;
  /*{
                  QStringList cmds;
                  cmds.push_back("uninstall");
                  cmds.push_back("fse");
                  QString ab = NpmRunner::Run(cmds, "e:\\t11es t121", [](const
  QString& output) { qDebug() << output;

                                  });
                  qDebug() << ab;
  }



  {
                  QStringList cmds;
                  cmds.push_back("update");
                  QString ab = NpmRunner::Run(cmds, "e:\\t11es t121", [](const
  QString& output) { qDebug() << output;

                                  });
                  qDebug() << ab;
  }*/
}
