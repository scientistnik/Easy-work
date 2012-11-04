/**
 * Easy work - writed by KeyGen 2012
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

//-- Интерфейсы плагинов --//
#include "CoreWidget_global.h"
#include "RegimeFile_global.h"
#include "Keyboard_global.h"
#include "Style_global.h"
#include "what_is_global.h"
//-------------------------//

#include <QPluginLoader>
#include <QMenu>
#include <QDir>

void Core::loadPlugins(const QString dir) {

    const QDir pluginsDir(dir);

    QStringList filter;
    filter << "*.so";   // Для Linux
    filter << "*.dll";  // Для Windows

    foreach (QString fileName, pluginsDir.entryList(filter, QDir::Files))
    {
        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));

        if (loader.isLoaded())
        {
            qDebug() << QString("%1: %2 %3.").arg("Plugin file").arg(fileName).arg(QObject::tr("is already loaded"));
            continue;
        }

        if (loader.load() == false)
        {
            qDebug() << QString("%1 %2\n%3: %4").arg(QObject::tr("Can't load a plugin"))
                .arg(fileName).arg(QObject::tr("error"))
                .arg(loader.errorString());
        }
        else
        {
            QObject * obj = loader.instance();

            if (CoreWidget * plugin = qobject_cast<CoreWidget *>(obj))
            {
                coreWidget = plugin;
                installationsCoreWidget(plugin);
            }
            else if(Keyboard * plugin = qobject_cast<Keyboard *>(obj))
            {
                keyboard = plugin;
                installationsKeyboard(plugin);
            }
            else if(RigimeFile * plugin = qobject_cast<RigimeFile *>(obj))
            {
                installationsRigimeFile(plugin);
            }
            else if(Style * plugin = qobject_cast<Style *>(obj))
            {
                style = plugin;
                installationsStyle(plugin);
            }
            else if (WhatIs * plugin = qobject_cast<WhatIs *>(obj))
            {
                installationsWhatIs(plugin);
            }

        }
    }

    keyboard->show();
    coreWidget->getActionRegime()->trigger();
    connect(style,SIGNAL(getStyle(QString)),saveCentralWidget,SLOT(setStyleSheet(QString)));
}

// Знагрузка найденных плагинов:
void Core::installationsCoreWidget(CoreWidget * plugin){

   qDebug() << plugin->getName() << plugin->getVersion();
   plugin->setMenuBar(coreMenu);

   connect(plugin,SIGNAL(siGetWidget(QWidget*)),this,SLOT(slSetCentralWidget(QWidget*)));
}

void Core::installationsRigimeFile(RigimeFile * plugin)
{
    qDebug() << plugin->getName() << plugin->getVersion();
    plugin->setMenuBar(coreMenu);

    coreWidget->setRegimeMenu(plugin->getActionRegime(), plugin->getIcon());

    connect(plugin,SIGNAL(siGetWidget(QWidget*)),this,SLOT(slSetCentralWidget(QWidget*)));
    connect(this,SIGNAL(siKeyPressEvent(QKeyEvent*)),plugin,SLOT(slKeyPressEvent(QKeyEvent*)));
    connect(this,SIGNAL(siKeyReleaseEvent(QKeyEvent*)),plugin,SLOT(slKeyReleaseEvent(QKeyEvent*)));
    connect(this,SIGNAL(siResizeEvent(QResizeEvent*)),plugin,SLOT(slResizeEvent(QResizeEvent*)));
    connect(plugin,SIGNAL(siGetWord(QChar)),keyboard,SLOT(slAnimatePressWord(QChar)));
    connect(keyboard,SIGNAL(siKeyboardLanguageChange()),plugin,SLOT(siKeyboardLanguageChange()));
    connect(plugin,SIGNAL(stopLesson()),keyboard,SLOT(pressDownOffAllKey()));
}

void Core::installationsKeyboard(Keyboard *plugin)
{
    qDebug() << plugin->getName() << plugin->getVersion();
    setting->addMenu(plugin->getMenu());

    connect(this,SIGNAL(siCloseEvent(QCloseEvent*)),plugin,SLOT(slCloseEvent(QCloseEvent*)));
    connect(this,SIGNAL(siKeyReleaseEvent(QKeyEvent*)),plugin,SLOT(slKeyReleaseEvent(QKeyEvent*)));
    connect(this,SIGNAL(siFocusInEvent(QFocusEvent*)),plugin,SLOT(slFocusInEvent(QFocusEvent*)));
    connect(this,SIGNAL(siKeyPressEvent(QKeyEvent*)),plugin,SLOT(slKeyPressEvent(QKeyEvent*)));
    connect(this,SIGNAL(siMoveEvent(QMoveEvent*)),plugin,SLOT(slMoveEvent(QMoveEvent*)));
    connect(this,SIGNAL(siResizeEvent(QResizeEvent*)),plugin,SLOT(slResizeEvent(QResizeEvent*)));
}

void Core::installationsWhatIs(WhatIs * plugin){
    qDebug() << plugin->getName() << plugin->getVersion();
    help->addAction(plugin->getAction());
}

void Core::installationsStyle(Style *plugin){
    qDebug() << plugin->getName() << plugin->getVersion();
    this->setStyleSheet(plugin->getStyleSheet());
    setting->addMenu(plugin->createZipStyle());
    keyboard->setStyleSheet(plugin->getStyleSheet());
    connect(plugin,SIGNAL(getStyle(QString)),this,SLOT(setStyleSheet(QString)));
}
