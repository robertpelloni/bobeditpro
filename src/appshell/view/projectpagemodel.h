/*
* Audacity: A Digital Audio Editor
*/
#ifndef AU_APPSHELL_PROJECTPAGEMODEL_H
#define AU_APPSHELL_PROJECTPAGEMODEL_H

#include "framework/global/modularity/ioc.h"
#include "framework/global/async/asyncable.h"
#include "framework/actions/actionable.h"
#include "framework/actions/iactionsdispatcher.h"
#include "framework/dockwindow/idockwindowprovider.h"
#include "framework/ui/iuiconfiguration.h"
#include "framework/ui/iuistate.h"

#include "context/iglobalcontext.h"
#include "playback/iplaybackconfiguration.h"

#include "iappshellconfiguration.h"

//! TODO AU4
// #include "braille/ibrailleconfiguration.h"

namespace au::appshell {
class ProjectPageModel : public QObject, public muse::async::Asyncable, public muse::actions::Actionable
{
    Q_OBJECT

    muse::Inject<muse::actions::IActionsDispatcher> dispatcher;
    muse::Inject<au::context::IGlobalContext> globalContext;
    muse::Inject<muse::dock::IDockWindowProvider> dockWindowProvider;
    muse::Inject<IAppShellConfiguration> configuration;
    muse::Inject<muse::ui::IUiConfiguration> uiConfiguration;
    muse::Inject<playback::IPlaybackConfiguration> playbackConfiguration;

//! TODO AU4
//    INJECT(braille::IBrailleConfiguration, brailleConfiguration)

    Q_PROPERTY(bool isNavigatorVisible READ isNavigatorVisible NOTIFY isNavigatorVisibleChanged)
    Q_PROPERTY(bool isBraillePanelVisible READ isBraillePanelVisible NOTIFY isBraillePanelVisibleChanged)

public:
    explicit ProjectPageModel(QObject* parent = nullptr);

    Q_INVOKABLE void init();

    Q_INVOKABLE QString projectToolBarName() const;
    Q_INVOKABLE QString playbackToolBarName() const;
    Q_INVOKABLE QString undoRedoToolBarName() const;
    Q_INVOKABLE QString workspacesToolBarName() const;

    Q_INVOKABLE QString tracksPanelName() const;
    Q_INVOKABLE QString historyPanelName() const;
    Q_INVOKABLE QString playbackMeterPanelName() const;

    Q_INVOKABLE QString statusBarName() const;

private:
    void toggleDock(const QString& name);

    void updatePlaybackMeterVisibility();

    bool m_inited = false;
};
}

#endif // AU_APPSHELL_PROJECTPAGEMODEL_H
