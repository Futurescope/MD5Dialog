#pragma once

#include <QObject>

class MD5CalTask :public QObject
{
	Q_OBJECT

public:
	MD5CalTask(QString strFilePath, QObject* parent = nullptr);

public slots:
	// doWork�������߳�Ҫִ�еĲ���
	void doWork();

signals:
	void currentProgress(double dProgress);
	void workFinished(QString strRes);

private:
	QString m_strFileName;
};

#if 0
/// \brief �ص�����
///
/// \param pCurrentView    ��ǰUi��ͼ
/// \param pickedPt  Pick���ĵ�(�����빤��ƽ��Ľ���)
/// \param mousePt   ����
typedef std::function<void(gcmp::IUiView* pCurrentView, const gcmp::Vector3d& pickedPt, const gcmp::Vector3d& mousePt)> MoveCallback;

/// \brief �����ص�����
/// \param *func    T����ĺ���ָ��
/// \param object  T����
template<typename T>
static MoveCallback CreateMoveCallback(
	void (T::*func)(gcmp::IUiView*, const gcmp::Vector3d& pos, const gcmp::Vector3d& mousePt),
	T* object)
{
	if (object)
	{
		return std::bind(func, object, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	}
	return nullptr;
}
#endif