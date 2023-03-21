#include "GUI.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton.h>
#include <QtWidgets/QFormLayout.h>
#include <QtWidgets/QLineEdit.h>
#include <QtWidgets/QMessageBox.h>
#include <qwidget.h>
#include <QKeyEvent>
#include <qshortcut.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define BUTTON_HEIGHT 50

GUI::GUI(Service& service, QWidget* parent) : QWidget(parent), service(service), startWindow(NULL), adminWindow(NULL),
tutorialTable(NULL), addTutorialWindow(NULL), likesTextBox(NULL), linkTextBox(NULL), minutesTextBox(NULL),
presenterTextBox(NULL), secondsTextBox(NULL), titleTextBox(NULL), 
isWatchListSavedCSV(false), isWatchListSavedHTML(false), csvFormat(false)
{
}

void GUI::start()
{
	this->service.readTutorialsFromFile();
	this->initStartWindow();
	this->initAdminWindow();
	this->initAddTutorialWindow();
	this->initUpdateTutorialWindow();
	this->initDeleteTutorialWindow();
	this->initStorageFormatWindow();
	this->initUserWindow();
	this->initSeeTutorialsWindow();
	this->initWatchListWindow();
	this->initDeleteWatchListTutorialWindow();
	new QShortcut(QKeySequence(Qt::Key_8), this, SLOT(QApplication::quit()));
	this->startWindow->show();
}

void GUI::initStartWindow()
{
	this->startWindow = new QWidget{};
	QVBoxLayout* vLay = new QVBoxLayout{};
	QPushButton* btn0 = new QPushButton{ "Exit" };
	QPushButton* btn1 = new QPushButton{ "Administrator" };
	QPushButton* btn2 = new QPushButton{ "User" };
	btn0->setFixedHeight(BUTTON_HEIGHT);
	btn1->setFixedHeight(BUTTON_HEIGHT);
	btn2->setFixedHeight(BUTTON_HEIGHT);
	vLay->addWidget(btn1);
	vLay->addWidget(btn2);
	vLay->addWidget(btn0);
	this->startWindow->setFixedWidth(WINDOW_WIDTH);
	this->startWindow->setFixedHeight(WINDOW_HEIGHT);
	this->startWindow->setLayout(vLay);
	this->startWindow->setWindowTitle("C++ Tutorials");
	QObject::connect(btn0, &QPushButton::clicked, this, &QApplication::quit);
	QObject::connect(btn0, &QPushButton::clicked, this, &GUI::saveTutorialsToFile);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::adminButtonClicked);
	QObject::connect(btn2, &QPushButton::clicked, this, &GUI::userButtonClicked);
}

void GUI::adminButtonClicked()
{
	this->adminWindow->show();
	this->startWindow->hide();
}

void GUI::userButtonClicked()
{
	this->storageFormatWindow->show();
	this->startWindow->hide();
}

void GUI::undoButtonClicked()
{
	bool retVal = this->service.undo();
	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");
	if (retVal)
		msgBox->setText("Undo succesful");
	else
		msgBox->setText("Cannot undo!");
	msgBox->exec();
}

void GUI::redoButtonClicked()
{
	bool retVal = this->service.redo();
	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");
	if (retVal)
		msgBox->setText("Redo succesful");
	else
		msgBox->setText("Cannot redo!");
	msgBox->exec();
}

