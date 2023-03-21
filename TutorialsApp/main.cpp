#include "A1112.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton.h>
#include "Repository.h"
#include "Service.h"
#include "GUI.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Repository repository{};
	Service service{ repository };
	GUI gui{ service };
	gui.start(); 
	return a.exec();
}
