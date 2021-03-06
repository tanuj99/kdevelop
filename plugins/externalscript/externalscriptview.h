/*
    This plugin is part of KDevelop.

    Copyright (C) 2010 Milian Wolff <mail@milianw.de>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef KDEVPLATFORM_PLUGIN_EXTERNALSCRIPTVIEW_H
#define KDEVPLATFORM_PLUGIN_EXTERNALSCRIPTVIEW_H

#include <QWidget>

#include "ui_externalscriptview.h"

class ExternalScriptItem;
class QAction;

class QSortFilterProxyModel;

class ExternalScriptPlugin;

class ExternalScriptView
    : public QWidget
    , Ui::ExternalScriptViewBase
{
    Q_OBJECT

public:
    explicit ExternalScriptView(ExternalScriptPlugin* plugin, QWidget* parent = nullptr);
    ~ExternalScriptView() override;

    /// @return Currently selected script item.
    ExternalScriptItem* currentItem() const;
    /// @return Item for @p index.
    ExternalScriptItem* itemForIndex(const QModelIndex& index) const;

private Q_SLOTS:
    void contextMenu (const QPoint& pos);

    void addScript();
    void removeScript();
    void editScript();

    /// disables or enables available actions based on the currently selected item
    void validateActions();

protected:
    /// insert snippet on double click
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    ExternalScriptPlugin* m_plugin;
    QSortFilterProxyModel* m_model;
    QAction* m_addScriptAction;
    QAction* m_editScriptAction;
    QAction* m_removeScriptAction;
};

#endif // KDEVPLATFORM_PLUGIN_EXTERNALSCRIPTVIEW_H
