#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <fstream>
#include <iostream>

#include "ui_QtWidgetsApplication1.h"
#include "PicRetriever.h"

class QtWidgetsApplication1 : public QMainWindow
{   
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);
    ~QtWidgetsApplication1();
public slots:
	void getDataSetDir();
    void getPicInfoDir();
    void getResultDir();
    void getOverallDir();
    void loadImageInfo();
    void loadQueries();
    void insertQuery();
    void searchAll();
    void exportResult();
    void onTableClicked(const QModelIndex& index);
private:
    Ui::QtWidgetsApplication1Class ui;
    QString dataSetDir;
    QString picInfoDir;
    QString queryDir;
    QString resultDir;
    QString overallDir;
    PicRetriever* retriever = NULL;
    QStandardItemModel* model;
    QImage queryImage;
    QImage resImage[3];
    std::ofstream fout;
    std::streambuf* stream_buffer_cout;
    std::streambuf* stream_buffer_cerr;
    std::streambuf* stream_buffer_file;
};
