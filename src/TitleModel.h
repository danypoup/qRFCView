/*
 * qRFCView, A smart IETF RFC viewer based on the Qt4 library.
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

#ifndef TITLEMODEL_H
#define TITLEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include <stdint.h>

#define MAX_TITLE_LEVEL 16

class CTitleItem;

class CTitleModel : public QAbstractItemModel {
    Q_OBJECT

public:
    CTitleModel(const QString& data, QObject* parent = 0);
    ~CTitleModel();

    QVariant data(const QModelIndex& index, int role) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& index) const;
    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex& parent = QModelIndex()) const;
    bool ParseTitle(const QString& qLevel, const QString& qTitle);

private:
    uint8_t m_iCurrentValidTitleNum[MAX_TITLE_LEVEL];
    uint8_t m_iCurrentValidTitleLevel;
    CTitleItem* m_pCurrentTitleItem[MAX_TITLE_LEVEL];

    CTitleItem* rootItem;
};

#endif
