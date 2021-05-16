#include "npm_runner.h"
#include "node_runner.h"
#include <QProcess>

static QString GetCliPath() {
	QString cli_path = "E:\\cli\\source\\bin\\npm-cli.js";
	return cli_path;
}

static QString GenerateOutputParam(const QString& output) {
	return QString("--out=%1").arg(output);
}

QString NpmRunner::Init(const QString& output)
{
	QStringList cmds = GenerateCommonCmds();
	cmds.push_back("init");
	cmds.push_back("-y");

	cmds.push_back(GenerateOutputParam(output));
	return NodeRunner::Run(cmds);
}

QString NpmRunner::Install(const QString& component, const QString& output)
{
	QStringList cmds = GenerateCommonCmds();
	cmds.push_back("install");
	if (!component.isEmpty())
	{
		cmds.push_back(component);
	}

	cmds.push_back(GenerateOutputParam(output));
	return NodeRunner::Run(cmds);
}

QString NpmRunner::UnInstall(const QString& component, const QString& output)
{
	QStringList cmds = GenerateCommonCmds();
	cmds.push_back("uninstall");
	cmds.push_back(component);

	cmds.push_back(GenerateOutputParam(output));
	return NodeRunner::Run(cmds);
}

QString NpmRunner::Update(const QString& output)
{
	QStringList cmds = GenerateCommonCmds();
	cmds.push_back("update");

	cmds.push_back(GenerateOutputParam(output));
	return NodeRunner::Run(cmds);
}


QStringList NpmRunner::GenerateCommonCmds()
{
	static QString cli_path = GetCliPath();

	QStringList common_cmds;
	common_cmds.push_back(cli_path);
	return common_cmds;
}
