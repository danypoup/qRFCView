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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QStringList>
#include <QDir>

#include <stdint.h>

namespace Ui {
class MainWindow;
}
//class QWorkspace;
class MdiChild;
class RfcDocument;
//class QSignalMapper;
class QRFCLoader;
class QProgressBar;
class CDialogFind;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    void SetCurrentDir(QDir qCurrentDir) { m_qLastOpenDir = qCurrentDir; }

public slots:
    void RFCReady(const QString& qFileName);

protected:
    void changeEvent(QEvent* e);
    void closeEvent(QCloseEvent* event);

private slots:
    void openRfc();
    void getRfc();
    void closeRfc();
    void print();

    void forward();
    void backward();
    void copy();
    void find();
    void findPrevious();
    void findNext();
    void setFont();
    void setDirectories();

    void about();
    void aboutQt();

    void updateMenus();

    void RFCLoad(uint32_t);
    //void RFCReady(const QString& qFileName);

    void RFCStart(const QString& qFilename);
    void updateRFCProgress(int bytesRead, int totalBytes);

    RfcDocument* createMdiChild(const QString& qTitle);

private:
    void readSettings();
    void writeSettings();
    void createStatusBar();

    RfcDocument* activeMdiChild();
    RfcDocument* findMdiChild(const QString& fileName);

    Ui::MainWindow* ui;

    QProgressBar* m_pProgressBar; // Progress bar located in the status bar
    QFont m_qFont; // Font used for text display
    QStringList m_qDirectoryList;
    uint8_t m_iDefaultDirectory;
    QString m_qRFCURL;
    QRFCLoader* m_pRFCLoader;
    CDialogFind* m_pDialogFind;
    QDir m_qLastOpenDir;
};

/* OLD impl.
class MainWindow : public QMainWindow {
    Q_OBJECT

public:

private slots:
    //void updateWindowMenu();

private:
    //QSignalMapper* windowMapper;

    / *
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;* /
};
*/
#endif // MAINWINDOW_H