void GUI::initAdminWindow()
{
	this->adminWindow = new AdminWindow{};
	QVBoxLayout* vLay = new QVBoxLayout{};
	QPushButton* btn0 = new QPushButton{ "Exit" };
	QPushButton* btn1 = new QPushButton{ "Show all tutorials" };
	QPushButton* btn2 = new QPushButton{ "Add tutorial" };
	QPushButton* btn3 = new QPushButton{ "Update tutorial" };
	QPushButton* btn4 = new QPushButton{ "Delete tutorial" };
	QPushButton* btn5 = new QPushButton{ "Undo" };
	QPushButton* btn6 = new QPushButton{ "Redo" };
	btn0->setFixedHeight(BUTTON_HEIGHT);
	btn1->setFixedHeight(BUTTON_HEIGHT);
	btn2->setFixedHeight(BUTTON_HEIGHT);
	btn3->setFixedHeight(BUTTON_HEIGHT);
	btn4->setFixedHeight(BUTTON_HEIGHT);
	btn5->setFixedHeight(BUTTON_HEIGHT);
	btn6->setFixedHeight(BUTTON_HEIGHT);
	vLay->addWidget(btn1);
	vLay->addWidget(btn2);
	vLay->addWidget(btn3);
	vLay->addWidget(btn4);
	vLay->addWidget(btn5);
	vLay->addWidget(btn6);
	vLay->addWidget(btn0);
	this->adminWindow->setFixedWidth(WINDOW_WIDTH);
	this->adminWindow->setFixedHeight(WINDOW_HEIGHT);
	this->adminWindow->setLayout(vLay);
	this->adminWindow->setWindowTitle("C++ Tutorials");
	QObject::connect(btn0, &QPushButton::clicked, this, &GUI::adminExitButtonClicked);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::showTutorialsButtonClicked);
	QObject::connect(btn2, &QPushButton::clicked, this, &GUI::addTutorialButtonClicked);
	QObject::connect(btn3, &QPushButton::clicked, this, &GUI::updateTutorialButtonClicked);
	QObject::connect(btn4, &QPushButton::clicked, this, &GUI::deleteTutorialButtonClicked);
	QObject::connect(btn5, &QPushButton::clicked, this, &GUI::undoButtonClicked);
	QObject::connect(btn6, &QPushButton::clicked, this, &GUI::redoButtonClicked);
	QObject::connect(this->adminWindow, &AdminWindow::undoPressed, this, &GUI::undoButtonClicked);
	QObject::connect(this->adminWindow, &AdminWindow::redoPressed, this, &GUI::redoButtonClicked);
}

void GUI::adminExitButtonClicked()
{
	this->startWindow->show();
	this->adminWindow->hide();
}

void GUI::saveTutorialsToFile()
{
	this->service.saveTutorialsToFile();
}

void GUI::initTutorialTable()
{
	this->tutorialTableWindow = new QWidget{};
	
	QVBoxLayout* layout = new QVBoxLayout{};
	this->tutorialTable = new QTableWidget{ this->service.getSize(), 5};
	this->filterTutorialsTextBox = new QLineEdit{};
	this->tutorialTable->setFixedWidth(WINDOW_WIDTH * 1.26);
	this->tutorialTable->setFixedHeight(WINDOW_HEIGHT);
	this->tutorialTable->setHorizontalHeaderLabels(QStringList{ "Title", "Presenter", "Link", "Duration", "Likes" });
	std::vector<Tutorial> tutorials = this->service.getTutorials();
	for (int i = 0; i < tutorials.size(); i++)
	{
		this->tutorialTable->setItem(i, 0, new QTableWidgetItem(tutorials[i].getTitle().c_str()));
		this->tutorialTable->setItem(i, 1, new QTableWidgetItem(tutorials[i].getPresenter().c_str()));
		this->tutorialTable->setItem(i, 2, new QTableWidgetItem(tutorials[i].getLink().c_str()));
		this->tutorialTable->setItem(i, 3, new QTableWidgetItem(tutorials[i].getDuration().toString().c_str()));
		this->tutorialTable->setItem(i, 4, new QTableWidgetItem(std::to_string(tutorials[i].getLikes()).c_str()));
		for (int j = 0; j < 5; j++)
		{
			QLinearGradient gradient(0, 0, 50, 50);
			gradient.setColorAt(0, QColor::fromRgbF(1, 0, 0, 1));
			gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
			QBrush brush(gradient);
			this->tutorialTable->item(i, j)->setBackground(brush);
		}
	}
	
	QObject::connect(filterTutorialsTextBox, &QLineEdit::textChanged, this, &GUI::filterTutorialsTextChanged);
	layout->addWidget(this->filterTutorialsTextBox);
	layout->addWidget(this->tutorialTable);
	this->tutorialTableWindow->setLayout(layout);
	this->tutorialTableWindow->setFixedWidth(WINDOW_WIDTH * 1.3);
	this->tutorialTableWindow->setFixedHeight(WINDOW_HEIGHT * 1.1);
	this->tutorialTableWindow->setWindowTitle("Tutorials");
}

