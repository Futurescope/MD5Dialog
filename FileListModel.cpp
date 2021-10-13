#include "FileListModel.h"
#include <QDir>
#include <QCryptographicHash>
#include <QDebug>



FileListModel::FileListModel(QObject *parent)
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
	m_md5Value.resize(m_fileList.size());
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
	QFile fileTemp(m_fileList.at(nRowIndex).filePath());
	QCryptographicHash crypto(QCryptographicHash::Md5);
	QString strRes;
	double nReadProgress = 0;
	if (fileTemp.open(QIODevice::ReadOnly))
	{
		long double nSize = fileTemp.size();
		while (!fileTemp.atEnd())
		{
			crypto.addData(fileTemp.read(8192));

			auto nRemains = fileTemp.bytesAvailable();
			nReadProgress = ((nSize - nRemains) * 100)/ nSize;
			qDebug() << nReadProgress;
			setData(index(nRowIndex, 1), nReadProgress, Qt::DisplayRole);
			emit dataChanged(index(nRowIndex, 1), index(nRowIndex, 1));
		}
	}
	else
	{
		qDebug() << "Can't open file.";
		strRes = "Can't open file.";
		return;
	}
	if (!strRes.isEmpty())
	{
		m_md5Value[nRowIndex] = "no file";
	}
	else
	{
		m_md5Value[nRowIndex] = crypto.result().toHex().toUpper();
	}
	fileTemp.close();
	emit dataChanged(index(nRowIndex, 1), index(nRowIndex, 1));
}

int FileListModel::rowCount(const QModelIndex & parent) const
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
			return m_md5Value.size() > nRowIndex ? m_md5Value.at(nRowIndex) : QVariant();
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
