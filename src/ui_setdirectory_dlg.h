/********************************************************************************
** Form generated from reading UI file 'setdirectory_dlg.ui'
**
** Created: Wed 2. Dec 03:03:13 2009
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETDIRECTORY_DLG_H
#define UI_SETDIRECTORY_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_directoryDialog
{
public:
    QWidget *widget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *vboxLayout;
    QPushButton *addButton;
    QPushButton *remButton;
    QPushButton *defaultButton;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout;
    QLabel *label_3_2_2_2_2_2_2;
    QLineEdit *urlLineEdit;
    QVBoxLayout *vboxLayout1;
    QPushButton *applyButton;
    QPushButton *cancelButton;
    QListWidget *directoryList;

    void setupUi(QDialog *directoryDialog)
    {
        if (directoryDialog->objectName().isEmpty())
            directoryDialog->setObjectName(QString::fromUtf8("directoryDialog"));
        directoryDialog->resize(517, 242);
        widget = new QWidget(directoryDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(9, 9, 453, 161));
        layoutWidget = new QWidget(directoryDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(510, 20, 87, 159));
        gridLayout = new QGridLayout(directoryDialog);
#ifndef Q_OS_MAC
        gridLayout->setSpacing(6);
#endif
        gridLayout->setContentsMargins(8, 8, 8, 8);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vboxLayout = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout->setSpacing(6);
#endif
#ifndef Q_OS_MAC
        vboxLayout->setContentsMargins(0, 0, 0, 0);
#endif
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        addButton = new QPushButton(directoryDialog);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        vboxLayout->addWidget(addButton);

        remButton = new QPushButton(directoryDialog);
        remButton->setObjectName(QString::fromUtf8("remButton"));

        vboxLayout->addWidget(remButton);

        defaultButton = new QPushButton(directoryDialog);
        defaultButton->setObjectName(QString::fromUtf8("defaultButton"));

        vboxLayout->addWidget(defaultButton);

        spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vboxLayout->addItem(spacerItem);


        gridLayout->addLayout(vboxLayout, 0, 1, 1, 1);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label_3_2_2_2_2_2_2 = new QLabel(directoryDialog);
        label_3_2_2_2_2_2_2->setObjectName(QString::fromUtf8("label_3_2_2_2_2_2_2"));

        hboxLayout->addWidget(label_3_2_2_2_2_2_2);

        urlLineEdit = new QLineEdit(directoryDialog);
        urlLineEdit->setObjectName(QString::fromUtf8("urlLineEdit"));

        hboxLayout->addWidget(urlLineEdit);


        gridLayout->addLayout(hboxLayout, 1, 0, 1, 1);

        vboxLayout1 = new QVBoxLayout();
#ifndef Q_OS_MAC
        vboxLayout1->setSpacing(6);
#endif
        vboxLayout1->setContentsMargins(0, 0, 0, 0);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        applyButton = new QPushButton(directoryDialog);
        applyButton->setObjectName(QString::fromUtf8("applyButton"));

        vboxLayout1->addWidget(applyButton);

        cancelButton = new QPushButton(directoryDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        vboxLayout1->addWidget(cancelButton);


        gridLayout->addLayout(vboxLayout1, 1, 1, 1, 1);

        directoryList = new QListWidget(directoryDialog);
        directoryList->setObjectName(QString::fromUtf8("directoryList"));

        gridLayout->addWidget(directoryList, 0, 0, 1, 1);


        retranslateUi(directoryDialog);

        QMetaObject::connectSlotsByName(directoryDialog);
    } // setupUi

    void retranslateUi(QDialog *directoryDialog)
    {
        directoryDialog->setWindowTitle(QApplication::translate("directoryDialog", "Set RFC directories", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("directoryDialog", "Add", 0, QApplication::UnicodeUTF8));
        remButton->setText(QApplication::translate("directoryDialog", "Remove", 0, QApplication::UnicodeUTF8));
        defaultButton->setText(QApplication::translate("directoryDialog", "Default", 0, QApplication::UnicodeUTF8));
        label_3_2_2_2_2_2_2->setText(QApplication::translate("directoryDialog", "RFC site URL", 0, QApplication::UnicodeUTF8));
        applyButton->setText(QApplication::translate("directoryDialog", "Apply", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("directoryDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class directoryDialog: public Ui_directoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETDIRECTORY_DLG_H
