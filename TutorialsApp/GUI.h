#pragma once
#include "Service.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton.h>
#include <QtWidgets/QTableWidget.h>
#include <QWidget.h>
#include "AdminWindow.h"

class GUI : public QWidget, public QObject
{
private:
	Service& service;
	QWidget* startWindow;
	AdminWindow* adminWindow;
	QWidget* storageFormatWindow;
	bool csvFormat;
	QWidget* userWindow;

	QWidget* tutorialTableWindow;
	QTableWidget* tutorialTable;
	QLineEdit* filterTutorialsTextBox;

	QWidget* addTutorialWindow;
	QLineEdit* titleTextBox;
	QLineEdit* presenterTextBox;
	QLineEdit* linkTextBox;
	QLineEdit* minutesTextBox;
	QLineEdit* secondsTextBox;
	QLineEdit* likesTextBox;

	QWidget* updateTutorialWindow;
	QLineEdit* updateLinkTextBox;
	QLineEdit* updateTitleTextBox;
	QLineEdit* updatePresenterTextBox;
	QLineEdit* updateNewLinkTextBox;
	QLineEdit* updateMinutesTextBox;
	QLineEdit* updateSecondsTextBox;
	QLineEdit* updateLikesTextBox;

	QWidget* deleteTutorialWindow;
	QLineEdit* deleteLinkTextBox;

	QWidget* seeTutorialsWindow;
	QLineEdit* enterPresenterTextBox;

	QWidget* watchListWindow;
	QLabel* currentTutorialLabel;
	QTableWidget* watchListTutorialTable;
	bool isWatchListSavedCSV;
	bool isWatchListSavedHTML;

	QWidget* deleteWatchListTutorialWindow;
	QLineEdit* deleteWatchListLinkTextBox;

public:
	GUI(Service& service, QWidget* parent = Q_NULLPTR);
	void start();
	void saveTutorialsToFile();

	void initStartWindow();
	void adminButtonClicked();
	void userButtonClicked();

	void undoButtonClicked();
	void redoButtonClicked();

	void initAdminWindow();
	void adminExitButtonClicked();

	void initStorageFormatWindow();
	void htmlButtonClicked();
	void csvButtonClicked();

	void initUserWindow();
	void userExitButtonClicked();
	void userSeeTutorialsButtonClicked();
	void userSaveWatchListButtonClicked();
	void userOpenSavedWatchListButtonClicked();

	void initWatchListWindow();
	void watchListExitButtonClicked();
	void addToWatchListButtonClicked();
	void nextTutorialButtonClicked();
	void deleteTutorialWatchListButtonClicked();
	void seeWatchListButtonClicked();

	void initSeeTutorialsWindow();
	void realSeeTutorialsButtonClicked();

	void initTutorialTable();
	void filterTutorialsTextChanged();
	void showTutorialsButtonClicked();

	void initWatchListTutorialTable();

	void initAddTutorialWindow();
	void addTutorialButtonClicked();
	void realAddTutorialButtonClicked();

	void initUpdateTutorialWindow();
	void updateTutorialButtonClicked();
	void realUpdateTutorialButtonClicked();

	void initDeleteTutorialWindow();
	void deleteTutorialButtonClicked();
	void realDeleteTutorialButtonClicked();

	void initDeleteWatchListTutorialWindow();
	void realDeleteTutorialWatchListButtonClicked();
};

