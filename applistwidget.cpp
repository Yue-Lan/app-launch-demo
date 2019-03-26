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


void list_recommend (char *content_type) {
    GList *all = g_app_info_get_all_for_type (content_type);
    GList *l = all;
    while (l != NULL) {
        GAppInfo *info = static_cast<GAppInfo*>(l->data);
        qDebug()<<g_app_info_get_name(info);
        l = l->next;
    }
    g_list_free (all);
}

char *get_file_content (GFile *file) {
    GFileInfo *info = g_file_query_info(file, G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE, G_FILE_QUERY_INFO_NONE, NULL, NULL);
    char *content_type = g_strdup(g_file_info_get_content_type(info));
    qDebug()<<"mime-type: "<<content_type;
    return content_type;
}

void launch_file (char *file_path) {
    GFile *file = g_file_new_for_path (file_path);
    if (!g_file_query_exists (file,NULL)) {
        qDebug()<<"file does not exist!";
        return;
    }

    char *content_type = get_file_content(file);//to be free

    GList *all = g_app_info_get_all_for_type (content_type);//to be free
    GList *l = all;
    int n = 1;
    while (l != NULL) {
        GAppInfo *info = static_cast<GAppInfo*>(l->data);
        qDebug()<<n<<". "<<g_app_info_get_name(info);
        l = l->next;
        n++;
    }

    n = 0;
    qDebug()<<"which application do you want? (1-"<<g_list_length (all)<<")";
    scanf("%d\n", &n);
    qDebug()<<n;
    while (n < 1 && n > (int)g_list_length (all)) {
        qDebug()<<"please choose a number in scope 1-"<<g_list_length (all)<<")";
        scanf("%d\n", &n);
    }

    l = g_list_nth(all, n-1);
    GAppInfo *selected_info = static_cast<GAppInfo*>(l->data);
    qDebug()<<g_app_info_get_name(selected_info);

    qDebug()<<"do you plan to set this application as default launch type for this mime-type? (y/n)";
    char yes_no = 'n';
    scanf("%s\n", &yes_no);

    if (yes_no == 'y') {
        qDebug()<<"trying set this application as default for this mime-type";
        GError *err1 = NULL;
        g_app_info_set_as_default_for_type (selected_info,
                                            content_type,
                                            &err1);
        if (err1) {
            fprintf(stderr, "%s\n", err1->message);
        }
    }

    GError *err = NULL;
    l = NULL;
    l = g_list_prepend(l, static_cast<gpointer>(file));

    g_app_info_launch (selected_info, l, NULL, &err);
    if (err) {
        fprintf(stderr,"%s\n",err->message);
    }

    g_list_free (all);
    g_free (content_type);
    g_list_free (l);
    g_object_unref(file);
}
