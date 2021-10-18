#include "MD5ProgressBar.h"
#include <QStyleOptionProgressBar>
#include <QEvent>
#include <QApplication>

MD5ProgressBar::MD5ProgressBar(QObject *parent /*= 0*/)
{
	//m_pBar = new QStyleOptionProgressBar(parent);
}

void MD5ProgressBar::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	if (!index.isValid())
	{
		return QStyledItemDelegate::paint(painter, option, index);
	}
	
	QStyleOptionProgressBar bar;
	bar.textAlignment = Qt::AlignCenter;
	bar.rect = option.rect;
	bar.maximum = 100;
	bar.minimum = 0;
	bar.textVisible = true;
	bar.text = QString("%1%").arg(bar.progress);	
	bar.progress = index.data().toDouble();

	QApplication::style()->drawControl(QStyle::CE_ProgressBar, &bar, painter);
}

bool MD5ProgressBar::editorEvent(QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index)
{
	if (event->type() == QEvent::MouseButtonDblClick)
	{
		return true;
	}
	return QStyledItemDelegate::editorEvent(event, model, option, index);
}
