#include "node_runner.h"
#include <thread>
#include <QMutex>
#include <QDir>
#include <QProcess>
#include <QUuid>
#include <QWaitCondition>
#ifdef Q_OS_IOS
#include <NodeMobile/NodeMobile.h>
#elif defined(Q_OS_ANDROID)
#include <node.h>
#endif

#define MAX_WAITTIME 60*60*1000


void NodeRunner::Run(const QStringList& cmds, RunnerOutputDelegate delegate)
{
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
	QProcess npm;
	npm.setProcessChannelMode(QProcess::MergedChannels);
	QDir tmp_dir = QDir::temp();
	QString tmp_path = tmp_dir.absoluteFilePath(QUuid::createUuid().toString(QUuid::Id128));
	npm.setStandardOutputFile(tmp_path);


	npm.start("node", cmds);
	npm.waitForStarted();
	QMutex mutex;
	QWaitCondition wait_condition;
	std::thread check([&]() {
		QFile input(tmp_path);
		if (!input.open(QIODevice::ReadOnly)) {
			return;
		}
		while (true)
		{
			QByteArray line = input.readLine();
			if (line.size() == 0) {
				mutex.lock();
				bool complete = wait_condition.wait(&mutex, 500);
				mutex.unlock();
				if (complete) {
					return;
				}
			}
			else {
				delegate(line.toStdString().c_str());
			}
		}
		});

	npm.waitForFinished(MAX_WAITTIME);
	mutex.lock();
	wait_condition.wakeAll();
	mutex.unlock();

	check.join();
	QFile::remove(tmp_path);
#else
    int c_arguments_size=0;
    
    //Compute byte size need for all arguments in contiguous memory.
    for (auto& cmd : cmds)
    {
        c_arguments_size+= cmd.size();
        c_arguments_size++; // for '\0'
    }
    
    //Stores arguments in contiguous memory.
    char* args_buffer=(char*)calloc(c_arguments_size, sizeof(char));
    
    //argv to pass into node.
    char* argv[cmds.size()];
    
    //To iterate through the expected start position of each argument in args_buffer.
    char* current_args_position=args_buffer;
    
    //Argc
    int argument_count=0;
    
    //Populate the args_buffer and argv.
    for (auto& cmd : cmds)
    {
        std::string current_argument = cmd.toStdString();
        
        //Copy current argument to its expected position in args_buffer
        strncpy(current_args_position, current_argument.c_str(), current_argument.length());
        
        //Save current argument start position in argv and increment argc.
        argv[argument_count]=current_args_position;
        argument_count++;
        
        //Increment to the next argument's expected position.
        current_args_position+=strlen(current_args_position)+1;
    }
    
    //Start node, with argc and argv.
#ifdef Q_OS_IOS
    node_start(argument_count,argv);
#else
    node::Start(argument_count, argv);
#endif
    free(args_buffer);
#endif
}
