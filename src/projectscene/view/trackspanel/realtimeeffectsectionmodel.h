/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "iprojectsceneconfiguration.h"
#include "actions/iactionsdispatcher.h"
#include "actions/actionable.h"
#include "async/asyncable.h"
#include "modularity/ioc.h"
#include <QObject>
#include <map>

namespace au::projectscene {
<<<<<<< HEAD
class RealtimeEffectSectionModel : public QObject, public muse::actions::Actionable, public muse::async::Asyncable
=======
class RealtimeEffectSectionModel : public QObject, public muse::actions::Actionable, public muse::async::Asyncable, public muse::Contextable
>>>>>>> upstream/master
{
    Q_OBJECT

    Q_PROPERTY(bool showEffectsSection READ prop_showEffectsSection WRITE prop_setShowEffectsSection NOTIFY showEffectsSectionChanged)

<<<<<<< HEAD
    muse::Inject<IProjectSceneConfiguration> configuration;
    muse::Inject<muse::actions::IActionsDispatcher> dispatcher;
=======
    muse::GlobalInject<IProjectSceneConfiguration> configuration;

    muse::ContextInject<muse::actions::IActionsDispatcher> dispatcher{ this };
>>>>>>> upstream/master

public:
    explicit RealtimeEffectSectionModel(QObject* parent = nullptr);

    Q_INVOKABLE void load();

    bool prop_showEffectsSection() const;
    void prop_setShowEffectsSection(bool show);

signals:
    void showEffectsSectionChanged();
    void focusEffectsPanelRequested();
};
}
