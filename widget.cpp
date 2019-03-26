#include "widget.h"
#include "applistwidget.h"

#include <glib.h>
#include <gio/gio.h>

#include <QDebug>

Widget::Widget()
{

}

Widget::~Widget()
{

}

void Widget::onFileSelected(QString file) {
    qDebug()<<file;
    AppListWidget *appListWidget = new AppListWidget(file);
    appListWidget->show();
}
