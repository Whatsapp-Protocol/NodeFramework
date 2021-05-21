#ifndef NPMRUNNER_H
#define NPMRUNNER_H

#include "node_runner.h"
#include <QStringList>
class NpmRunner
{
public:
    static void SetCliPath(const QString& cli_path);
	static void Run(const QStringList& cmds, const QString& output, NodeRunner::RunnerOutputDelegate delegate = nullptr);
	
private:
	static QStringList GenerateCommonCmds();
};

#endif // NPMRUNNER_H