void GUI::filterTutorialsTextChanged()
{
	std::string filterString = this->filterTutorialsTextBox->text().toStdString();
	this->tutorialTable->clear();
	this->tutorialTable->setHorizontalHeaderLabels(QStringList{ "Title", "Presenter", "Link", "Duration", "Likes" });
	std::vector<Tutorial> tutorials = this->service.getFilteredTutorials(filterString);
	for (int i = 0; i < tutorials.size(); i++)
	{
		this->tutorialTable->setItem(i, 0, new QTableWidgetItem(tutorials[i].getTitle().c_str()));
		this->tutorialTable->setItem(i, 1, new QTableWidgetItem(tutorials[i].getPresenter().c_str()));
		this->tutorialTable->setItem(i, 2, new QTableWidgetItem(tutorials[i].getLink().c_str()));
		this->tutorialTable->setItem(i, 3, new QTableWidgetItem(tutorials[i].getDuration().toString().c_str()));
		this->tutorialTable->setItem(i, 4, new QTableWidgetItem(std::to_string(tutorials[i].getLikes()).c_str()));
		for (int j = 0; j < 5; j++)
		{
			QLinearGradient gradient(0, 0, 50, 50);
			gradient.setColorAt(0, QColor::fromRgbF(1, 0, 0, 1));
			gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
			QBrush brush(gradient);
			this->tutorialTable->item(i, j)->setBackground(brush);
		}
	}
}

void GUI::showTutorialsButtonClicked()
{
	this->initTutorialTable();
	this->tutorialTableWindow->show();
}

void GUI::addTutorialButtonClicked()
{
	this->addTutorialWindow->show();
}

void GUI::initAddTutorialWindow()
{
	this->addTutorialWindow = new QWidget{};
	this->addTutorialWindow->setWindowTitle("Add tutorial");
	QFormLayout* formLayout = new QFormLayout{};

	this->titleTextBox = new QLineEdit{};
	QLabel* titleLabel = new QLabel{ "Title:" };
	titleLabel->setBuddy(titleTextBox);

	this->presenterTextBox = new QLineEdit{};
	QLabel* presenterLabel = new QLabel{ "Presenter:" };
	presenterLabel->setBuddy(presenterTextBox);

	this->linkTextBox = new QLineEdit{};
	QLabel* linkLabel = new QLabel{ "Link:" };
	linkLabel->setBuddy(linkTextBox);

	this->minutesTextBox = new QLineEdit{};
	QLabel* minutesLabel = new QLabel{ "Minutes:" };
	minutesLabel->setBuddy(minutesTextBox);

	this->secondsTextBox = new QLineEdit{};
	QLabel* secondsLabel = new QLabel{ "Seconds:" };
	secondsLabel->setBuddy(secondsTextBox);

	this->likesTextBox = new QLineEdit{};
	QLabel* likesLabel = new QLabel{ "Likes:" };
	likesLabel->setBuddy(likesTextBox);

	QPushButton* btn1 = new QPushButton{ "Add" };
	btn1->setFixedHeight(BUTTON_HEIGHT);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::realAddTutorialButtonClicked);

	formLayout->addRow(titleLabel, titleTextBox);
	formLayout->addRow(presenterLabel, presenterTextBox);
	formLayout->addRow(linkLabel, linkTextBox);
	formLayout->addRow(minutesLabel, minutesTextBox);
	formLayout->addRow(secondsLabel, secondsTextBox);
	formLayout->addRow(likesLabel, likesTextBox);
	formLayout->addWidget(btn1);


	this->addTutorialWindow->setFixedWidth(WINDOW_WIDTH / 2);
	this->addTutorialWindow->setFixedHeight(WINDOW_HEIGHT / 2);
	this->addTutorialWindow->setLayout(formLayout);
}

void GUI::realAddTutorialButtonClicked()
{
	std::string title, presenter, link;
	int minutes = 0, seconds = 0, likes = 0;
	title = this->titleTextBox->text().toStdString();
	presenter = this->presenterTextBox->text().toStdString();
	link = this->linkTextBox->text().toStdString();
	minutes = this->minutesTextBox->text().toInt();
	seconds = this->secondsTextBox->text().toInt();
	likes = this->likesTextBox->text().toInt();
	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");
	bool result = this->service.addTutorial(title, presenter, link, likes, Duration{ minutes, seconds });
	if (result)
	{
		msgBox->setText("Tutorial added!");
	}

	else
	{
		msgBox->setText("Tutorial already exists / invalid input!");
	}
	msgBox->exec();
}

