#include "npm_runner.h"
#include <QProcess>

static QString s_cli_path;

static QString GenerateOutputParam(const QString& output) {
	return QString("--out=%1").arg(output);
}

void NpmRunner::Run(const QStringList& cmds, const QString& output, NodeRunner::RunnerOutputDelegate delegate)
{
	QStringList runner_cmds = GenerateCommonCmds();
	runner_cmds.append(cmds);
	runner_cmds.append(GenerateOutputParam(output));
	NodeRunner::Run(runner_cmds, std::move(delegate));
}

QStringList NpmRunner::GenerateCommonCmds()
{
    if (s_cli_path.isEmpty()) {
        printf("cli is empty");
    }
	QStringList common_cmds;
	common_cmds.push_back(s_cli_path);
	return common_cmds;
}

void NpmRunner::SetCliPath(const QString &cli_path) {
    s_cli_path = cli_path;
}

