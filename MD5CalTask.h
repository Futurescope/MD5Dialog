#pragma once

#include <QObject>

class MD5CalTask :public QObject
{
	Q_OBJECT

public:
	MD5CalTask(QString strFilePath, int nIndex, QObject* parent = nullptr);
	int GetTaskIndex();

public slots:
	// doWork定义了线程要执行的操作
	void doWork();

signals:
	void currentProgress(int nIndex, double dProgress);
	void workFinished(int nIndex, QString strRes);

private:
	QString m_strFileName;
	int m_nIndex;
};

#if 0
/// \brief 回调函数
///
/// \param pCurrentView    当前Ui视图
/// \param pickedPt  Pick到的点(射线与工作平面的交点)
/// \param mousePt   鼠标点
typedef std::function<void(gcmp::IUiView* pCurrentView, const gcmp::Vector3d& pickedPt, const gcmp::Vector3d& mousePt)> MoveCallback;

/// \brief 创建回调函数
/// \param *func    T对象的函数指针
/// \param object  T对象
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