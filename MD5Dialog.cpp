#include "ui_MD5Dialog.h"
#include "MD5Dialog.h"
#include "FileListModel.h"
#include "MD5ProgressBar.h"
#include <QFileDialog>

MD5Dialog::MD5Dialog(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::MD5DialogClass)
{
	ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);

	auto pModel = new FileListModel(this);
	ui->tbvFiles->setModel(pModel);
	ui->tbvFiles->verticalHeader()->setVisible(false);
	ui->tbvFiles->setColumnWidth(0, 160);
	ui->tbvFiles->setColumnWidth(1, 250);
	ui->tbvFiles->verticalHeader()->resizeSections(QHeaderView::Stretch);
	ui->tbvFiles->setSelectionMode(QAbstractItemView::MultiSelection);
	ui->tbvFiles->setSelectionBehavior(QAbstractItemView::SelectRows);
	auto pBar = new MD5ProgressBar(this);
	ui->tbvFiles->setItemDelegateForColumn(1, pBar);
	// 输入框
	connect(ui->letDir, &QLineEdit::editingFinished, this, [this]()
	{
		m_strDir = ui->letDir->text();
		UpdateTabelList();
	});
	// 读取文件夹
	connect(ui->pbtFolder, &QPushButton::clicked, this, [this]()
	{
		m_strDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), m_strDir,
			QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly | QFileDialog::DontResolveSymlinks);
		if (m_strDir.isEmpty())
		{
			m_strDir = QDir::homePath();
		}
		ui->letDir->setText(m_strDir);
		UpdateTabelList();
	});
	// 计算全部MD5
	// 计算选中项MD5
	connect(ui->pbtCalSelect, &QPushButton::clicked, this, [this]()
	{
		auto pModel = ui->tbvFiles->selectionModel();
		auto arrRows = pModel->selectedRows();
		for (auto iIndex : arrRows)
		{
			CalculateMd5(iIndex.row());
		}
	});
	m_strDir = QDir::homePath();
	ui->letDir->setText(m_strDir);
	UpdateTabelList();
}

MD5Dialog::~MD5Dialog()
{
	delete ui;
	ui = nullptr;
}

void MD5Dialog::UpdateTabelList()
{
	auto pModel = static_cast<FileListModel*>(ui->tbvFiles->model());
	pModel->UpdateFileFolder(m_strDir);
}

void MD5Dialog::CalculateMd5(int nRowIndex)
{
	auto pModel = static_cast<FileListModel*>(ui->tbvFiles->model());
	pModel->CalculateMD5(nRowIndex);
}
