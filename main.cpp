#include "widget.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *w = new Widget;
    QObject::connect(w, &Widget::fileSelected, w, &Widget::onFileSelected);
    w->show();
    return a.exec();
}
