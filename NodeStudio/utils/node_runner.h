#ifndef NODERUNNER_H
#define NODERUNNER_H
#include <QStringList>
#include <functional>

class NodeRunner
{
public:
	using RunnerOutputDelegate = std::function<void(const QString&)>;
	static void Run(const QStringList& cmds, RunnerOutputDelegate delegate = nullptr);
};

#endif // NODERUNNER_H
