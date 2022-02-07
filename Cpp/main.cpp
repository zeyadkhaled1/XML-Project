#include "mainwindow.h"
#include <QApplication>
#include "Consistency.h"
#include "Prettify.h"
#include "Compression.h"
#include "Xml_to_Json.h"
#include"minify.h"
#include"check_errors.h"
#include "Bit.h"
#include <fstream>
#include "gvc.h"
#include "cdt.h"
#include "cgraph.h"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
