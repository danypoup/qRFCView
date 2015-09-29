/*
 * qRFCView, A smart IETF RFC viewer based on the Qt library.
 * Copyright (C) 2005 Mitsubishi Electric ITE-TCL,
 *                    R. Rollet (rollet@tcl.ite.mee.com)
 * Copyright (C) 2015 Ľubomír Carik <Lubomir.Carik@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "rfcloader.h"
#include <RfcDocument.h>
#include "cdialogsetdirectory.h"
#include "cdialogfind.h"
#include "RfcView.h"

#include <QMessageBox>

#include <QtGui>
#include <QFontDialog>
#include <QPrinter>
#include <QLibrary>
#include <QStatusBar>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QProgressBar>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_qLastOpenDir(".")
{
    ui->setupUi(this);

    /*
    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget *)),
            workspace, SLOT(setActiveWindow(QWidget *)));
            */

    //TODO: connect(ui->action_AboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);

    readSettings();
    QUrl qURL(m_qRFCURL);
    m_pRFCLoader = new QRFCLoader(this);
    connect(m_pRFCLoader, SIGNAL(done(QString)), this, SLOT(RFCReady(QString)));
    connect(m_pRFCLoader, SIGNAL(start(QString)), this, SLOT(RFCStart(QString)));
    m_pRFCLoader->SetDownloadURL(qURL);
    m_pRFCLoader->SetDirectories(m_qDirectoryList, m_iDefaultDirectory);

    createStatusBar();
    //m_pDialogFind=NULL;
    m_pDialogFind = new CDialogFind(this);
    connect(m_pDialogFind, SIGNAL(findnext()), this, SLOT(findNext()));
    //m_pRFCLoader->GetFile(794);

    updateMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //workspace->closeAllWindows();
    /*
    if (activeMdiChild()) {
        event->ignore();
    } else {
        writeSettings();
        event->accept();
    }*/
    writeSettings();
    event->accept();
}

