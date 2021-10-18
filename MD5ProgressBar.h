#pragma once
#include <QStyledItemDelegate>

class QProgressBar;

class MD5ProgressBar : public QStyledItemDelegate
{
	Q_OBJECT

public:
	MD5ProgressBar(QObject *parent = 0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};
