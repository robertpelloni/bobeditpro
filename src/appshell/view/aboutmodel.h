/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
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
#ifndef MU_APPSHELL_ABOUTMODEL_H
#define MU_APPSHELL_ABOUTMODEL_H

#include <QObject>

#include "modularity/ioc.h"
#include "iappshellconfiguration.h"
#include "global/iglobalconfiguration.h"
#include "global/iapplication.h"

#include "update/iupdateconfiguration.h"

class QUrl;

namespace au::appshell {
<<<<<<< HEAD:src/appshell/view/aboutmodel.h
class AboutModel : public QObject
=======
class AboutModel : public QObject, public muse::Contextable
>>>>>>> upstream/master:src/appshell/qml/Audacity/AppShell/aboutmodel.h
{
    Q_OBJECT

<<<<<<< HEAD:src/appshell/view/aboutmodel.h
    muse::Inject<IAppShellConfiguration> configuration;
    muse::Inject<muse::IGlobalConfiguration> globalConfiguration;
    muse::Inject<muse::IApplication> application;
=======
    muse::GlobalInject<IAppShellConfiguration> configuration;
    muse::GlobalInject<muse::IGlobalConfiguration> globalConfiguration;
    muse::GlobalInject<muse::IApplication> application;
>>>>>>> upstream/master:src/appshell/qml/Audacity/AppShell/aboutmodel.h

//! TODO AU4
//     muse::Inject<update::IUpdateConfiguration> updateConfiguration;

public:
    explicit AboutModel(QObject* parent = nullptr);

    Q_INVOKABLE QString appVersion() const;
    Q_INVOKABLE QString appRevision() const;
    Q_INVOKABLE QVariantMap appUrl() const;
    Q_INVOKABLE QVariantMap forumUrl() const;
    Q_INVOKABLE QVariantMap contributionUrl() const;
    Q_INVOKABLE QVariantMap privacyPolicyUrl() const;

    Q_INVOKABLE void copyRevisionToClipboard() const;

    Q_INVOKABLE void toggleDevMode();

private:
    QVariantMap makeUrl(const QUrl& url, bool showPath = true) const;
};
}

#endif // MU_APPSHELL_ABOUTMODEL_H
