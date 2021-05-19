#ifndef STDOUTMANAGER_H
#define STDOUTMANAGER_H
#include <QString>
#include <functional>
#include <set>
#include <QMutex>

class StdoutManager
{
public:
	class OutputDelegate {
	public:
		virtual void OnOutput(const QString&) = 0;
	};

	static StdoutManager& Instance();
	void AddDelegate(OutputDelegate* delegate);
	void RemoveDelegate(OutputDelegate* delegate);

private:
	StdoutManager();
	QMutex mutex_;
	std::set<OutputDelegate*> delegates_;
};

#endif // STDOUTMANAGER_H
