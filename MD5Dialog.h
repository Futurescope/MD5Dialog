#pragma once

#include <QtWidgets/QDialog>
#include "ui_MD5Dialog.h"

class MD5Dialog : public QDialog
{
	Q_OBJECT

public:
	MD5Dialog(QWidget *parent = Q_NULLPTR);

private:
	void UpdateTabelList();

private:
	QString m_strDir;
	Ui::MD5DialogClass ui;
};
