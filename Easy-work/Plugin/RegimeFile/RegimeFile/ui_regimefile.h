/********************************************************************************
** Form generated from reading UI file 'regimefile.ui'
**
** Created: Tue Jan 22 14:31:17 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGIMEFILE_H
#define UI_REGIMEFILE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Regime
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelShow;
    QLabel *labelInput;
    QLabel *labelStart;

    void setupUi(QWidget *Regime)
    {
        if (Regime->objectName().isEmpty())
            Regime->setObjectName(QString::fromUtf8("Regime"));
        Regime->resize(765, 210);
        gridLayout = new QGridLayout(Regime);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelShow = new QLabel(Regime);
        labelShow->setObjectName(QString::fromUtf8("labelShow"));
        QFont font;
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        labelShow->setFont(font);
        labelShow->setStyleSheet(QString::fromUtf8(""));
        labelShow->setFrameShape(QFrame::NoFrame);
        labelShow->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        labelShow->setMargin(0);

        horizontalLayout->addWidget(labelShow);

        labelInput = new QLabel(Regime);
        labelInput->setObjectName(QString::fromUtf8("labelInput"));
        labelInput->setFont(font);
        labelInput->setStyleSheet(QString::fromUtf8(""));
        labelInput->setFrameShape(QFrame::NoFrame);

        horizontalLayout->addWidget(labelInput);

        labelStart = new QLabel(Regime);
        labelStart->setObjectName(QString::fromUtf8("labelStart"));
        labelStart->setFrameShape(QFrame::Box);
        labelStart->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(labelStart);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Regime);

        QMetaObject::connectSlotsByName(Regime);
    } // setupUi

    void retranslateUi(QWidget *Regime)
    {
        Regime->setWindowTitle(QApplication::translate("Regime", "\320\240\320\265\320\266\320\270\320\274 \321\204\320\260\320\271\320\273\320\260", 0, QApplication::UnicodeUTF8));
        labelShow->setText(QString());
        labelInput->setText(QString());
        labelStart->setText(QApplication::translate("Regime", "\320\237\321\200\320\276\320\261\320\265\320\273 - \321\201\321\202\320\260\321\200\321\202, Enter - \321\201\321\202\320\276\320\277", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Regime: public Ui_Regime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGIMEFILE_H
