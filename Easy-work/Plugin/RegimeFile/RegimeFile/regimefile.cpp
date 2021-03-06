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

#include "regimefile.h"
#include "ui_regimefile.h"
#include "ui_infoPrint.h"
#include "OpenFile_global.h"

#include <QKeyEvent>
#include <QMenuBar>
#include <QDialog>
#include <QWidget>
#include <QTimer>
#include <QIcon>
#include <QTime>
#include <QSize>

Q_EXPORT_PLUGIN(RigimeFileClass)

RigimeFileClass::RigimeFileClass() : uiDialog (new Ui::InfoPrint)
{
    dialog = new QDialog;
    uiDialog->setupUi(dialog);

    calculateTime = new QTime;

    destroyedBL = true;
    startBL = false;

    defaultWorkerText = "Вы можете загрузить внешний файл в меню \"Режим файла\"";
    workerText = defaultWorkerText;

    menuRegimeFile = new QMenu(tr("Режим файла"));
    startRegime = new QAction(tr("Режим файла"),this);

    connect(startRegime,SIGNAL(triggered()),this,SLOT(slGetWidget()));
}

RigimeFileClass::~RigimeFileClass(){
    delete ui;
}

void RigimeFileClass::destroyedWidget(){
    emit stopLesson();
    startBL = false;
    destroyedBL = true;
    connect(startRegime,SIGNAL(triggered()),this,SLOT(slGetWidget()));
}

void RigimeFileClass::slCloseEvent(){
    saveSetting();
}

const QIcon RigimeFileClass::getIcon(){
    const QIcon *ico = new QIcon(":/icon");
    return *ico;
}

void RigimeFileClass::slResizeEvent (QResizeEvent * event){

    saveSizeLabelInputAndShow.setHeight(event->size().height()-33);
    saveSizeLabelInputAndShow.setWidth(event->size().width()-14);

    if(!destroyedBL)
    {
        if(ui->labelInput->width() == 0){
            ui->labelStart->setMaximumSize(saveSizeLabelInputAndShow);
        }
        else {
            ui->labelInput->setMaximumWidth(saveSizeLabelInputAndShow.width()/2);
            ui->labelShow->setMaximumWidth(saveSizeLabelInputAndShow.width()/2);
            ui->labelStart->setMaximumSize(saveSizeLabelInputAndShow);
        }
    }

}

void RigimeFileClass::slKeyboardLanguageChange(){
    if(startBL)
        if(!ui->labelInput->text().isEmpty())
            emit siGetWord(ui->labelInput->text().at(0));
}

void RigimeFileClass::slKeyPressEvent (QKeyEvent *event){

    if(!destroyedBL){
        if(startBL){

            if(event->key() == Qt::Key_CapsLock)
                emit siGetWord(ui->labelInput->text().at(0));

            if(event->key() != Qt::Key_Return){ // 16777220 - Enter
                if(!event->text().isEmpty())
                    centralAdministration(event->text().at(0));
            }
            else{
                stopPrint();
            }
        }
        else{
            if(event->key() == Qt::Key_Space){
                startPrint();
            }
        }
    }
}

void RigimeFileClass::slKeyReleaseEvent(QKeyEvent *event){

    if(!destroyedBL)
        if(event->key() == Qt::Key_Shift)
            if(!ui->labelInput->text().isEmpty())
                emit siGetWord(ui->labelInput->text().at(0));
}

void RigimeFileClass::startPrint(){

    startBL = true;

    if(!dateText.isEmpty()){

        while(dateText.at(0) == ' ')
            dateText = dateText.right(dateText.size()-1);

        if(!dateText.isEmpty())
        openFile->setBoxPosition(dateText.at(0));

        if(dateText.size()>=30){
            workerText = dateText.left(30);
            ui->labelInput->setText(workerText);
        }
        else{
            if(!dateText.isEmpty()){
                workerText = dateText;
                ui->labelInput->setText(workerText);
            }
            else
                workerText = defaultWorkerText;
        }
    }
    else
        workerText = defaultWorkerText;

    ui->labelInput->setText(workerText);

    ui->labelStart->close();

    if(!ui->labelInput->text().isEmpty())
        emit siGetWord(ui->labelInput->text().at(0));

    calculateCorrectly = 0;
    calculateError = 0;

    ////////////////////////////////////////////
    ui->labelInput->setMaximumWidth(saveSizeLabelInputAndShow.width()/2);
    ui->labelInput->setMinimumWidth(10);
    ui->labelShow->setMaximumWidth(saveSizeLabelInputAndShow.width()/2);
    ui->labelShow->setMinimumWidth(10);
    ////////////////////////////////////////////

    calculateTime->start();
}

void RigimeFileClass::stopPrint(){

    if(startBL) {
        emit stopLesson();
        startBL = false;
        ui->labelInput->clear();
        ui->labelShow->clear();

        ////////////////////////////////////////////
        ui->labelInput->setMaximumWidth(0);
        ui->labelInput->setMinimumWidth(0);
        ui->labelShow->setMaximumWidth(0);
        ui->labelShow->setMinimumWidth(0);
        ////////////////////////////////////////////

        ui->labelStart->show();

        uiDialog->inputCorrectly->setText(QString::number(calculateCorrectly,10));
        uiDialog->inputError->setText(QString::number(calculateError,10));
        uiDialog->inputTime->setText(createFormatTime(calculateTime->elapsed()));
        uiDialog->inputSign->setText(QString::number((calculateCorrectly/(calculateTime->elapsed()/1000.0))*60.0));


        if((calculateTime->elapsed())>2000){

            QStringList value;

            value << QDate::currentDate().toString("dd.MM.yyyy")
                  + QTime::currentTime().toString(" hh:mm:ss");
            value << uiDialog->inputError->text();
            value << uiDialog->inputCorrectly->text();
            value << uiDialog->inputTime->text();
            value << uiDialog->inputSign->text();

            emit siGetDateValue(value);
        }

        dialog->exec();
    }
}

