#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "utils/stdout_manager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog, public StdoutManager::OutputDelegate
{
	Q_OBJECT

public:
	Dialog(QWidget* parent = nullptr);
	~Dialog();


	void OnOutput(const QString&) override;

private slots:
	void on_pushButton_clicked();

private:
	Ui::Dialog* ui;
};
#endif // DIALOG_H
