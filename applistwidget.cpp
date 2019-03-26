#include "applistwidget.h"
#include "dialog.h"
#include <glib.h>
#include <gio/gio.h>

#include <QDebug>

void list_recommend(char *content_type);
void launch_file(char *file_path);
char *get_file_content(GFile *file);

AppListWidget::AppListWidget(QString filePath)
{
    this->filePath = filePath;
    std::string tmp = filePath.toStdString();
    const char* file_path = tmp.c_str();
    GFile *file = g_file_new_for_path(file_path);
    char *content_type = get_file_content(file);
    GList *all = g_app_info_get_all_for_type (content_type);
    appList = all;
    GList *l = all;
    while (l != NULL) {
        GAppInfo *info = static_cast<GAppInfo*>(l->data);
        qDebug()<<g_app_info_get_name(info);
        this->addItem(QString(g_app_info_get_name(info)));
        l = l->next;
    }
    connect(this, &AppListWidget::doubleClicked, this, &AppListWidget::launchApplication);
}

void AppListWidget::launchApplication(const QModelIndex &index) {
    qDebug()<<index.data();
    int number = index.row();
    qDebug()<<number;
    GAppInfo *info = static_cast<GAppInfo*>(g_list_nth_data(appList, number));
    Dialog *dialog = new Dialog;
    dialog->setFilePath(filePath);
    dialog->setLaunchAppInfo(info);
    dialog->show();
}

char *get_file_content (GFile *file) {
    GFileInfo *info = g_file_query_info(file, G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE, G_FILE_QUERY_INFO_NONE, NULL, NULL);
    char *content_type = g_strdup(g_file_info_get_content_type(info));
    qDebug()<<"mime-type: "<<content_type;
    return content_type;
}
