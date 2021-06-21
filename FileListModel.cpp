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

	QFileInfoList list = dir.entryInfoList();

    return true;
}

void FileListModel::CalculateMD5(bool bOnlySelect)
{
}

int FileListModel::rowCount(const QModelIndex & parent) const
{
    return 0;
}

int FileListModel::columnCount(const QModelIndex & parent) const
{
    return 0;
}

QVariant FileListModel::data(const QModelIndex & index, int role) const
{
    return QVariant();
}

bool FileListModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    return false;
}

QVariant FileListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

Qt::ItemFlags FileListModel::flags(const QModelIndex & index) const
{
    return Qt::ItemFlags();
}