void GUI::initUpdateTutorialWindow()
{
	this->updateTutorialWindow = new QWidget{};
	this->updateTutorialWindow->setWindowTitle("Update tutorial");
	QFormLayout* formLayout = new QFormLayout{};

	this->updateLinkTextBox = new QLineEdit{};
	QLabel* linkLabel = new QLabel{ "Current link:" };
	linkLabel->setBuddy(updateLinkTextBox);

	this->updateTitleTextBox = new QLineEdit{};
	QLabel* titleLabel = new QLabel{ "New title:" };
	titleLabel->setBuddy(updateTitleTextBox);

	this->updatePresenterTextBox = new QLineEdit{};
	QLabel* presenterLabel = new QLabel{ "New presenter:" };
	presenterLabel->setBuddy(updatePresenterTextBox);

	this->updateNewLinkTextBox = new QLineEdit{};
	QLabel* newLinkLabel = new QLabel{ "New link:" };
	newLinkLabel->setBuddy(updateNewLinkTextBox);

	this->updateMinutesTextBox = new QLineEdit{};
	QLabel* minutesLabel = new QLabel{ "New minutes:" };
	minutesLabel->setBuddy(updateMinutesTextBox);

	this->updateSecondsTextBox = new QLineEdit{};
	QLabel* secondsLabel = new QLabel{ "New seconds:" };
	secondsLabel->setBuddy(updateSecondsTextBox);

	this->updateLikesTextBox = new QLineEdit{};
	QLabel* likesLabel = new QLabel{ "New likes:" };
	likesLabel->setBuddy(updateLikesTextBox);

	QPushButton* btn1 = new QPushButton{ "Update" };
	btn1->setFixedHeight(BUTTON_HEIGHT);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::realUpdateTutorialButtonClicked);

	formLayout->addRow(linkLabel, updateLinkTextBox);
	formLayout->addRow(titleLabel, updateTitleTextBox);
	formLayout->addRow(presenterLabel, updatePresenterTextBox);
	formLayout->addRow(newLinkLabel, updateNewLinkTextBox);
	formLayout->addRow(minutesLabel, updateMinutesTextBox);
	formLayout->addRow(secondsLabel, updateSecondsTextBox);
	formLayout->addRow(likesLabel, updateLikesTextBox);
	formLayout->addWidget(btn1);

	this->updateTutorialWindow->setFixedWidth(WINDOW_WIDTH / 2);
	this->updateTutorialWindow->setFixedHeight(WINDOW_HEIGHT / 1.5);
	this->updateTutorialWindow->setLayout(formLayout);
}

void GUI::updateTutorialButtonClicked()
{
	this->updateTutorialWindow->show();
}

void GUI::realUpdateTutorialButtonClicked()
{
	std::string title, presenter, link, newLink;
	int minutes = 0, seconds = 0, likes = 0;
	link = this->updateLinkTextBox->text().toStdString();
	title = this->updateTitleTextBox->text().toStdString();
	presenter = this->updatePresenterTextBox->text().toStdString();
	newLink = this->updateNewLinkTextBox->text().toStdString();
	minutes = this->updateMinutesTextBox->text().toInt();
	seconds = this->updateSecondsTextBox->text().toInt();
	likes = this->updateLikesTextBox->text().toInt();

	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");
	bool result = (this->service.find(Tutorial{ link }) != -1);
	if (result)
	{
		result = this->service.updateTutorial(link, title, presenter, newLink, likes, Duration{ minutes, seconds });
	}

	if (result)
	{
		msgBox->setText("Tutorial updated!");
	}

	else
	{
		msgBox->setText("Tutorial does not exist / invalid input!");
	}
	msgBox->exec();
}

