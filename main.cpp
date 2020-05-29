#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "PicRetriever.h"
int main(int argc, char *argv[])
{
    /*PicRetriever retriever("DataSet/");
    retriever.loadPicPool("AllImages.txt");
    retriever.loadQueries("QueryImages.txt");
    retriever.retrieveAll(PicRetriever::DistanceMethod::LTWO, 16);
    retriever.dumpAllQueries("","");*/
    QApplication a(argc, argv);
    QtWidgetsApplication1 w;
    w.show();
    return a.exec();
}
