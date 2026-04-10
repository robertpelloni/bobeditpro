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

#include "appshellmodule.h"

#include <QQmlEngine>

#include "modularity/ioc.h"

#include "ui/iuiactionsregister.h"
#include "ui/iinteractiveuriregister.h"

#include "internal/applicationuiactions.h"
#include "internal/applicationactioncontroller.h"
#include "internal/appshellconfiguration.h"
#include "internal/startupscenario.h"
#include "internal/sessionsmanager.h"

#include "view/devtools/settingslistmodel.h"
#include "view/mainwindowtitleprovider.h"
#include "view/projectpagemodel.h"
//#include "view/notationstatusbarmodel.h"
#include "view/aboutmodel.h"
#include "view/firstlaunchsetup/firstlaunchsetupmodel.h"
#include "view/firstlaunchsetup/themespagemodel.h"
#include "view/firstlaunchsetup/clipvisualizationpagemodel.h"
#include "view/firstlaunchsetup/workspacelayoutpagemodel.h"
#include "view/preferences/preferencesmodel.h"
#include "view/preferences/generalpreferencesmodel.h"
#include "view/preferences/editpreferencesmodel.h"
#include "view/preferences/pluginpreferencesmodel.h"
// #include "view/preferences/updatepreferencesmodel.h"
#include "view/preferences/appearancepreferencesmodel.h"
// #include "view/preferences/folderspreferencesmodel.h"
// #include "view/preferences/noteinputpreferencesmodel.h"
// #include "view/preferences/advancedpreferencesmodel.h"
// #include "view/preferences/canvaspreferencesmodel.h"
// #include "view/preferences/saveandpublishpreferencesmodel.h"
// #include "view/preferences/scorepreferencesmodel.h"
// #include "view/preferences/importpreferencesmodel.h"
#include "view/preferences/playbackpreferencesmodel.h"
#include "view/preferences/recordingpreferencesmodel.h"
#include "view/preferences/commonaudioapiconfigurationmodel.h"
// #include "view/preferences/braillepreferencesmodel.h"
#include "view/framelesswindow/framelesswindowmodel.h"
#include "view/publish/publishtoolbarmodel.h"
#include "view/windowdroparea.h"
#include "view/internal/maintoolbarmodel.h"

#ifdef Q_OS_MAC
#include "view/appmenumodel.h"
#include "view/internal/platform/macos/macosappmenumodelhook.h"
#else
#include "view/navigableappmenumodel.h"
#endif

using namespace au::appshell;
<<<<<<< HEAD
using namespace au::appshell;
using namespace mu;
using namespace muse;
using namespace muse::modularity;
using namespace muse::ui;

static void appshell_init_qrc()
{
    Q_INIT_RESOURCE(appshell);
}
=======

static const std::string mname("appshell");
>>>>>>> upstream/master

AppShellModule::AppShellModule()
{
}

std::string AppShellModule::moduleName() const
{
    return mname;
}

void AppShellModule::registerExports()
{
<<<<<<< HEAD
    m_applicationActionController = std::make_shared<ApplicationActionController>();
    m_applicationUiActions = std::make_shared<ApplicationUiActions>(m_applicationActionController);
    m_appShellConfiguration = std::make_shared<AppShellConfiguration>();
    m_sessionsManager = std::make_shared<SessionsManager>();

    ioc()->registerExport<IAppShellConfiguration>(moduleName(), m_appShellConfiguration);
    ioc()->registerExport<IApplicationActionController>(moduleName(), m_applicationActionController);
    ioc()->registerExport<IStartupScenario>(moduleName(), new StartupScenario());
    ioc()->registerExport<ISessionsManager>(moduleName(), m_sessionsManager);
=======
    m_appShellConfiguration = std::make_shared<AppShellConfiguration>(muse::modularity::globalCtx());

    globalIoc()->registerExport<IAppShellConfiguration>(mname, m_appShellConfiguration);
>>>>>>> upstream/master

#ifdef Q_OS_MAC
    globalIoc()->registerExport<IAppMenuModelHook>(mname, std::make_shared<MacOSAppMenuModelHook>());
#else
    globalIoc()->registerExport<IAppMenuModelHook>(mname, std::make_shared<AppMenuModelHookStub>());
#endif
}

