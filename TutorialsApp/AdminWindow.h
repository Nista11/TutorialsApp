#pragma once
#include <qwidget.h>
class AdminWindow : public QWidget, public QObject
{
	Q_OBJECT
protected:
	void keyPressEvent(QKeyEvent* event);
public:
	QWidget* adminWindow;
	AdminWindow(QWidget* parent = Q_NULLPTR);
signals:
	void redoPressed();
	void undoPressed();
};