void GUI::initStorageFormatWindow()
{
	this->storageFormatWindow = new QWidget{};
	QVBoxLayout* vLay = new QVBoxLayout{};
	QPushButton* btn1 = new QPushButton{ "HTML storage format" };
	QPushButton* btn2 = new QPushButton{ "CSV storage format" };
	btn1->setFixedHeight(BUTTON_HEIGHT);
	btn2->setFixedHeight(BUTTON_HEIGHT);
	vLay->addWidget(btn1);
	vLay->addWidget(btn2);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::htmlButtonClicked);
	QObject::connect(btn2, &QPushButton::clicked, this, &GUI::csvButtonClicked);
	this->storageFormatWindow->setFixedWidth(WINDOW_WIDTH);
	this->storageFormatWindow->setFixedHeight(WINDOW_HEIGHT);
	this->storageFormatWindow->setLayout(vLay);
	this->storageFormatWindow->setWindowTitle("Storage format");
}

void GUI::htmlButtonClicked()
{
	this->csvFormat = false;
	this->userWindow->show();
	this->storageFormatWindow->hide();
}

void GUI::csvButtonClicked()
{
	this->csvFormat = true;
	this->userWindow->show();
	this->storageFormatWindow->hide();
}

void GUI::initUserWindow()
{
	this->userWindow = new QWidget{};
	QVBoxLayout* vLay = new QVBoxLayout{};
	QPushButton* btn1 = new QPushButton{ "See all tutorials with a given presenter" };
	QPushButton* btn2 = new QPushButton{ "Save watch list" };
	QPushButton* btn3 = new QPushButton{ "Opened saved watch list" };
	QPushButton* btn0 = new QPushButton{ "Exit" };
	btn0->setFixedHeight(BUTTON_HEIGHT);
	btn1->setFixedHeight(BUTTON_HEIGHT);
	btn2->setFixedHeight(BUTTON_HEIGHT);
	btn3->setFixedHeight(BUTTON_HEIGHT);
	QObject::connect(btn0, &QPushButton::clicked, this, &GUI::userExitButtonClicked);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::userSeeTutorialsButtonClicked);
	QObject::connect(btn2, &QPushButton::clicked, this, &GUI::userSaveWatchListButtonClicked);
	QObject::connect(btn3, &QPushButton::clicked, this, &GUI::userOpenSavedWatchListButtonClicked);
	vLay->addWidget(btn1);
	vLay->addWidget(btn2);
	vLay->addWidget(btn3);
	vLay->addWidget(btn0);
	this->userWindow->setFixedWidth(WINDOW_WIDTH);
	this->userWindow->setFixedHeight(WINDOW_HEIGHT);
	this->userWindow->setLayout(vLay);
	this->userWindow->setWindowTitle("C++ tutorials");
}

void GUI::userExitButtonClicked()
{
	this->startWindow->show();
	this->userWindow->hide();
}

void GUI::userSeeTutorialsButtonClicked()
{
	this->seeTutorialsWindow->show();
	this->userWindow->hide();
}

void GUI::userSaveWatchListButtonClicked()
{
	this->service.saveWatchList(this->csvFormat);
	if (this->csvFormat)
		this->isWatchListSavedCSV = true;
	else
		this->isWatchListSavedHTML = true;
	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");
	std::string s = "Watch list saved to ";
	s += ((this->csvFormat) ? "csv format!" : "html format!");
	msgBox->setText(s.c_str());
	msgBox->exec();
}

void GUI::userOpenSavedWatchListButtonClicked()
{
	if ((this->csvFormat && !this->isWatchListSavedCSV) || (!this->csvFormat && !this->isWatchListSavedHTML))
	{
		QMessageBox* msgBox = new QMessageBox{};
		msgBox->setWindowTitle("Result");
		msgBox->setText("Watch list is not saved in the current format!");
		msgBox->exec();
	}
	else
	{
		this->service.openWatchList(this->csvFormat);
	}
}

void GUI::initDeleteTutorialWindow()
{
	this->deleteTutorialWindow = new QWidget{};
	this->deleteTutorialWindow->setWindowTitle("Delete tutorial");
	QFormLayout* formLayout = new QFormLayout{};

	this->deleteLinkTextBox = new QLineEdit{};
	QLabel* linkLabel = new QLabel{ "Link:" };
	linkLabel->setBuddy(deleteLinkTextBox);

	QPushButton* btn1 = new QPushButton{ "Delete" };
	btn1->setFixedHeight(BUTTON_HEIGHT);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::realDeleteTutorialButtonClicked);

	formLayout->addRow(linkLabel, deleteLinkTextBox);
	formLayout->addWidget(btn1);

	this->deleteTutorialWindow->setFixedWidth(WINDOW_WIDTH / 2);
	this->deleteTutorialWindow->setFixedHeight(WINDOW_HEIGHT / 2);
	this->deleteTutorialWindow->setLayout(formLayout);
}

