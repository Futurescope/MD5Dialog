#include "MD5CalTask.h"
#include <QDir>
#include <QCryptographicHash>

MD5CalTask::MD5CalTask(QString strFilePath, QObject* parent /*= nullptr*/)
	:m_strFileName(strFilePath)
{

}

void MD5CalTask::doWork()
{
	QFile fileTemp(m_strFileName);
	QCryptographicHash crypto(QCryptographicHash::Md5);

	QString strRes;
	if (fileTemp.open(QIODevice::ReadOnly))
	{
		long double nSize = fileTemp.size();
		while (!fileTemp.atEnd())
		{
			crypto.addData(fileTemp.read(8192));

			auto nRemains = fileTemp.bytesAvailable();
			double dReadProgress = (nSize - nRemains) / nSize;
			emit currentProgress(dReadProgress);
		}
		strRes = crypto.result().toHex().toUpper();
	}
	fileTemp.close();
	emit workFinished(strRes);
}

