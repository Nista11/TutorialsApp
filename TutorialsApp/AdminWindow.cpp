#include "AdminWindow.h"
#include <qmessagebox.h>
#include <qkeyevent>

void AdminWindow::keyPressEvent(QKeyEvent* event)
{
	if (event->keyCombination() == (Qt::CTRL | Qt::Key_Z))
	{
		emit undoPressed();
	}
	else if (event->keyCombination() == (Qt::CTRL | Qt::Key_Y))
	{
		emit redoPressed();
	}
}

AdminWindow::AdminWindow(QWidget* parent) : QWidget(parent), adminWindow(NULL)
{
}
