#ifndef NODERUNNER_H
#define NODERUNNER_H
#include <QStringList>

class NodeRunner
{
public:
	static QString Run(const QStringList& cmds);
};

#endif // NODERUNNER_H
