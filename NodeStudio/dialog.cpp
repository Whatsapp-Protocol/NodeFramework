#include "dialog.h"
#include <iostream>
#include <QFile>
#include <QDir>
#include <thread>
#include "ui_dialog.h"
#include "utils/npm_runner.h"
#include <QStandardPaths>
#include "utils/file_util.h"
#include "utils/message_looper_impl.h"
#include <QMessageBox>


Dialog::Dialog(QWidget* parent) : QDialog(parent), ui(new Ui::Dialog) {
	ui->setupUi(this);
    StdoutManager::Instance().AddDelegate(this);
	QDir document_dir(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation));
    QString cli_dir = document_dir.absoluteFilePath("NodeStudio/cli");
    
    QString exist_path =document_dir.absoluteFilePath("NodeStudio/cli/exit_flag");
    if (!QFile::exists(exist_path)) {
        BASE_LOOPER::MessageLooperImpl::WorkLooper()->PostRunable([cli_dir, exist_path](){
            BASE_FILE_UTIL::CopyDir(":/assets/cli", cli_dir);
            QFile exist_file(exist_path);
            exist_file.open(QFile::Truncate | QFile::ReadWrite);
        });
    }
    QString cli_path = document_dir.absoluteFilePath("NodeStudio/cli/bin/npm-cli.js");
    NpmRunner::SetCliPath(cli_path);
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
    printf("aaa\r\n");
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

void Dialog::on_pushButton_2_clicked()
{
    printf("aaa\r\n");
    std::cout << "aa" << std::endl;
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();

}


void Dialog::on_pushButton_3_clicked(bool checked)
{
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.exec();
}