void GUI::deleteTutorialButtonClicked()
{
	this->deleteTutorialWindow->show();
}

void GUI::realDeleteTutorialButtonClicked()
{
	std::string link;
	link = this->deleteLinkTextBox->text().toStdString();
	bool result = this->service.deleteTutorial(link);
	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");
	if (result)
	{
		msgBox->setText("Tutorial deleted!");
	}
	else
	{
		msgBox->setText("Tutorial does not exist!");
	}
	msgBox->exec();
}

void GUI::initWatchListWindow()
{
	this->watchListWindow = new QWidget{};
	this->currentTutorialLabel = new QLabel{};
	QVBoxLayout* vLay = new QVBoxLayout{};
	QPushButton* btn0 = new QPushButton{ "Exit" };
	QPushButton* btn1 = new QPushButton{ "Add to watch list" };
	QPushButton* btn2 = new QPushButton{ "Next tutorial" };
	QPushButton* btn3 = new QPushButton{ "Delete tutorial from watch list" };
	QPushButton* btn4 = new QPushButton{ "See watch list" };
	btn0->setFixedHeight(BUTTON_HEIGHT);
	btn1->setFixedHeight(BUTTON_HEIGHT);
	btn2->setFixedHeight(BUTTON_HEIGHT);
	btn3->setFixedHeight(BUTTON_HEIGHT);
	btn4->setFixedHeight(BUTTON_HEIGHT);
	QObject::connect(btn0, &QPushButton::clicked, this, &GUI::watchListExitButtonClicked);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::addToWatchListButtonClicked);
	QObject::connect(btn2, &QPushButton::clicked, this, &GUI::nextTutorialButtonClicked);
	QObject::connect(btn3, &QPushButton::clicked, this, &GUI::deleteTutorialWatchListButtonClicked);
	QObject::connect(btn4, &QPushButton::clicked, this, &GUI::seeWatchListButtonClicked);
	vLay->addWidget(currentTutorialLabel);
	vLay->addWidget(btn1);
	vLay->addWidget(btn2);
	vLay->addWidget(btn3);
	vLay->addWidget(btn4);
	vLay->addWidget(btn0);
	this->watchListWindow->setFixedWidth(WINDOW_WIDTH * 1.6);
	this->watchListWindow->setFixedHeight(WINDOW_HEIGHT);
	this->watchListWindow->setLayout(vLay);
	this->watchListWindow->setWindowTitle("C++ tutorials");
}

void GUI::watchListExitButtonClicked()
{
	this->userWindow->show();
	this->watchListWindow->hide();
}

void GUI::initSeeTutorialsWindow()
{
	this->seeTutorialsWindow = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{};

	QPushButton* btn1 = new QPushButton{ "See tutorials" };
	btn1->setFixedHeight(BUTTON_HEIGHT);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::realSeeTutorialsButtonClicked);

	this->enterPresenterTextBox = new QLineEdit{};
	QLabel* presenterLabel = new QLabel{ "Enter presenter (empty for all):" };
	presenterLabel->setBuddy(updatePresenterTextBox);

	formLayout->addRow(presenterLabel, enterPresenterTextBox);
	formLayout->addWidget(btn1);

	this->seeTutorialsWindow->setWindowTitle("C++ tutorials");
	this->seeTutorialsWindow->setFixedWidth(WINDOW_WIDTH / 2);
	this->seeTutorialsWindow->setFixedHeight(WINDOW_HEIGHT / 1.5);
	this->seeTutorialsWindow->setLayout(formLayout);
}

void GUI::realSeeTutorialsButtonClicked()
{
	std::string presenter = this->enterPresenterTextBox->text().toStdString();
	bool result = this->service.seeTutorials(presenter);
	if (result)
	{
		Tutorial t{ this->service.getCurrentTutorial() };
		if (!(t == Tutorial{}))
		{
			this->currentTutorialLabel->setText(this->service.getCurrentTutorial().toString().c_str());
		}
		this->watchListWindow->show();
		this->seeTutorialsWindow->hide();
	}
	else
	{
		QMessageBox* msgBox = new QMessageBox{};
		msgBox->setWindowTitle("Result");
		msgBox->setText("There are no tutorials with that presenter!");
		msgBox->exec();
	}
}