void AppShellModule::resolveImports()
{
<<<<<<< HEAD
    auto ar = ioc()->resolve<ui::IUiActionsRegister>(moduleName());
    if (ar) {
        ar->reg(m_applicationUiActions);
    }

    auto ir = ioc()->resolve<IInteractiveUriRegister>(moduleName());
    if (ir) {
        ir->registerUri(Uri("musescore://home"), ContainerMeta(ContainerType::PrimaryPage));
        ir->registerUri(Uri("audacity://project"), ContainerMeta(ContainerType::PrimaryPage));
        ir->registerUri(Uri("musescore://sequencer"), ContainerMeta(ContainerType::PrimaryPage));
        ir->registerUri(Uri("musescore://publish"), ContainerMeta(ContainerType::PrimaryPage));
        ir->registerUri(Uri("musescore://devtools"), ContainerMeta(ContainerType::PrimaryPage));
        ir->registerUri(Uri("musescore://about/musescore"), ContainerMeta(ContainerType::QmlDialog, "AboutDialog.qml"));
        ir->registerUri(Uri("musescore://about/musicxml"), ContainerMeta(ContainerType::QmlDialog, "AboutMusicXMLDialog.qml"));
        ir->registerUri(Uri("musescore://firstLaunchSetup"),
                        ContainerMeta(ContainerType::QmlDialog, "FirstLaunchSetup/FirstLaunchSetupDialog.qml"));
        ir->registerUri(Uri("audacity://alphaWelcomePopup"), ContainerMeta(ContainerType::QmlDialog, "AlphaWelcomePopup.qml"));
        ir->registerUri(Uri("audacity://preferences"), ContainerMeta(ContainerType::QmlDialog, "Preferences/PreferencesDialog.qml"));
    }
}

void AppShellModule::registerResources()
{
    appshell_init_qrc();
}

void AppShellModule::registerUiTypes()
{
    qmlRegisterType<SettingListModel>("Audacity.Preferences", 1, 0, "SettingListModel");
    qmlRegisterType<PreferencesModel>("Audacity.Preferences", 1, 0, "PreferencesModel");
    qmlRegisterType<GeneralPreferencesModel>("Audacity.Preferences", 1, 0, "GeneralPreferencesModel");
    qmlRegisterType<EditPreferencesModel>("Audacity.Preferences", 1, 0, "EditPreferencesModel");
    qmlRegisterType<PluginPreferencesModel>("Audacity.Preferences", 1, 0, "PluginPreferencesModel");
    // qmlRegisterType<UpdatePreferencesModel>("MuseScore.Preferences", 1, 0, "UpdatePreferencesModel");
    qmlRegisterType<AppearancePreferencesModel>("Audacity.Preferences", 1, 0, "AppearancePreferencesModel");
    // qmlRegisterType<FoldersPreferencesModel>("MuseScore.Preferences", 1, 0, "FoldersPreferencesModel");
    // qmlRegisterType<NoteInputPreferencesModel>("MuseScore.Preferences", 1, 0, "NoteInputPreferencesModel");
    // qmlRegisterType<AdvancedPreferencesModel>("MuseScore.Preferences", 1, 0, "AdvancedPreferencesModel");
    // qmlRegisterType<CanvasPreferencesModel>("MuseScore.Preferences", 1, 0, "CanvasPreferencesModel");
    // qmlRegisterType<SaveAndPublishPreferencesModel>("MuseScore.Preferences", 1, 0, "SaveAndPublishPreferencesModel");
    // qmlRegisterType<ScorePreferencesModel>("MuseScore.Preferences", 1, 0, "ScorePreferencesModel");
    // qmlRegisterType<ImportPreferencesModel>("MuseScore.Preferences", 1, 0, "ImportPreferencesModel");
    qmlRegisterType<PlaybackPreferencesModel>("Audacity.Preferences", 1, 0, "PlaybackPreferencesModel");
    qmlRegisterType<RecordingPreferencesModel>("Audacity.Preferences", 1, 0, "RecordingPreferencesModel");
    qmlRegisterType<CommonAudioApiConfigurationModel>("Audacity.Preferences", 1, 0, "CommonAudioApiConfigurationModel");
    // qmlRegisterType<BraillePreferencesModel>("MuseScore.Preferences", 1, 0, "BraillePreferencesModel");

#if defined(Q_OS_MACOS)
    qmlRegisterType<AppMenuModel>("Audacity.AppShell", 1, 0, "PlatformAppMenuModel");
#elif defined(Q_OS_LINUX) || defined(Q_OS_FREEBSD)
    qmlRegisterType<AppMenuModel>("Audacity.AppShell", 1, 0, "PlatformAppMenuModel");
    qmlRegisterType<NavigableAppMenuModel>("Audacity.AppShell", 1, 0, "AppMenuModel");
#else
    qmlRegisterType<NavigableAppMenuModel>("Audacity.AppShell", 1, 0, "AppMenuModel");
#endif

    qmlRegisterType<MainWindowTitleProvider>("Audacity.AppShell", 1, 0, "MainWindowTitleProvider");
    qmlRegisterType<ProjectPageModel>("Audacity.AppShell", 1, 0, "ProjectPageModel");
//    qmlRegisterType<NotationStatusBarModel>("Audacity.AppShell", 1, 0, "NotationStatusBarModel");
    qmlRegisterType<AboutModel>("Audacity.AppShell", 1, 0, "AboutModel");
    qmlRegisterType<FirstLaunchSetupModel>("Audacity.AppShell", 1, 0, "FirstLaunchSetupModel");
    qmlRegisterType<ThemesPageModel>("Audacity.AppShell", 1, 0, "ThemesPageModel");
    qmlRegisterType<ClipVisualizationPageModel>("Audacity.AppShell", 1, 0, "ClipVisualizationPageModel");
    qmlRegisterType<WorkspaceLayoutPageModel>("Audacity.AppShell", 1, 0, "WorkspaceLayoutPageModel");
    qmlRegisterType<FramelessWindowModel>("Audacity.AppShell", 1, 0, "FramelessWindowModel");
    qmlRegisterType<PublishToolBarModel>("Audacity.AppShell", 1, 0, "PublishToolBarModel");
    qmlRegisterType<MainToolBarModel>("Audacity.AppShell", 1, 0, "MainToolBarModel");

    qmlRegisterType<WindowDropArea>("Audacity.AppShell", 1, 0, "WindowDropArea");
}

