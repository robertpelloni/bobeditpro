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
#include "systemtraycontroller.h"

#include <QApplication>
#include <QAction>
#include <QIcon>
#include <QPixmap>
#include <QPainter>

#include "log.h"

namespace au::appshell {

SystemTrayController::SystemTrayController(QObject* parent)
    : QObject(parent)
{
    setupTray();
}

SystemTrayController::~SystemTrayController()
{
    if (m_trayIcon) {
        m_trayIcon->hide();
    }
}

bool SystemTrayController::isAvailable() const
{
    return QSystemTrayIcon::isSystemTrayAvailable();
}

bool SystemTrayController::isVisible() const
{
    return m_trayIcon && m_trayIcon->isVisible();
}

void SystemTrayController::setVisible(bool visible)
{
    if (!m_trayIcon) {
        return;
    }

    if (m_trayIcon->isVisible() != visible) {
        m_trayIcon->setVisible(visible);
        emit visibleChanged();
    }
}

QString SystemTrayController::toolTip() const
{
    return m_trayIcon ? m_trayIcon->toolTip() : QString();
}

void SystemTrayController::setToolTip(const QString& toolTip)
{
    if (m_trayIcon && m_trayIcon->toolTip() != toolTip) {
        m_trayIcon->setToolTip(toolTip);
        emit toolTipChanged();
    }
}

bool SystemTrayController::serversRunning() const
{
    return m_serversRunning;
}

void SystemTrayController::setupTray()
{
    if (!isAvailable()) {
        LOGW() << "System tray is not available on this platform.";
        return;
    }

    m_trayIcon = new QSystemTrayIcon(this);

    // Create a fallback default audio waveform icon if resource is not found
    QPixmap pixmap(32, 32);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(56, 132, 255));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(2, 2, 28, 28, 6, 6);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawLine(8, 16, 8, 16);
    painter.drawLine(12, 10, 12, 22);
    painter.drawLine(16, 6, 16, 26);
    painter.drawLine(20, 11, 20, 21);
    painter.drawLine(24, 15, 24, 17);

    m_trayIcon->setIcon(QIcon(pixmap));
    m_trayIcon->setToolTip(QStringLiteral("BobEditPro Audio Workstation"));

    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &SystemTrayController::onActivated);

    updateMenu();
    m_trayIcon->show();
}

void SystemTrayController::updateMenu()
{
    if (!m_trayIcon) {
        return;
    }

    if (!m_contextMenu) {
        m_contextMenu = new QMenu(m_trayIcon ? static_cast<QWidget*>(nullptr) : nullptr);
        m_contextMenu->setParent(this);
    } else {
        m_contextMenu->clear();
    }

    QAction* showHideAction = m_contextMenu->addAction(tr("Show / Hide BobEditPro"));
    connect(showHideAction, &QAction::triggered, this, &SystemTrayController::toggleWindowVisibility);

    QAction* newProjAction = m_contextMenu->addAction(tr("New Project"));
    connect(newProjAction, &QAction::triggered, this, &SystemTrayController::createNewProject);

    m_contextMenu->addSeparator();

    QAction* statusAction = m_contextMenu->addAction(tr("Audio Engines & Servers: Active"));
    statusAction->setEnabled(false);

    m_contextMenu->addSeparator();

    QAction* quitAction = m_contextMenu->addAction(tr("Quit Servers & Application"));
    connect(quitAction, &QAction::triggered, this, &SystemTrayController::quitServersAndApp);

    m_trayIcon->setContextMenu(m_contextMenu);
}

void SystemTrayController::onActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick) {
        toggleWindowVisibility();
    }
}

void SystemTrayController::toggleWindowVisibility()
{
    if (!m_mainWindow) {
        return;
    }

    QWindow* window = m_mainWindow->qWindow();
    if (!window) {
        return;
    }

    if (window->isVisible() && !window->property("isMinimized").toBool()) {
        window->hide();
    } else {
        window->show();
        window->requestActivate();
        window->raise();
    }
}

void SystemTrayController::showNotification(const QString& title, const QString& message)
{
    if (m_trayIcon && m_trayIcon->isVisible()) {
        m_trayIcon->showMessage(title, message, QSystemTrayIcon::Information, 3000);
    }
}

void SystemTrayController::quitServersAndApp()
{
    m_serversRunning = false;
    emit serversRunningChanged();

    if (m_dispatcher) {
        m_dispatcher->dispatch("quit");
    } else {
        QCoreApplication::quit();
    }
}

void SystemTrayController::createNewProject()
{
    if (m_mainWindow) {
        QWindow* window = m_mainWindow->qWindow();
        if (window && !window->isVisible()) {
            window->show();
            window->requestActivate();
        }
    }

    if (m_dispatcher) {
        m_dispatcher->dispatch("project-new");
    }
}

} // namespace au::appshell
