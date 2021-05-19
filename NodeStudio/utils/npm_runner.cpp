#include "npm_runner.h"
#include <QProcess>

static QString GetCliPath() {
	QString cli_path = "E:\\cli\\source\\bin\\npm-cli.js";
	return cli_path;
}

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
	static QString cli_path = GetCliPath();

	QStringList common_cmds;
	common_cmds.push_back(cli_path);
	return common_cmds;
}
