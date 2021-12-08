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

	/// brief: �����ļ���·�������б�
	/// param: strFolder �ļ���·��
    bool UpdateFileFolder(const QString& strFolder);

	/// brief: �����б���MD5
	/// param: bOnlySelect ֻ����ѡ����
	void CalculateMD5(int nRowIndex);

public slots:
	void SetProgress(int nIndex, double dProgress);

//���ؽӿ�
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