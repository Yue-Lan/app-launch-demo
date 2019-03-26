#ifndef WIDGET_H
#define WIDGET_H

#include <QFileDialog>

class Widget : public QFileDialog
{
    Q_OBJECT

public:
    Widget ();
    ~Widget();

public Q_SLOTS:
    void onFileSelected (QString file);
};

#endif // WIDGET_H
