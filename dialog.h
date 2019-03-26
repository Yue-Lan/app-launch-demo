#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <gio/gio.h>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void setFilePath (QString filePath);
    void setLaunchAppInfo (GAppInfo *appInfo);

private:
    Ui::Dialog *ui;
    QString mFilePath = NULL;
    GAppInfo *mAppInfo = NULL;

private Q_SLOTS:
    void yesButtonClicked();
    void noButtonClicked();
};

#endif // DIALOG_H
