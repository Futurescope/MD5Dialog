#include "FileListModel.h"
#include "MD5CalTask.h"

#include <QDir>
#include <QCryptographicHash>
#include <QDebug>
#include <QThread>

FileListModel::FileListModel(QObject *parent)
	:QAbstractTableModel(parent)
{
}

FileListModel::~FileListModel()
{
}

bool FileListModel::UpdateFileFolder(const QString& strFolder)
{
	QDir dir(strFolder);
	if (!dir.exists())
	{
		return false;
	}
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	dir.setSorting(QDir::Name | QDir::IgnoreCase);

	beginResetModel();
	//重置model中的数据
	m_fileList = dir.entryInfoList();
	m_md5Value.fill("", m_fileList.size());
	m_Progress.fill(0, m_fileList.size());
	//数据设置结束后调用endResetModel，此时会触发modelReset信号
	endResetModel();

	return true;
}

void FileListModel::CalculateMD5(int nRowIndex)
{
	if (m_md5Value.size() <= nRowIndex)
	{
		return;
	}
	qDebug() << m_fileList.at(nRowIndex).filePath();
	// 开始计算线程
	MD5CalTask* pTask = new MD5CalTask(m_fileList.at(nRowIndex).filePath(), nRowIndex);
	QThread* pThread = new QThread;
	pTask->moveToThread(pThread);
	connect(pThread, &QThread::started, pTask, &MD5CalTask::doWork);
	connect(pTask, &MD5CalTask::currentProgress, this, &FileListModel::SetProgress);
	connect(pTask, &MD5CalTask::workFinished, this, [this, pThread](int nIndex, QString strTemp)
	{
		if (strTemp.isEmpty())
		{
			qDebug() << "ERROR";
			pThread->exit(0);
			pThread->wait();
			return;
		}
		SetProgress(nIndex, 0);
		m_md5Value[nIndex] = strTemp;
	});
	connect(pThread, &QThread::finished, pTask, &QObject::deleteLater);
	pThread->start();
	emit dataChanged(index(nRowIndex, 1), index(nRowIndex, 1));
}

void FileListModel::SetProgress(int nIndex, double dProgress)
{
	if (nIndex < 0 || nIndex >= m_fileList.size()) return;
	if (dProgress < 0 || dProgress > 1) return;
	m_Progress[nIndex] = dProgress;
	emit dataChanged(index(nIndex, 1), index(nIndex, 1));
}

int FileListModel::rowCount(const QModelIndex & parent) const
{
	return parent.isValid() ? 0 : m_fileList.size();
}

int FileListModel::rowCount() const
{
	return m_fileList.size();
}

int FileListModel::columnCount(const QModelIndex & parent) const
{
	return 4;
}

QVariant FileListModel::data(const QModelIndex & index, int role) const
{
	if (!index.isValid())
	{
		return QVariant();
	}
	if (role == Qt::TextAlignmentRole)
	{
		if (index.column() == 3)
		{
			return int(Qt::AlignHCenter | Qt::AlignVCenter);
		}
		return int(Qt::AlignLeft | Qt::AlignVCenter);
	}
	if (role == Qt::DisplayRole)
	{
		int nRowIndex = index.row();
		int nColIndex = index.column();
		switch (nColIndex)
		{
		default:
			return QVariant();
		case 0:
			return m_fileList.size() > nRowIndex ? m_fileList.at(nRowIndex).fileName() : QVariant();
		case 1:
		{
			if (qFuzzyIsNull(m_Progress.at(nRowIndex)))
				return m_md5Value.size() > nRowIndex ? m_md5Value.at(nRowIndex) : QVariant();
			return m_Progress.at(nRowIndex);
		}
		}
	}
	return QVariant();
}

bool FileListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
	return false;
}

QVariant FileListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		switch (section)
		{
		default:
			return QVariant();
		case 0:
			return tr(u8"文件");
		case 1:
			return tr(u8"MD5");
		case 2:
			return tr(u8"jsonKey");
		case 3:
			return tr(u8"对比结果");
		}
	}
	return QVariant();
}

Qt::ItemFlags FileListModel::flags(const QModelIndex & index) const
{
	return Qt::ItemIsSelectable + Qt::ItemIsEnabled;
}