QString RigimeFileClass::createFormatTime(int timeMS){

    int allTimeSeconds = timeMS/1000;

    int second  = 0;
    int min     = 0;
    int hours   = 0;

    if(allTimeSeconds/60){

        second = allTimeSeconds%60;
        allTimeSeconds -= second;
        min = allTimeSeconds/60;


        if(min/60){
            min = min%60;
            allTimeSeconds -= min*60;
            hours = (allTimeSeconds/60)/60;

        }
    }
    else
        second = allTimeSeconds;

    QTime resulatTime(hours,min,second);

    if(!resulatTime.toString().isEmpty())
        return resulatTime.toString();
    else
        return tr("Время велико");
}

void RigimeFileClass::centralAdministration(QChar inputWord){

    if(!ui->labelInput->text().isEmpty()){
        if(ui->labelInput->text().at(0) == inputWord)
        {
            ui->labelShow->setText(ui->labelShow->text() + QString(inputWord));

            if(ui->labelShow->text().size()>40)
                ui->labelShow->setText(ui->labelShow->text().right(22));

            ui->labelInput->setText(ui->labelInput->text().right(ui->labelInput->text().size() - 1));
            dateText = dateText.right(dateText.size() -1);


            if(ui->labelInput->text().size()<20){
                if(!dateText.isEmpty()){
                    if(dateText.size()>=30){
                        workerText = dateText.left(30);
                        ui->labelInput->setText(workerText);
                    }
                    else{
                        workerText = dateText;
                        ui->labelInput->setText(workerText);
                    }
                }
            }

            if(ui->labelInput->text().isEmpty()){

                if(dateText.isEmpty()){

                    dateText = openFile->getAllText();

                    if(!dateText.isEmpty()){
                        if(dateText.size()>=30){
                            workerText = dateText.left(30);
                        }
                        else{
                            workerText = dateText;
                        }
                    }
                    else{
                        workerText = defaultWorkerText;
                    }
                }

                stopPrint();
            }
            else{
                emit siGetWord(ui->labelInput->text().at(0));
                openFile->setBoxPosition(ui->labelInput->text().at(0));
                workerText = ui->labelInput->text();
            }


            calculateCorrectly++;
        }
        else
        {
            labelSetStyleSheetError();
            calculateError++;
            emit siGetWord(ui->labelInput->text().at(0));
        }
    }
    else
    {
        stopPrint();
    }
}

void RigimeFileClass::labelSetStyleSheetDefault(){
    ui->labelInput->setStyleSheet("border-color: black; border-width: 2px 2px 2px 0px;");
    ui->labelShow->setStyleSheet("border-color: black; border-width: 2px 0px 2px 2px;");
}

void RigimeFileClass::labelSetStyleSheetError(){

    ui->labelInput->setStyleSheet("border-color: red; border-width: 3px 3px 3px 0px;");
    ui->labelShow->setStyleSheet("border-color: red; border-width: 3px 0px 3px 3px;");

    QTimer::singleShot(200, this, SLOT(labelSetStyleSheetDefault()));
}

QWidget * RigimeFileClass::getWidget() {

    menuBar = new QMenuBar();
    widget = new QWidget();
    destroyedBL = false;
    ui = new Ui::Regime;

    ui->setupUi(widget);

    for(int i = 0; i<listMenu.size(); i++){
        if(i == 2)
            menuBar->addMenu(menuRegimeFile);
        menuBar->addMenu(listMenu.at(i));
    }

    ui->gridLayout->setMenuBar(menuBar);

    QList<QAction*> listAction;
    listAction = listMenu.at(1)->actions();
    for(int i = 0; i<listAction.size(); i++){
        if(i == 0)
            listAction.at(i)->setVisible(true);
        else
            listAction.at(i)->setVisible(false);
    }

    ////////////////////////////////////////////
    ui->labelStart->setMaximumSize(saveSizeLabelInputAndShow);
    ui->labelStart->setMinimumSize(0,0);

    ui->labelInput->setMaximumWidth(0);
    ui->labelInput->setMinimumWidth(0);
    ui->labelShow->setMaximumWidth(0);
    ui->labelShow->setMinimumWidth(0);
    ////////////////////////////////////////////

    connect(widget,SIGNAL(destroyed()),this,SLOT(destroyedWidget()));
    disconnect(startRegime,SIGNAL(triggered()),this,SLOT(slGetWidget()));
    emit siDBOpen();

    return widget;
}

void RigimeFileClass::setMenuBar(QList <QMenu *> bar)
{
    listMenu = bar;

    if(!listMenu.isEmpty())
    {
        listMenu.at(1)->addAction(startRegime);
    }
}

void RigimeFileClass::slGetWidget(){
    emit siGetWidget(getWidget());
}

void RigimeFileClass::setWorkerText(QString workerTextTemp) {

    dateText = workerTextTemp;
}
