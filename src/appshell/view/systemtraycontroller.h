/*
 * SPDX-License-Identifier: GPL-3.0-only
 * Audacity-CLA-applies
 *
 * Audacity
 * A Digital Audio Editor
 *
 * Copyright (C) 2024 Audacity BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef AU_APPSHELL_SYSTEMTRAYCONTROLLER_H
#define AU_APPSHELL_SYSTEMTRAYCONTROLLER_H

#include <QObject>
#include <QString>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QPointer>
#include <QWindow>

#include "async/asyncable.h"
#include "modularity/ioc.h"
#include "context/iglobalcontext.h"
#include "actions/iactionsdispatcher.h"
#include "mainwindow/imainwindow.h"

namespace au::appshell {

class SystemTrayController : public QObject, public muse::async::Asyncable
{
    Q_OBJECT

    muse::Inject<context::IGlobalContext> m_globalContext;
    muse::Inject<muse::actions::IActionsDispatcher> m_dispatcher;
    muse::Inject<muse::ui::IMainWindow> m_mainWindow;

    Q_PROPERTY(bool available READ isAvailable CONSTANT)
    Q_PROPERTY(bool visible READ isVisible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QString toolTip READ toolTip WRITE setToolTip NOTIFY toolTipChanged)
    Q_PROPERTY(bool serversRunning READ serversRunning NOTIFY serversRunningChanged)

public:
    explicit SystemTrayController(QObject* parent = nullptr);
    ~SystemTrayController() override;

    bool isAvailable() const;
    bool isVisible() const;
    void setVisible(bool visible);

    QString toolTip() const;
    void setToolTip(const QString& toolTip);

    bool serversRunning() const;

    Q_INVOKABLE void showNotification(const QString& title, const QString& message);
    Q_INVOKABLE void toggleWindowVisibility();
    Q_INVOKABLE void quitServersAndApp();
    Q_INVOKABLE void createNewProject();

signals:
    void visibleChanged();
    void toolTipChanged();
    void serversRunningChanged();

private slots:
    void onActivated(QSystemTrayIcon::ActivationReason reason);

private:
    void setupTray();
    void updateMenu();

    QPointer<QSystemTrayIcon> m_trayIcon;
    QPointer<QMenu> m_contextMenu;
    bool m_serversRunning = true;
};

} // namespace au::appshell

#endif // AU_APPSHELL_SYSTEMTRAYCONTROLLER_H
