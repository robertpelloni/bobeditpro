/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include <QObject>

#include "../ieffectsuiengine.h"

#include "modularity/ioc.h"
#include "ui/iuiengine.h"

namespace au::effects {
class QmlApiEngine;
<<<<<<< HEAD
class EffectsUiEngine : public QObject, public IEffectsUiEngine
{
    Q_OBJECT

    muse::Inject<muse::ui::IUiEngine> uiEngine;

public:
=======
class EffectsUiEngine : public QObject, public IEffectsUiEngine, public muse::Contextable
{
    Q_OBJECT

    muse::ContextInject<muse::ui::IUiEngine> uiEngine{ this };

public:
    EffectsUiEngine(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}
>>>>>>> upstream/master
    ~EffectsUiEngine() override;

    QQmlEngine* qmlEngine() const override;

private:
    QQmlEngine* engine();
    void setup();

    QQmlEngine* m_engine = nullptr;
};
}
