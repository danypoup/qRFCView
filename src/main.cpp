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
#include "version.h"

#include <QFile>
#include <QIcon>
#include <QApplication>
#include <QFileInfo>

int main(int argc, char* argv[])
{
    Q_INIT_RESOURCE(rfcview);

    QApplication app(argc, argv);
    app.setApplicationName(QString(appName));
    app.setApplicationVersion(QString("%1 [%2]").arg(appVersion, appBuildTimestamp));
    app.setOrganizationName(QString(orgName));

    MainWindow mainWin;
    mainWin.show();

    if (argc > 1) {
        if (QFile::exists(argv[1])) {
            mainWin.RFCReady(argv[1]);
            QFileInfo qFileInfo(argv[1]);
            mainWin.SetCurrentDir(qFileInfo.dir());
        }
    }

    return app.exec();
}
