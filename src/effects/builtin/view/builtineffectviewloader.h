/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include <QObject>
#include <QQmlComponent>
#include <QQuickItem>

#include "global/async/asyncable.h"
#include "modularity/ioc.h"

#include "effects/builtin/ibuiltineffectsviewregister.h"
#include "effects/effects_base/ieffectsuiengine.h"
#include "effects/effects_base/ieffectinstancesregister.h"
#include "effects/effects_base/ieffectsprovider.h"

namespace au::effects {
<<<<<<< HEAD
//! TODO Move to builtin module
class BuiltinEffectViewLoader : public QObject, public muse::async::Asyncable
=======
class BuiltinEffectViewLoader : public QObject, public muse::async::Asyncable, muse::Contextable
>>>>>>> upstream/master
{
    Q_OBJECT

    Q_PROPERTY(QQuickItem * contentItem READ contentItem NOTIFY contentItemChanged FINAL)

<<<<<<< HEAD
    muse::Inject<IEffectsViewRegister> viewRegister;
    muse::Inject<IEffectsUiEngine> engine;
    muse::Inject<IEffectInstancesRegister> instancesRegister;
=======
    muse::GlobalInject<IBuiltinEffectsViewRegister> viewRegister;
    muse::GlobalInject<IEffectInstancesRegister> instancesRegister;
    muse::GlobalInject<IEffectsProvider> effectsProvider;

    muse::ContextInject<IEffectsUiEngine> engine { this };
    muse::ContextInject<IEffectInstancesRegister> instancesRegister { this };
>>>>>>> upstream/master

public:
    ~BuiltinEffectViewLoader() override;

    QQuickItem* contentItem() const;

    Q_INVOKABLE void load(int instanceId, QObject* itemParent, QObject* dialogView, bool usedDestructively);

signals:
    void titleChanged();
    void contentItemChanged();

    void closeRequested();

private:
    QQuickItem* m_contentItem = nullptr;
};
}
