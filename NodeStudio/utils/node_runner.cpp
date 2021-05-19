#include "node_runner.h"
#include <thread>
#include <QMutex>
#include <QDir>
#include <QProcess>
#include <QUuid>
#include <QWaitCondition>

#define MAX_WAITTIME 60*60*1000


void NodeRunner::Run(const QStringList& cmds, RunnerOutputDelegate delegate)
{
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
	QProcess npm;
	npm.setProcessChannelMode(QProcess::MergedChannels);
	QDir tmp_dir = QDir::temp();
	QString tmp_path = tmp_dir.absoluteFilePath(QUuid::createUuid().toString(QUuid::Id128));
	npm.setStandardOutputFile(tmp_path);


	npm.start("node", cmds);
	npm.waitForStarted();
	QMutex mutex;
	QWaitCondition wait_condition;
	std::thread check([&]() {
		QFile input(tmp_path);
		if (!input.open(QIODevice::ReadOnly)) {
			return;
		}
		while (true)
		{
			QByteArray line = input.readLine();
			if (line.size() == 0) {
				mutex.lock();
				bool complete = wait_condition.wait(&mutex, 500);
				mutex.unlock();
				if (complete) {
					return;
				}
			}
			else {
				delegate(line.toStdString().c_str());
			}
		}
		});

	npm.waitForFinished(MAX_WAITTIME);
	mutex.lock();
	wait_condition.wakeAll();
	mutex.unlock();

	check.join();
	QFile::remove(tmp_path);
#endif
}
