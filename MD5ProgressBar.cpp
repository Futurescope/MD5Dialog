#include "MD5ProgressBar.h"
#include <QStyleOptionProgressBar>
#include <QEvent>
#include <QApplication>
#include <QDebug>

MD5ProgressBar::MD5ProgressBar(QObject *parent /*= 0*/)
	:QStyledItemDelegate(parent)
{
	//QScopedPointer<QStyleOptionProgressBar> m_pBar(new QStyleOptionProgressBar());
	m_pBar = new QStyleOptionProgressBar();
	m_pBar->textAlignment = Qt::AlignCenter;
	m_pBar->maximum = 100;
	m_pBar->minimum = 0;
	m_pBar->textVisible = true;
}

void MD5ProgressBar::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (!index.isValid() || m_pBar == nullptr || qFuzzyIsNull(index.data().toDouble()))
	{
		return QStyledItemDelegate::paint(painter, option, index);
	}
	m_pBar->rect = option.rect;
	m_pBar->progress = index.data().toDouble() * 100;
	m_pBar->text = QString("%1%").arg(m_pBar->progress);

	QApplication::style()->drawControl(QStyle::CE_ProgressBar, m_pBar, painter);
}

bool MD5ProgressBar::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		return true;
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}
