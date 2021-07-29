#include "FileListModel.h"
#include <QDir>

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
	//����model�е�����
	m_fileList = dir.entryInfoList();
	//�������ý��������endResetModel����ʱ�ᴥ��modelReset�ź�
	endResetModel();

    return true;
}

void FileListModel::CalculateMD5(bool bOnlySelect)
{
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
			return tr(u8"�ļ�");
		case 1:
			return tr(u8"MD5");
		case 2:
			return tr(u8"jsonKey");
		case 3:
			return tr(u8"�ԱȽ��");
		}
	}
	return QVariant();
}

Qt::ItemFlags FileListModel::flags(const QModelIndex & index) const
{
    return Qt::ItemIsSelectable + Qt::ItemIsEnabled;
}
