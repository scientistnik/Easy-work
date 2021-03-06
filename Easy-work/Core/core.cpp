/**
 * Easy work - краткое описание на английском
 * Copyright (C) 2012 KeyGen <KeyGenQt@gmail.com>
 * https://github.com/KeyGen/Easy-work/wiki
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "core.h"
#include "CoreWidget_global.h"

#include <QDesktopServices>
#include <QDesktopWidget>
#include <QApplication>
#include <QKeyEvent>
#include <QMenuBar>
#include <QUrl>
#include <QDir>

#include <stdlib.h>

Core::Core(QWidget *parent)
    : QMainWindow(parent)
{
    QMainWindow::setWindowTitle("Easy work");
    QMainWindow::setWindowIcon(QIcon(":/gloabl_icon"));
    installationsCoreMenu();
    delUpdate();

    loadKeyboard    = false;
    loadStyle       = false;
    loadRegimeFile  = false;
    loadUpdate      = false;
    loadRegimeLesson= false;
    loadRegimeGame  = false;

    QMainWindow::resize(850,220);
    loadPlugins();

    moveWindowCenter();

    this->setVisible(false);
    this->setVisible(true);
}

void Core::delUpdate(QString pathTempUpdate){
    QDir dir(pathTempUpdate);
    if(dir.exists()){
        QStringList filter;

#ifdef Q_OS_WIN32
        filter << "*.exe";
        filter << "*.pak";
#endif

#ifdef Q_OS_LINUX
        filter << "*.deb";
#endif

        QStringList files = dir.entryList(filter);
        for(int i = 0; i<files.size(); i++){
            QString file = files.at(i);
            QDir remove;
            qDebug() << tr("Найдено обновление. Удалние:")
                     << remove.remove(pathTempUpdate.toAscii() + "/" + file.toAscii());
        }

#ifdef Q_OS_WIN32
        dir.cdUp();
        QStringList list = pathTempUpdate.split("/");
        dir.rmdir(list.last());
#endif
    }
}

Core::~Core() {

    if(!pathUpdate.isEmpty()){

        #ifdef Q_OS_WIN32
            qDebug() << system(pathUpdate.toAscii());
        #endif

        #ifdef Q_OS_LINUX
            QDir dir;
            QString absolute = dir.absolutePath();
            absolute.chop(3);
            pathUpdate = pathUpdate.right(pathUpdate.size()-3);

            qDebug() << system("xterm -e sudo dpkg -i " + absolute.toAscii()+ pathUpdate.toAscii() + "&&cd /usr/bin&&Easy_work");
        #endif

    }

    #ifdef Q_OS_WIN32
        delDir();
    #endif
}

#ifdef Q_OS_WIN32
void Core::delDir(QString pathTempUpdate){
    QDir dir(pathTempUpdate);
    dir.cdUp();
    QStringList list = pathTempUpdate.split("/");
    dir.rmdir(list.last());
}
#endif

void Core::slUpdateTrue(QString path){
    pathUpdate = path;
}

void Core::moveWindowCenter(){
    // Запустим программу по центру экрана
    QDesktopWidget *desktop = QApplication::desktop();  // Определяем разрешение экрана
    this->move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2-150); // Распологаем MainWindow в ценре
}

void Core::installationsCoreMenu()
{
    menu = new QMenu(tr("Меню"),this);
    regime  = new QMenu(tr("Режимы"),this);
    learner  = new QMenu(tr("Ученики"),this);
    setting = new QMenu(tr("Настройки"),this);
    help = new QMenu(tr("Справка"),this);

    coreMenu << menu;
    coreMenu << regime;
    //coreMenu << learner;
    coreMenu << setting;
    coreMenu << help;

    QAction *exit = new QAction(tr("Выход"),this);
    menu->addAction(exit);
    connect(exit,SIGNAL(triggered()),this,SLOT(close()));

    QAction *bags = new QAction(tr("Сообщить об ошибке"),this);
    help->addAction(bags);
    connect(bags,SIGNAL(triggered()),this,SLOT(slCommunicateBags()));

    QAction *goToWebSite = new QAction(tr("Посетить сайт"),this);
    help->addAction(goToWebSite);
    connect(goToWebSite,SIGNAL(triggered()),this,SLOT(slGoToWebSite()));

    this->setFocusPolicy(Qt::StrongFocus); // Focus Tab and Click
}

void Core::slGoToWebSite() { fGoToWebSite(); }
void Core::slCommunicateBags() { fCommunicateBags(); }

void Core::fGoToWebSite(QString site){
    QDesktopServices::openUrl(QUrl(site));
}

void Core::fCommunicateBags(QString site){
    QDesktopServices::openUrl(QUrl(site));
}

void Core::showEvent ( QShowEvent * event ){
    event->type();
    emit siShowCore();
}

void Core::hideEvent ( QHideEvent * event ){
    event->type();
    emit siHideCore();
}

// slots
void Core::slSetCentralWidget(QWidget *widget)
{
    //saveCentralWidget = widget;
    QMainWindow::setWindowTitle(widget->windowTitle());
    this->setCentralWidget(widget);
}

// signals
void Core::keyPressEvent  (QKeyEvent *event){
    emit siKeyPressEvent  (event);
}

void Core::keyReleaseEvent(QKeyEvent * event){
    emit siKeyReleaseEvent(event);
}

void Core::resizeEvent    (QResizeEvent * event){
    emit siResizeEvent(event);
}

void Core::moveEvent      (QMoveEvent * event){
    emit siMoveEvent(event);
}

void Core::closeEvent     (QCloseEvent * event){
    saveSetting();
    emit siCloseEvent(event);
}

void Core::focusInEvent   (QFocusEvent * event){
    emit siFocusInEvent(event);
}


