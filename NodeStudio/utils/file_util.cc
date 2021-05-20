#include "file_util.h"
#include <QDirIterator>

BEGIN_NAMESPACE_FILE_UTIL

bool CopyDir(const QString& src, const QString& dest)
{
	QDirIterator dirIterator(src);
	QDir q_dest_dir(dest);
	q_dest_dir.mkpath(dest);
	while (dirIterator.hasNext()) {
		QFileInfo fileInfo = dirIterator.fileInfo();
		QString dest_path = q_dest_dir.absoluteFilePath(fileInfo.fileName());
		if (fileInfo.isFile())
		{
			//拷贝文件

			QFile::copy(fileInfo.absoluteFilePath(), dest_path);
			QFile::setPermissions(dest_path, (QFile::Permissions)0x777);
		}
		else if (fileInfo.isDir())
		{
			CopyDir(fileInfo.absoluteFilePath(), dest_path);
		}
		dirIterator.next();
	}
	return true;
}


END_NAMESPACE_FILE_UTIL

