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
	connect(ui.queryFileButton, SIGNAL(clicked()), this, SLOT(loadQueries()));
	connect(ui.queryButton, SIGNAL(clicked()), this, SLOT(insertQuery()));
	connect(ui.searchButton, SIGNAL(clicked()), this, SLOT(searchAll()));
	connect(ui.exportButton, SIGNAL(clicked()), this, SLOT(exportResult()));

	model = new QStandardItemModel();
	model->setColumnCount(2);
	model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("图片路径"));
	model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("检索准确率"));
	ui.tableView->setModel(model);
}

void QtWidgetsApplication1::getDataSetDir() {
	dataSetDir = QFileDialog::getExistingDirectory(
		this, "Choose DataSet folder",
		"DataSet");

	if (dataSetDir.isEmpty()){
		qDebug() << "Directory is empty" << endl;
		ui.dataSetBrowser->setTextBackgroundColor(QColor(230, 0, 0));
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

	if (dataSetDir.isEmpty() || picInfoDir.isEmpty()) {
		ui.loadButton->setEnabled(false);
	}
	else {
		ui.loadButton->setEnabled(true);
	}
}

QtWidgetsApplication1::~QtWidgetsApplication1(){
	if (retriever != NULL) {
		delete retriever;
	}
	if (model)
		delete model;
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
	}
	else {
		ui.infoBrowser->setText(picInfoDir);
		ui.infoBrowser->setTextBackgroundColor(QColor(255, 255, 255));
	}

	if (dataSetDir.isEmpty() || picInfoDir.isEmpty()) {
		ui.loadButton->setEnabled(false);
	}
	else {
		ui.loadButton->setEnabled(true);
	}
}


void QtWidgetsApplication1::getResultDir(){
	resultDir = QFileDialog::getExistingDirectory(
		this, "Choose folder to store retrieve result",
		"");

	if (resultDir.isEmpty()) {
		qDebug() << "Directory is empty" << endl;
		ui.resultBrowser->setTextBackgroundColor(QColor(230, 0, 0));
	}
	else {
		resultDir += "/";

		ui.resultBrowser->setText(resultDir);
		ui.resultBrowser->setTextBackgroundColor(QColor(255, 255, 255));
	}

	if (resultDir.isEmpty() || overallDir.isEmpty()) {
		ui.exportButton->setEnabled(false);
	}
	else {
		ui.exportButton->setEnabled(true);
	}
}

void QtWidgetsApplication1::getOverallDir(){
	overallDir = QFileDialog::getExistingDirectory(
		this, "Choose folder to store overall result",
		"");

	if (overallDir.isEmpty()) {
		qDebug() << "Directory is empty" << endl;
		ui.overallBrowser->setTextBackgroundColor(QColor(230, 0, 0));
	}
	else {
		overallDir += "/";

		ui.overallBrowser->setText(overallDir);
		ui.overallBrowser->setTextBackgroundColor(QColor(255, 255, 255));
	}

	if (resultDir.isEmpty() || overallDir.isEmpty()) {
		ui.exportButton->setEnabled(false);
	}
	else {
		ui.exportButton->setEnabled(true);
	}
}

void QtWidgetsApplication1::loadImageInfo(){
	if (picInfoDir.isEmpty() || dataSetDir.isEmpty()) {
		qDebug() << "Cannot load image infos because either directory is empty";
	}
	else {
		if (retriever->loadPicPool(picInfoDir.toStdString()) > 0) {
			QMessageBox::information(this, "Load finished", "Images loading finished!", QMessageBox::Ok);
			ui.queryButton->setEnabled(true);
			ui.queryFileButton->setEnabled(true);
			ui.searchButton->setEnabled(true);
		}
		else {
			QMessageBox::warning(this, "Load failed", "Images loading failed. Please check debug message.", QMessageBox::Ok);
			ui.queryButton->setEnabled(false);
			ui.queryFileButton->setEnabled(false);
			ui.searchButton->setEnabled(false);
		}
	}
}

void QtWidgetsApplication1::loadQueries(){
	queryDir = QFileDialog::getOpenFileName(
		this, "Choose queries description file",
		"QueryImages.txt",
		"");
	int ret = 0;
	if (queryDir.isEmpty()) {
		qDebug() << "Cannot load queries because the directory is empty";
		return;
	}
	else {
		model->removeRows(0, model->rowCount());
		if ((ret = retriever->loadQueries(queryDir.toStdString())) > 0) {
			for (int i = 0; i < retriever->queries.size(); ++i) {
				model->setItem(i, 0, new QStandardItem((retriever->queries[i]->picInfo->fileName).c_str()));
				model->setItem(i, 1, new QStandardItem("0"));
			}
		}
		else if(ret == -1){
			QMessageBox::warning(this, "Load query error", "You need to load image data first", QMessageBox::Ok);
		}
	}
}

void QtWidgetsApplication1::insertQuery(){
	QString n_fileName = ui.lineEdit->text();
	PicInfo* tmpInfo = NULL;
	if (retriever->m_pool.isLoaded()) {
		if ((tmpInfo = retriever->m_pool.findPic(n_fileName.toStdString()))) {
			Query* n_query = new Query();
			n_query->picInfo = tmpInfo;
			retriever->queries.push_back(n_query);

			model->setItem(retriever->queries.size() - 1, 0, new QStandardItem(n_fileName));
			model->setItem(retriever->queries.size() - 1, 1, new QStandardItem(0));
		}
		else {
			QMessageBox::warning(this, "Filename error", "The filename is invalid.", QMessageBox::Ok);
		}
	}
	else {
		QMessageBox::warning(this, "Image data error", "You need to load image data first.", QMessageBox::Ok);
	}
}

void QtWidgetsApplication1::searchAll(){
	PicRetriever::DistanceMethod method;
	int bins = 0;
	if (ui.bin16Button->isChecked()) {
		bins = 16;
	}
	else {
		bins = 128;
	}

	if (ui.L2radioButton->isChecked()) {
		method = PicRetriever::LTWO;
	}
	else if (ui.HIradioButton->isChecked()) {
		method = PicRetriever::HI;
	}
	else if (ui.BhradioButton->isChecked()) {
		method = PicRetriever::BH;
	}
	else if (ui.cosradioButton->isChecked()) {
		method = PicRetriever::COS;
	}
	else if (ui.JMradioButton->isChecked()) {
		method = PicRetriever::JM;
	}
	else {
		//invalid
		method = (PicRetriever::DistanceMethod) -1;
	}

	retriever->retrieveAll(method, bins);

	for (int i = 0; i < retriever->queries.size(); ++i) {
		model->setItem(i, 1, new QStandardItem(QString::fromStdString(std::to_string(retriever->queries[i]->precision))));
	}
}

void QtWidgetsApplication1::exportResult(){
	if (retriever->dumpAllQueries(resultDir.toStdString(), overallDir.toStdString()) < 0) {
		QMessageBox::warning(this, "Export error", "Fail to export to target directory", QMessageBox::Ok);
	}
	else {
		QMessageBox::information(this, "Export succeeds", "Exportation is finished.", QMessageBox::Ok);
	}
}
