#include "message_looper_impl.h"
#include "time_util.h"
BEGIN_NAMESPACE_LOOPER
MessageLooperImpl::MessageLooperImpl(MessageLooperType type,
	const QString& name)
	: type_(type) {
	if (type == LooperType_UI) {
		work_thread_ = QThread::currentThread();
	}
	else {
		//工作线程设置线程名
		work_thread_ = new QThread;
		work_thread_->setObjectName(name);
	}
	//将对象和线程关联，这样可以抛消息到线程
	moveToThread(work_thread_);
	//连接DoWork 信号槽
	connect(this, SIGNAL(FireDoWork()), this, SLOT(DoWork()), Qt::QueuedConnection);
	//连接启动定时器信号槽
	connect(this, SIGNAL(FireStartTimer(int)), this, SLOT(HandleStartTimer(int)));

	//连接定时器信号
	timer_ = new QTimer;
	timer_->setSingleShot(true);
	timer_->moveToThread(work_thread_);
	connect(timer_, SIGNAL(timeout()), this, SLOT(DoWork()));


	if (type != LooperType_UI) {
		work_thread_->start();
	}
}

MessageLooperImpl::~MessageLooperImpl() {
	if (type_ != LooperType_UI) {
		work_thread_->quit();
		work_thread_->wait();
		delete work_thread_;
	}
	delete timer_;
	std::lock_guard<std::mutex> lock(runable_set_mutex_);
	runable_set_.clear();
}

uint64_t MessageLooperImpl::PostRunable(Runable runable) {
	return PostRunable(std::move(runable), 0);
}

uint64_t MessageLooperImpl::PostRunable(Runable runable, uint64_t timeout) {
	uint64_t expired_time = BASE_TIME::GetTickCount2() + timeout;
	uint64_t id = 0;
	bool wakeup = false;
	{
		std::lock_guard<std::mutex> lock(runable_set_mutex_);
		id = ++id_;
		if (runable_set_.empty() ||
			(expired_time < runable_set_.begin()->expired_time)) {
			wakeup = true;
		}
		RunnableInfo runable_info(expired_time, id, std::move(runable));
		runable_set_.insert(std::move(runable_info));
	}
	if (wakeup) {
		Wakeup(expired_time);
	}
	return id;
}

void MessageLooperImpl::DoWork() {
	//遍历已经到期的所有runable，挨个执行
	uint64_t now = BASE_TIME::GetTickCount2();
	std::vector<Runable> runnables;
	{
		//set 中是按时间顺序排列，取到不符合的直接break就可以
		std::lock_guard<std::mutex> lock(runable_set_mutex_);
		for (auto begin = runable_set_.begin(); begin != runable_set_.end();) {
			if (begin->expired_time <= now) {
				runnables.push_back(std::move(begin->runnable));
				begin = runable_set_.erase(begin);
			}
			else {
				break;
			}
		}
	}
	for (auto& runable : runnables) {
		runable();
	}
	//唤醒下一个
	{
		std::lock_guard<std::mutex> lock(runable_set_mutex_);
		if (!runable_set_.empty()) {
			Wakeup(runable_set_.begin()->expired_time);
		}
	}
}

//启动定时器
void MessageLooperImpl::HandleStartTimer(int timeout)
{
	timer_->start(timeout);
}

void MessageLooperImpl::Wakeup(uint64_t expired_time)
{
	auto now = BASE_TIME::GetTickCount2();
	if (expired_time > now) {
		emit FireStartTimer((int)(expired_time - now));
	}
	else {
		//已经到期了，直接抛一个异步任务
		emit FireDoWork();
    }
}

END_NAMESPACE_LOOPER
