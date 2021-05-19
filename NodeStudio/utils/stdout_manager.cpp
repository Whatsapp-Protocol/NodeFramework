#include "stdout_manager.h"
#include <QDir>
#include <QFile>
#include <QMutexLocker>
#include <QThread>
#include <QUuid>
#include <thread>

StdoutManager& StdoutManager::Instance() {
  static StdoutManager single_ton;
  return single_ton;
}

void StdoutManager::AddDelegate(OutputDelegate* delegate) {
  QMutexLocker lock(&mutex_);
  delegates_.insert(delegate);
}

void StdoutManager::RemoveDelegate(OutputDelegate* delegate) {
  QMutexLocker lock(&mutex_);
  delegates_.erase(delegate);
}

StdoutManager::StdoutManager() {
  std::thread intercept([=]() {
    QDir tmp_dir = QDir::temp();
    QString tmp_path =
        tmp_dir.absoluteFilePath(QUuid::createUuid().toString(QUuid::Id128));

    FILE* stream = freopen(tmp_path.toStdString().c_str(), "w+", stdout);
    setvbuf(stream, 0, _IONBF, 0);

    QFile input(tmp_path);
    if (!input.open(QIODevice::ReadOnly)) {
      return;
    }

    while (true) {
      QByteArray line = input.readLine();
      if (line.length() == 0) {
        QThread::msleep(200);
      } else {
        QMutexLocker lock(&mutex_);
        for (auto item : delegates_) {
          item->OnOutput(line.toStdString().c_str());
        }
      }
    }
  });
  intercept.detach();
}
