#include "dialog.h"
#include "ui_dialog.h"

#include <gio/gio.h>
#include <glib.h>

void setDefaultLaunchApp (QString filePath, GAppInfo *info) {
    std::string tmp = filePath.toStdString();
    const char* file_path = tmp.c_str();
    GFile *file = g_file_new_for_path(file_path);
    tmp.clear();
    GFileInfo *file_info = g_file_query_info(file, G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE, G_FILE_QUERY_INFO_NONE, NULL, NULL);
    char *content_type = g_strdup(g_file_info_get_content_type(file_info));
    g_object_unref(file_info);
    g_app_info_set_as_default_for_type (info,
                                        content_type,
                                        NULL);
    g_free (content_type);
    g_object_unref(file);
}

void launchFileWithAppInfo (QString filePath, GAppInfo *info) {
    std::string tmp = filePath.toStdString();
    const char* file_path = tmp.c_str();
    GFile *file = g_file_new_for_path(file_path);
    GList *l = NULL;
    l = g_list_prepend(l, static_cast<gpointer>(file));
    g_app_info_launch (info,
                       l,
                       NULL,
                       NULL);
    g_list_free (l);
    g_object_unref(file);
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Dialog::yesButtonClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Dialog::noButtonClicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setFilePath(QString filePath) {
    mFilePath = filePath;
}

void Dialog::setLaunchAppInfo(GAppInfo *appInfo) {
    mAppInfo = appInfo;
}

void Dialog::yesButtonClicked() {
    launchFileWithAppInfo(mFilePath, mAppInfo);
    qApp->closeAllWindows();
}

void Dialog::noButtonClicked() {
    setDefaultLaunchApp(mFilePath, mAppInfo);
    launchFileWithAppInfo(mFilePath, mAppInfo);
    qApp->closeAllWindows();
}
