#include "QtWidgetsApplication1.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//std::streambuf* stream_buffer_cout = std::cout.rdbuf();
	connect(ui.ddataButton, SIGNAL(clicked()), this, SLOT(getDataSetDir()));
	connect(ui.fimageButton, SIGNAL(clicked()), this, SLOT(getPicInfoDir()));
	connect(ui.dresultButton, SIGNAL(clicked()), this, SLOT(getResultDir()));
	connect(ui.doverallButton, SIGNAL(clicked()), this, SLOT(getOverallDir()));

	connect(ui.loadButton, SIGNAL(clicked()), this, SLOT(loadImageInfo()));
}

void QtWidgetsApplication1::getDataSetDir() {
	dataSetDir = QFileDialog::getExistingDirectory(
		this, "Choose DataSet folder",
		"DataSet");

	if (dataSetDir.isEmpty()){
		qDebug() << "Directory is empty" << endl;
		ui.dataSetBrowser->setTextBackgroundColor(QColor(230, 0, 0));
		return;
	}
	else{
		if (retriever) {
			delete retriever;
		}
		dataSetDir += "/";
		retriever = new PicRetriever(dataSetDir.toStdString());

		ui.dataSetBrowser->setText(dataSetDir);
		ui.dataSetBrowser->setTextBackgroundColor(QColor(255,255,255));
	}
}

QtWidgetsApplication1::~QtWidgetsApplication1(){
	if (retriever != NULL) {
		delete retriever;
	}
}

void QtWidgetsApplication1::getPicInfoDir()
{
	picInfoDir = QFileDialog::getOpenFileName(
		this, "Choose image information file",
		"AllImages.txt",
		"");
	if (picInfoDir.isEmpty()){
		qDebug() << "Directory is empty" << endl;
		ui.infoBrowser->setTextBackgroundColor(QColor(230, 0, 0));
		return;
	}
	else {
		ui.infoBrowser->setText(picInfoDir);
		ui.infoBrowser->setTextBackgroundColor(QColor(255, 255, 255));
	}
}


void QtWidgetsApplication1::getResultDir(){
	resultDir = QFileDialog::getExistingDirectory(
		this, "Choose folder to store retrieve result",
		"");

	if (resultDir.isEmpty()) {
		qDebug() << "Directory is empty" << endl;
		ui.resultBrowser->setTextBackgroundColor(QColor(230, 0, 0));
		return;
	}
	else {
		resultDir += "/";

		ui.resultBrowser->setText(resultDir);
		ui.resultBrowser->setTextBackgroundColor(QColor(255, 255, 255));
	}
}

void QtWidgetsApplication1::getOverallDir(){
	overallDir = QFileDialog::getExistingDirectory(
		this, "Choose folder to store overall result",
		"");

	if (overallDir.isEmpty()) {
		qDebug() << "Directory is empty" << endl;
		ui.overallBrowser->setTextBackgroundColor(QColor(230, 0, 0));
		return;
	}
	else {
		overallDir += "/";

		ui.overallBrowser->setText(overallDir);
		ui.overallBrowser->setTextBackgroundColor(QColor(255, 255, 255));
	}
}

void QtWidgetsApplication1::loadImageInfo(){
	if (picInfoDir.isEmpty() || dataSetDir.isEmpty()) {
		qDebug() << "Cannot load image infos because either directory is empty" << endl;
	}
	else {
		retriever->loadPicPool(picInfoDir.toStdString());
	}
}

void QtWidgetsApplication1::loadQueries()
{
}
