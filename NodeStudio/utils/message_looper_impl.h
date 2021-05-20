#ifndef MESSAGELOOPERIMPL_H
#define MESSAGELOOPERIMPL_H
#include <QThread>
#include <QTimer>
#include <set>
#include <namespace_define.h>

BEGIN_NAMESPACE_LOOPER
enum MessageLooperType { LooperType_UI, LooperType_WORK };
using Runable = std::function<void()>;


struct RunnableInfo {
	RunnableInfo(uint64_t expired_time, uint64_t id, Runable runnable) {
		this->expired_time = expired_time;
		this->id = id;
		this->runnable = std::move(runnable);
	}

	RunnableInfo(RunnableInfo&& other) {
		expired_time = other.expired_time;
		id = other.id;
		runnable = std::move(other.runnable);
	}

	RunnableInfo& operator=(RunnableInfo&& other) {
		expired_time = other.expired_time;
		id = other.id;
		runnable = std::move(other.runnable);
		return *this;
	}

	bool operator < (const RunnableInfo& other) const {
		if (expired_time == other.expired_time) {
			return id < other.id;
		}
		return expired_time < other.expired_time;
	}
	uint64_t expired_time;
	Runable  runnable;
	uint64_t id;
};

class MessageLooperImpl : QObject {
	Q_OBJECT
public:
	MessageLooperImpl(MessageLooperType type, const QString& name);
	~MessageLooperImpl();

	uint64_t PostRunable(Runable runable);
	uint64_t PostRunable(Runable runable, uint64_t timeout);

signals:
	void FireDoWork();
	void FireStartTimer(int);

private slots:
	void DoWork();
	void HandleStartTimer(int timeout);

private:
	void Wakeup(uint64_t expired_time);

private:
	QThread* work_thread_ = nullptr;
	QTimer* timer_ = nullptr;
	MessageLooperType type_ = LooperType_WORK;

	std::set<RunnableInfo> runable_set_;
	std::mutex runable_set_mutex_;
	uint64_t id_ = 0;
};

#endif  // MESSAGELOOPER_H
END_NAMESPACE_LOOPER
