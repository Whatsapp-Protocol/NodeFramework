#ifndef NPMRUNNER_H
#define NPMRUNNER_H

#include <QStringList>
class NpmRunner
{
public:
	static QString Init(const QString& output);
	static QString Install(const QString& component, const QString& output);
	static QString UnInstall(const QString& component, const QString& output);
	static QString Update(const QString& output);

private:
	static QStringList GenerateCommonCmds();
};

#endif // NPMRUNNER_H
