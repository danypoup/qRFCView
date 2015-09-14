/********************************************************************************
** Form generated from reading UI file 'find_dlg.ui'
**
** Created: Wed 2. Dec 03:03:13 2009
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIND_DLG_H
#define UI_FIND_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_findDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QLabel *label_2;
    QComboBox *textComboBox;
    QHBoxLayout *hboxLayout;
    QCheckBox *regexpCheckBox;
    QSpacerItem *spacerItem;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QCheckBox *wholeCheckBox;
    QCheckBox *caseCheckBox;
    QCheckBox *cursorCheckBox;
    QCheckBox *backwardCheckBox;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem1;
    QPushButton *findButton;
    QPushButton *closeButton;

    void setupUi(QDialog *findDialog)
    {
        if (findDialog->objectName().isEmpty())
            findDialog->setObjectName(QString::fromUtf8("findDialog"));
        findDialog->resize(400, 260);
        vboxLayout = new QVBoxLayout(findDialog);
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
        vboxLayout->setContentsMargins(8, 8, 8, 8);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(findDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
        vboxLayout1->setContentsMargins(8, 8, 8, 8);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        vboxLayout1->addWidget(label_2);

        textComboBox = new QComboBox(groupBox);
        textComboBox->setObjectName(QString::fromUtf8("textComboBox"));
        textComboBox->setEditable(true);

        vboxLayout1->addWidget(textComboBox);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        regexpCheckBox = new QCheckBox(groupBox);
        regexpCheckBox->setObjectName(QString::fromUtf8("regexpCheckBox"));

        hboxLayout->addWidget(regexpCheckBox);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout1->addLayout(hboxLayout);


        vboxLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(findDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
        gridLayout->setContentsMargins(8, 8, 8, 8);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        wholeCheckBox = new QCheckBox(groupBox_2);
        wholeCheckBox->setObjectName(QString::fromUtf8("wholeCheckBox"));

        gridLayout->addWidget(wholeCheckBox, 1, 0, 1, 1);

        caseCheckBox = new QCheckBox(groupBox_2);
        caseCheckBox->setObjectName(QString::fromUtf8("caseCheckBox"));

        gridLayout->addWidget(caseCheckBox, 0, 0, 1, 1);

        cursorCheckBox = new QCheckBox(groupBox_2);
        cursorCheckBox->setObjectName(QString::fromUtf8("cursorCheckBox"));

        gridLayout->addWidget(cursorCheckBox, 0, 1, 1, 1);

        backwardCheckBox = new QCheckBox(groupBox_2);
        backwardCheckBox->setObjectName(QString::fromUtf8("backwardCheckBox"));

        gridLayout->addWidget(backwardCheckBox, 1, 1, 1, 1);


        vboxLayout->addWidget(groupBox_2);

        hboxLayout1 = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout1->setSpacing(6);
#endif
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem1 = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem1);

        findButton = new QPushButton(findDialog);
        findButton->setObjectName(QString::fromUtf8("findButton"));

        hboxLayout1->addWidget(findButton);

        closeButton = new QPushButton(findDialog);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        hboxLayout1->addWidget(closeButton);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(findDialog);
        QObject::connect(closeButton, SIGNAL(clicked()), findDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(findDialog);
    } // setupUi

    void retranslateUi(QDialog *findDialog)
    {
        findDialog->setWindowTitle(QApplication::translate("findDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("findDialog", "Find", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("findDialog", "Text to find", 0, QApplication::UnicodeUTF8));
        regexpCheckBox->setText(QApplication::translate("findDialog", "Regular expression", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("findDialog", "Options", 0, QApplication::UnicodeUTF8));
        wholeCheckBox->setText(QApplication::translate("findDialog", "Whole words only", 0, QApplication::UnicodeUTF8));
        caseCheckBox->setText(QApplication::translate("findDialog", "Case sensitive", 0, QApplication::UnicodeUTF8));
        cursorCheckBox->setText(QApplication::translate("findDialog", "From cursor", 0, QApplication::UnicodeUTF8));
        backwardCheckBox->setText(QApplication::translate("findDialog", "Find backwards", 0, QApplication::UnicodeUTF8));
        findButton->setText(QApplication::translate("findDialog", "Find", 0, QApplication::UnicodeUTF8));
        closeButton->setText(QApplication::translate("findDialog", "Close", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class findDialog: public Ui_findDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIND_DLG_H
