#include "MD5Dialog.h"
#include "FileListModel.h"
#include <QFileDialog>

MD5Dialog::MD5Dialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
	
	auto pModel = new FileListModel(this);
	ui.tbvFiles->setModel(pModel);

	connect(ui.letDir, &QLineEdit::editingFinished, this, [this]()
	{
		m_strDir = ui.letDir->text();
		UpdateTabelList();
	});
	connect(ui.pbtFolder, &QPushButton::clicked, this, [this]()
	{
		m_strDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home/user/Documents",
			QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly | QFileDialog::DontResolveSymlinks);
		ui.letDir->setText(m_strDir);
		UpdateTabelList();
	});

}

void MD5Dialog::UpdateTabelList()
{
	auto pModel = static_cast<FileListModel*>(ui.tbvFiles->model());
	pModel->UpdateFileFolder(m_strDir);
}