void AppShellModule::onPreInit(const IApplication::RunMode& mode)
{
    if (mode == IApplication::RunMode::AudioPluginRegistration) {
        return;
    }

    m_applicationActionController->preInit();
}

void AppShellModule::onInit(const IApplication::RunMode& mode)
=======
    auto ir = globalIoc()->resolve<muse::interactive::IInteractiveUriRegister>(mname);
    if (ir) {
        ir->registerPageUri(muse::Uri("audacity://home"));
        ir->registerPageUri(muse::Uri("audacity://project"));
        ir->registerPageUri(muse::Uri("audacity://publish"));
        ir->registerPageUri(muse::Uri("audacity://devtools"));

        ir->registerQmlUri(muse::Uri("audacity://about/audacity"), "Audacity.AppShell", "AboutDialog");
        ir->registerQmlUri(muse::Uri("audacity://firstLaunchSetup"), "Audacity.AppShell", "FirstLaunchSetupDialog");
        ir->registerQmlUri(muse::Uri("audacity://signin/audiocom"), "Audacity.AppShell", "SigninAudiocomDialog");
        ir->registerQmlUri(muse::Uri("audacity://welcomedialog"), "Audacity.AppShell", "WelcomeDialog");
    }
}

void AppShellModule::onInit(const muse::IApplication::RunMode& mode)
>>>>>>> upstream/master
{
    if (mode == IApplication::RunMode::AudioPluginRegistration) {
        return;
    }

    m_appShellConfiguration->init();
}

muse::modularity::IContextSetup* AppShellModule::newContext(const muse::modularity::ContextPtr& ctx) const
{
    return new AppShellContext(ctx);
}

// =====================================================
// AppShellContext
// =====================================================

void AppShellContext::registerExports()
{
    m_applicationActionController = std::make_shared<ApplicationActionController>(iocContext());
    m_applicationUiActions = std::make_shared<ApplicationUiActions>(iocContext(), m_applicationActionController);
    m_sessionsManager = std::make_shared<SessionsManager>(iocContext());

    ioc()->registerExport<IApplicationActionController>(mname, m_applicationActionController);
    ioc()->registerExport<IStartupScenario>(mname, new StartupScenario(iocContext()));
    ioc()->registerExport<ISessionsManager>(mname, m_sessionsManager);
}

void AppShellContext::onPreInit(const muse::IApplication::RunMode& mode)
{
    if (mode == muse::IApplication::RunMode::AudioPluginRegistration) {
        return;
    }

    m_applicationActionController->preInit();
}

void AppShellContext::onInit(const muse::IApplication::RunMode& mode)
{
    if (mode == muse::IApplication::RunMode::AudioPluginRegistration) {
        return;
    }

    m_applicationActionController->init();
    m_applicationUiActions->init();
    m_sessionsManager->init();

    auto ar = ioc()->resolve<muse::ui::IUiActionsRegister>(mname);
    if (ar) {
        ar->reg(m_applicationUiActions);
    }
}

<<<<<<< HEAD
void AppShellModule::onAllInited(const IApplication::RunMode& mode)
=======
void AppShellContext::onAllInited(const muse::IApplication::RunMode& mode)
>>>>>>> upstream/master
{
    if (mode == IApplication::RunMode::AudioPluginRegistration) {
        return;
    }

    //! NOTE: process QEvent::FileOpen as early as possible if it was postponed
#ifdef Q_OS_MACOS
    qApp->processEvents();
#endif
}

void AppShellContext::onDeinit()
{
    m_sessionsManager->deinit();
}