void GUI::addToWatchListButtonClicked()
{
	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");
	bool result = this->service.addToWatchList();
	if (result)
	{
		msgBox->setText("Tutorial added to watch list!");
	}
	else
	{
		msgBox->setText("Tutorial already exists in the watch list!");
	}
	msgBox->exec();
}

void GUI::nextTutorialButtonClicked()
{
	this->service.nextTutorial();
	Tutorial t{ this->service.getCurrentTutorial() };
	if (!(t == Tutorial{}))
	{
		this->currentTutorialLabel->setText(this->service.getCurrentTutorial().toString().c_str());
	}
}

void GUI::deleteTutorialWatchListButtonClicked()
{
	this->deleteWatchListTutorialWindow->show();
}

void GUI::seeWatchListButtonClicked()
{
	this->initWatchListTutorialTable();
	this->watchListTutorialTable->show();
}

void GUI::initWatchListTutorialTable()
{
	std::vector<Tutorial> tutorials = this->service.getWatchListTutorials();
	this->watchListTutorialTable = new QTableWidget{ (int)tutorials.size(), 5};
	this->watchListTutorialTable->setWindowTitle("Watch List");
	this->watchListTutorialTable->setFixedWidth(WINDOW_WIDTH * 1.26);
	this->watchListTutorialTable->setFixedHeight(WINDOW_HEIGHT);
	this->watchListTutorialTable->setHorizontalHeaderLabels(QStringList{ "Title", "Presenter", "Link", "Duration", "Likes" });
	for (int i = 0; i < tutorials.size(); i++)
	{
		this->watchListTutorialTable->setItem(i, 0, new QTableWidgetItem(tutorials[i].getTitle().c_str()));
		this->watchListTutorialTable->setItem(i, 1, new QTableWidgetItem(tutorials[i].getPresenter().c_str()));
		this->watchListTutorialTable->setItem(i, 2, new QTableWidgetItem(tutorials[i].getLink().c_str()));
		this->watchListTutorialTable->setItem(i, 3, new QTableWidgetItem(tutorials[i].getDuration().toString().c_str()));
		this->watchListTutorialTable->setItem(i, 4, new QTableWidgetItem(std::to_string(tutorials[i].getLikes()).c_str()));
	}
}

void GUI::initDeleteWatchListTutorialWindow()
{
	this->deleteWatchListTutorialWindow = new QWidget{};
	this->deleteWatchListTutorialWindow->setWindowTitle("Delete tutorial");
	QFormLayout* formLayout = new QFormLayout{};

	this->deleteWatchListLinkTextBox = new QLineEdit{};
	QLabel* linkLabel = new QLabel{ "Link:" };
	linkLabel->setBuddy(deleteWatchListLinkTextBox);

	QPushButton* btn1 = new QPushButton{ "Delete" };
	btn1->setFixedHeight(BUTTON_HEIGHT);
	QObject::connect(btn1, &QPushButton::clicked, this, &GUI::realDeleteTutorialWatchListButtonClicked);

	formLayout->addRow(linkLabel, deleteWatchListLinkTextBox);
	formLayout->addWidget(btn1);

	this->deleteWatchListTutorialWindow->setFixedWidth(WINDOW_WIDTH / 2);
	this->deleteWatchListTutorialWindow->setFixedHeight(WINDOW_HEIGHT / 2);
	this->deleteWatchListTutorialWindow->setLayout(formLayout);
}

void GUI::realDeleteTutorialWatchListButtonClicked()
{
	std::string link = this->deleteWatchListLinkTextBox->text().toStdString();
	bool retVal = this->service.deleteTutorialWatchList(link);
	QMessageBox* msgBox = new QMessageBox{};
	msgBox->setWindowTitle("Result");

	if (!retVal)
	{
		msgBox->setText("Tutorial does not exist in the watch list!");
		msgBox->exec();
	}
	else
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::question(this->deleteWatchListTutorialWindow, "", "Like tutorial?",
			QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::Yes)
		{
			this->service.likeTutorial(link);
		}
		msgBox->setText("Tutorial deleted from the watch list!");
		msgBox->exec();
	}
}
