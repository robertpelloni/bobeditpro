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
#ifndef AU_APPSHELL_SESSIONSMANAGER_H
#define AU_APPSHELL_SESSIONSMANAGER_H

#include "istartupscenario.h"

#include "async/asyncable.h"

#include "modularity/ioc.h"
#include "actions/iactionsdispatcher.h"
#include "context/iglobalcontext.h"
#include "iappshellconfiguration.h"
#include "multiinstances/imultiinstancesprovider.h"
#include "isessionsmanager.h"
#include "au3wrap/iau3project.h"

#include "project/iprojectconfiguration.h"

namespace au::appshell {
<<<<<<< HEAD
class SessionsManager : public ISessionsManager, public muse::async::Asyncable
{
    INJECT(muse::actions::IActionsDispatcher, dispatcher)
    INJECT(au::context::IGlobalContext, globalContext)
    INJECT(IAppShellConfiguration, configuration)
    INJECT(muse::mi::IMultiInstancesProvider, multiInstancesProvider)
    INJECT(project::IProjectConfiguration, projectConfiguration)
    INJECT(muse::io::IFileSystem, fileSystem)
    INJECT(au::au3::IAu3ProjectCreator, au3ProjectCreator)

public:
=======
class SessionsManager : public ISessionsManager, public muse::async::Asyncable, public muse::Contextable
{
    muse::GlobalInject<muse::io::IFileSystem> fileSystem;
    muse::GlobalInject<project::IProjectConfiguration> projectConfiguration;
    muse::GlobalInject<IAppShellConfiguration> configuration;
    muse::GlobalInject<muse::mi::IMultiWindowsProvider> multiwindowsProvider;
    muse::GlobalInject<au::au3::IAu3ProjectCreator> au3ProjectCreator;

    muse::ContextInject<muse::actions::IActionsDispatcher> dispatcher { this };
    muse::ContextInject<au::context::IGlobalContext> globalContext { this };

public:
    SessionsManager(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}

>>>>>>> upstream/master
    void init();
    void deinit();

    bool hasProjectsForRestore() override;

    void restore() override;
    void reset() override;

private:
    void update();

    void removeProjectFromSession(const muse::io::path_t& projectPath);
    void addProjectToSession(const muse::io::path_t& projectPath);

    void removeProjectsUnsavedChanges(const muse::io::paths_t& projectsPaths);
    void removeUnsavedChanges(const muse::io::path_t& projectPath);

    muse::io::path_t m_lastOpenedProjectPath;
};
}

#endif // AU_APPSHELL_SESSIONSMANAGER_H
