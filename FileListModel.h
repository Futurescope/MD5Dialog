#pragma once

#include <QAbstractTableModel>
#include <QStringList>
#include <QVector>
#include <QString>
#include <QFileInfoList>

class FileListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    FileListModel(QObject *parent = nullptr);
    ~FileListModel();

	/// brief: 根据文件夹路径更新列表
	/// param: strFolder 文件夹路径
    bool UpdateFileFolder(const QString& strFolder);

	/// brief: 计算列表项MD5
	/// param: bOnlySelect 只计算选中项
	void CalculateMD5(int nRowIndex);

public slots:
	void SetProgress(int nIndex, double dProgress);

//重载接口
public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant& value,int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    
	Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
	QVector<double> m_Progress;
	QFileInfoList m_fileList;
	QVector<QString> m_md5Value;
};