void MainWindow::changeEvent(QEvent* e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::openRfc()
{
    QString fileName = QFileDialog::getOpenFileName(this, QString(), m_qLastOpenDir.absolutePath());
    QFileInfo qFileInfo(fileName);

    if (!fileName.isEmpty()) {
        RfcDocument* existing = findMdiChild(fileName);
        if (existing) {
            ui->tabWidget->setCurrentWidget(existing);
            return;
        }

        RfcDocument* child = createMdiChild(qFileInfo.fileName());
        child->setCurrentFont(m_qFont);
        if (child->loadFile(fileName)) {
            statusBar()->showMessage(tr("File loaded"), 2000);
            child->show();
            m_qLastOpenDir = qFileInfo.dir();
        } else {
            child->close();
        }
    }
}

void MainWindow::getRfc()
{
    // Load a RFC number
    bool bOK;
    int iRFCNum = QInputDialog::getInt(this, tr("Please enter a RFC number"),
                                       tr("RFC#:"), 0, 1, 99999, 1, &bOK);
    if (bOK)
        RFCLoad(iRFCNum);
}

void MainWindow::closeRfc()
{
    RfcDocument* pMdiChild = activeMdiChild();

    if (pMdiChild) {
        ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
        delete pMdiChild;
    }
    updateMenus();
}

void MainWindow::print()
{
    RfcDocument* pMdiChild = activeMdiChild();
    if (pMdiChild) {
        QPrinter printer(QPrinter::HighResolution);

        printer.setFullPage(true);
        printer.setNumCopies(2);
        QPrintDialog dlg(&printer, this);
        //dlg.setPrintRange(QAbstractPrintDialog::PageRange);
        dlg.setMinMax(1, pMdiChild->GetNbPages());
        //dlg.setFromTo(1, 2);
        //dlg.setEnabledOptions(QAbstractPrintDialog::PrintPageRange);

        if (dlg.exec() == QDialog::Accepted) {
            pMdiChild->Print(&printer, dlg.printRange() == QAbstractPrintDialog::AllPages, dlg.fromPage(), dlg.toPage());
            //pMdiChild->Print(&printer, false, 4,6);
        }
    }
}

void MainWindow::forward()
{
    RfcDocument* pMdiChild = activeMdiChild();
    if (pMdiChild)
        pMdiChild->m_pTextEdit->forward();
}

void MainWindow::backward()
{
    RfcDocument* pMdiChild = activeMdiChild();
    if (pMdiChild)
        pMdiChild->m_pTextEdit->backward();
}

void MainWindow::copy()
{
    activeMdiChild()->copy();
}

void MainWindow::find()
{
    m_pDialogFind->show();
    m_pDialogFind->raise();
    m_pDialogFind->activateWindow();
}

void MainWindow::findPrevious()
{
    bool bResult;
    uint32_t iOptionFlags;

    QString qTextToFind = m_pDialogFind->GetTextToFind();
    iOptionFlags = m_pDialogFind->GetOptionFlags();
    RfcDocument* pMdiChild = activeMdiChild();
    if (pMdiChild && !qTextToFind.isEmpty()) {
        iOptionFlags |= FIND_OPTIONSFLAG_CURSOR | FIND_OPTIONSFLAG_BACKWARD;
        bResult = pMdiChild->FindText(qTextToFind, iOptionFlags);
        if (!bResult)
            statusBar()->showMessage(tr("No more occurence"), 3000);
        else
            statusBar()->clearMessage();
    }
}

void MainWindow::findNext()
{
    bool bResult;
    uint32_t iOptionFlags;

    QString qTextToFind = m_pDialogFind->GetTextToFind();
    iOptionFlags = m_pDialogFind->GetOptionFlags();
    RfcDocument* pMdiChild = activeMdiChild();
    if (pMdiChild && !qTextToFind.isEmpty()) {
        bResult = pMdiChild->FindText(qTextToFind, iOptionFlags);
        if (!bResult)
            statusBar()->showMessage(tr("No more occurence"), 3000);
        else
            statusBar()->clearMessage();
        iOptionFlags |= FIND_OPTIONSFLAG_CURSOR;
        m_pDialogFind->SetOptionFlags(iOptionFlags);
    }
    updateMenus();
}

void MainWindow::setFont()
{
    bool bOK;
    RfcDocument* pMDIChild;
    QFont qFont = QFontDialog::getFont(&bOK, m_qFont, this);
    m_qFont = qFont;
    if (bOK) {
        for (int i = 0; i < ui->tabWidget->count(); i++) {
            pMDIChild = qobject_cast<RfcDocument*>(ui->tabWidget->widget(i));
            pMDIChild->setCurrentFont(m_qFont);
        }
    }
}

void MainWindow::setDirectories()
{
    CDialogSetDirectory* pDialog = new CDialogSetDirectory(&m_qDirectoryList, m_iDefaultDirectory, m_qRFCURL, this);
    if (pDialog->exec() == QDialog::Accepted) {
        m_iDefaultDirectory = pDialog->GetDirectoryList(&m_qDirectoryList);
        m_qRFCURL = pDialog->GetRFCURL();
        QUrl qURL(m_qRFCURL);
        m_pRFCLoader->SetDownloadURL(qURL);
        m_pRFCLoader->SetDirectories(m_qDirectoryList, m_iDefaultDirectory);
    }
    delete pDialog;
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About qRFCView"),
                       tr("<b>qRFCView v0.63</b><br /> A smart RFC Viewer using the Qt library.<br><br> Mitsubishi Electric, 2005<br /><br /><a href=\"http://qrfcview.berlios.de/\">http://qrfcview.berlios.de/</a><br /><br /><small>Small Bugfix by Josef Freundorfer <a href=\"http://www.freundorfer.info\">http://www.freundorfer.info</a></small>"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}

void MainWindow::updateMenus()
{
    /*
    bool hasMdiChild = (activeMdiChild() != 0);

    closeAct->setEnabled(hasMdiChild);
    closeAllAct->setEnabled(hasMdiChild);
    tileAct->setEnabled(hasMdiChild);
    cascadeAct->setEnabled(hasMdiChild);
    nextAct->setEnabled(hasMdiChild);
    previousAct->setEnabled(hasMdiChild);
    separatorAct->setVisible(hasMdiChild);
*/
    bool hasSelection = (activeMdiChild() && activeMdiChild()->hasSelection());
    ui->action_Copy->setEnabled(hasSelection);
    ui->action_Find->setEnabled(activeMdiChild() != NULL);
    ui->action_Print->setEnabled(activeMdiChild() != NULL);
    ui->action_FindNext->setEnabled(activeMdiChild() != NULL && (!m_pDialogFind->GetTextToFind().isEmpty()));
    ui->action_FindPrevious->setEnabled(activeMdiChild() != NULL && (!m_pDialogFind->GetTextToFind().isEmpty()));
    ui->action_Forward->setEnabled(activeMdiChild() != NULL && activeMdiChild()->m_pTextEdit->isForwardAvailable());
    ui->action_Backward->setEnabled(activeMdiChild() != NULL && activeMdiChild()->m_pTextEdit->isBackwardAvailable());
    ui->action_Close->setEnabled(activeMdiChild() != NULL);
}

void MainWindow::readSettings()
{
    int i;
    QSettings settings;
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    m_qFont.setFamily(settings.value("Font_family", m_qFont.family()).toString());
    m_qFont.setPointSize(settings.value("Font_size", m_qFont.pointSize()).toInt());
    m_qFont.setWeight(settings.value("Font_weight", m_qFont.weight()).toInt());
    m_qFont.setItalic(settings.value("Font_italic", m_qFont.italic()).toBool());
    m_qDirectoryList = settings.value("Directories", QStringList(QString("."))).toStringList();
    m_iDefaultDirectory = settings.value("DefaultDirectory", 0).toInt();
    m_qRFCURL = settings.value("RFC_URL", QString("http://www.ietf.org/rfc/")).toString();

    move(pos);
    resize(size);
    for (i = 0; i < m_qDirectoryList.count(); i++)
        if (m_qDirectoryList[i].isEmpty())
            m_qDirectoryList.removeAt(i);
    if (m_qDirectoryList.count() == 0) {
        m_qDirectoryList = QStringList(QString("."));
        m_iDefaultDirectory = 0;
    }
    // Check DefaultDirectory index
    if (m_iDefaultDirectory >= m_qDirectoryList.size())
        m_iDefaultDirectory = 0;
    //qDebug() << m_qDirectoryList.count();
    m_qLastOpenDir = QDir(settings.value("LastOpenedDirectory", m_qDirectoryList[m_iDefaultDirectory]).toString());
    //m_qLastOpenDir=QDir(m_qDirectoryList[m_iDefaultDirectory]);
}

void MainWindow::writeSettings()
{
    QSettings settings;
    settings.setValue("pos", pos());
    settings.setValue("size", size());
    settings.setValue("Font_family", m_qFont.family());
    settings.setValue("Font_size", m_qFont.pointSize());
    settings.setValue("Font_weight", m_qFont.weight());
    settings.setValue("Font_italic", m_qFont.italic());
    settings.setValue("Directories", m_qDirectoryList);
    settings.setValue("DefaultDirectory", m_iDefaultDirectory);
    settings.setValue("RFC_URL", m_qRFCURL);
    settings.setValue("LastOpenedDirectory", m_qLastOpenDir.absolutePath());
}

void MainWindow::createStatusBar()
{
    m_pProgressBar = new QProgressBar();
    m_pProgressBar->setRange(0, 100);
    m_pProgressBar->setValue(50);
    //TODO Qt5: connect(m_pRFCLoader->GetQHttp(), SIGNAL(dataReadProgress(int, int)), this, SLOT(updateRFCProgress(int, int)));
    statusBar()->showMessage(tr("Ready"));
    //statusBar()->addWidget(m_pProgressBar, 0);
    //qProgressBar.show();
}

void MainWindow::RFCLoad(uint32_t iRFCNum)
{
    QString qFilename = QString("rfc%1.txt").arg(iRFCNum);
    QFileInfo qFileInfo;

    // Check if the required RFC is not yet opened
    for (int i = 0; i < ui->tabWidget->count(); i++) {
        RfcDocument* mdiChild = qobject_cast<RfcDocument*>(ui->tabWidget->widget(i));
        qFileInfo.setFile(mdiChild->currentFile());
        if (qFileInfo.fileName() == qFilename) {
            ui->tabWidget->setCurrentWidget(mdiChild);
            return;
        }
    }

    m_pRFCLoader->GetFile(iRFCNum);
}

void MainWindow::RFCStart(const QString& qFilename)
{ // Start downloading a RFC file
    //statusBar()->showMessage(tr("Downloading ")+qFilename);
    statusBar()->clearMessage();
    statusBar()->addWidget(m_pProgressBar);
    m_pProgressBar->show();
}

void MainWindow::RFCReady(const QString& qFilename)
{
    QFileInfo qFileInfo(qFilename);
    RfcDocument* child = createMdiChild(qFileInfo.fileName());
    child->setCurrentFont(m_qFont);
    if (child->loadFile(qFilename)) {
        child->show();
    } else {
        child->close();
    }
    statusBar()->showMessage(tr("Load ") + qFilename, 2000);
    statusBar()->removeWidget(m_pProgressBar);
}

void MainWindow::updateRFCProgress(int bytesRead, int totalBytes)
{
    m_pProgressBar->setMaximum(totalBytes);
    m_pProgressBar->setValue(bytesRead);
}

RfcDocument* MainWindow::createMdiChild(const QString& qTitle)
{
    RfcDocument* child = new RfcDocument();
    ui->tabWidget->addTab(child, qTitle);

    connect(child, SIGNAL(copyAvailable(bool)),
            ui->action_Copy, SLOT(setEnabled(bool)));
    connect(child->m_pTextEdit, SIGNAL(RFCReq(uint32_t)), this, SLOT(RFCLoad(uint32_t)));
    connect(child->m_pTextEdit, SIGNAL(forwardAvailable(bool)), ui->action_Forward, SLOT(setEnabled(bool)));
    connect(child->m_pTextEdit, SIGNAL(backwardAvailable(bool)), ui->action_Backward, SLOT(setEnabled(bool)));
    ui->tabWidget->setCurrentWidget(child);
    return child;
}

RfcDocument* MainWindow::activeMdiChild()
{

    return qobject_cast<RfcDocument*>(ui->tabWidget->currentWidget());
}

RfcDocument* MainWindow::findMdiChild(const QString& fileName)
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    for (int i = 0; i < ui->tabWidget->count(); i++) {
        RfcDocument* mdiChild = qobject_cast<RfcDocument*>(ui->tabWidget->widget(i));
        if (mdiChild->currentFile() == canonicalFilePath)
            return mdiChild;
    }
    return 0;
}

/*
void MainWindow::updateWindowMenu()
{
    / *
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(separatorAct);

    QList<QWidget *> windows = workspace->windowList();
    separatorAct->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i));

        QString text;
        if (i < 9) {
            text = tr("&%1. %2").arg(i + 1)
                                .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1. %2").arg(i + 1)
                                .arg(child->userFriendlyCurrentFile());
        }
        QAction *action  = windowMenu->addAction(text);
        action->setCheckable(true);
        action ->setChecked(child == activeMdiChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, child);
    }* /
}
*/

/*
void MainWindow::createActions()
{
    / *
    closeAllAct = new QAction(tr("Close &All"), this);
    closeAllAct->setStatusTip(tr("Close all the windows"));
    connect(closeAllAct, SIGNAL(triggered()),
            workspace, SLOT(closeAllWindows()));

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, SIGNAL(triggered()), workspace, SLOT(tile()));

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, SIGNAL(triggered()), workspace, SLOT(cascade()));

    nextAct = new QAction(tr("Ne&xt"), this);
    nextAct->setShortcut(tr("Ctrl+F6"));
    nextAct->setStatusTip(tr("Move the focus to the next window"));
    connect(nextAct, SIGNAL(triggered()),
            workspace, SLOT(activateNextWindow()));

    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setShortcut(tr("Ctrl+Shift+F6"));
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                  "window"));
    connect(previousAct, SIGNAL(triggered()),
            workspace, SLOT(activatePreviousWindow()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);
* /
}
*/

/*
void MainWindow::createMenus()
{
    //windowMenu = menuBar()->addMenu(tr("&Window"));
    //connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    //menuBar()->addSeparator();
}
*/
