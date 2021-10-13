#pragma once

#include <QtWidgets/QDialog>

namespace Ui
{
	class MD5DialogClass;
}

class MD5Dialog : public QDialog
{
	Q_OBJECT

public:
	MD5Dialog(QWidget *parent = Q_NULLPTR);
	~MD5Dialog();

private:
	void UpdateTabelList();
	void CalculateMd5(int nRowIndex);

private:
	QString m_strDir;
	Ui::MD5DialogClass* ui;
};
