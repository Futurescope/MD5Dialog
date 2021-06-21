#pragma once

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>
#include <QString>

class FileListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    FileListModel(QObject *parent = nullptr);
    ~FileListModel();

    bool UpdateFileFolder(const QString& strFolder);
	void CalculateMD5(bool bOnlySelect = true);

public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value,int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    
	Qt::ItemFlags flags(const QModelIndex &index) const override;
};