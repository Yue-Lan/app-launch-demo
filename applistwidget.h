#ifndef APPLISTWIDGET_H
#define APPLISTWIDGET_H

#include <QObject>
#include <QListWidget>

#include <glib.h>

class AppListWidget : public QListWidget
{
public:
    AppListWidget(QString filePath);

public Q_SLOTS:
    void launchApplication (const QModelIndex &index);

private:
    GList *appList = NULL;
    QString filePath;
};

#endif // APPLISTWIDGET_H
