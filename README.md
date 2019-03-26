# app-launch-demo
An easy demo for open a mime-type file with application-lauch-configration, mainly depends on gio (g_app_info_\*).
Just like we open a file in the filemanager, this program intents to use very few codes to simply reproduce the whole workflow.
Use FileDialog to choose a file, and use ListView to choose the application for openning, and then use a Dialog to determine if you need to set this app as the default app to open the type file.

BTW, in Qt, we can use QDesktopService::openUrl() to open a file with it's default application. But it seems that at this time there is no API to set the defaut application in Qt.

# build depends
- qt5-default
- gilb-2.0
- gio-2.0

# how to build and use
- qmake
1. git clone and cd into the code directory
2. mkdir build && cd build
3. qmake ..
4. ./app-launch-demo
- qt-creator
1. make sure your qt-creator work
2. import the .pro file
3. run
