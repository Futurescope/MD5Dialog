#include "MD5Dialog.h"
#include "FileListModel.h"
#include <QFileDialog>

MD5Dialog::MD5Dialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
	
	auto pModel = new FileListModel(this);
	ui.tbvFiles->setModel(pModel);
	ui.tbvFiles->verticalHeader()->setVisible(false);
	//ui.tbvFiles->horizontalHeader()->resizeSections(QHeaderView::Stretch);
	ui.tbvFiles->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tbvFiles->setSelectionBehavior(QAbstractItemView::SelectRows);

	connect(ui.letDir, &QLineEdit::editingFinished, this, [this]()
	{
		m_strDir = ui.letDir->text();
		UpdateTabelList();
	});
	connect(ui.pbtFolder, &QPushButton::clicked, this, [this]()
	{
		m_strDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), m_strDir,
			QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly | QFileDialog::DontResolveSymlinks);
		if (m_strDir.isEmpty())
		{
			m_strDir = QDir::homePath();
		}
		ui.letDir->setText(m_strDir);
		UpdateTabelList();
	});
	m_strDir = QDir::homePath();
	ui.letDir->setText(m_strDir);
	UpdateTabelList();
}

void MD5Dialog::UpdateTabelList()
{
	auto pModel = static_cast<FileListModel*>(ui.tbvFiles->model());
	pModel->UpdateFileFolder(m_strDir);
}
