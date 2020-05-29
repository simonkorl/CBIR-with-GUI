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
private:
    Ui::QtWidgetsApplication1Class ui;
    QString dataSetDir;
    QString picInfoDir;
    QString queryDir;
    QString resultDir;
    QString overallDir;
    PicRetriever* retriever = NULL;
    QStandardItemModel* model;
};
