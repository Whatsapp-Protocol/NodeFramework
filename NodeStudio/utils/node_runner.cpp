#include "node_runner.h"
#include <QProcess>
#define MAX_WAITTIME 1000


QString NodeRunner::Run(const QStringList& cmds)
{
	QString result;
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
	QProcess npm;
	npm.start("node", cmds);
	npm.waitForFinished();
	QByteArray output = npm.readAllStandardOutput();
	return QString::fromStdString(output.toStdString());
#endif
	return result;
}
