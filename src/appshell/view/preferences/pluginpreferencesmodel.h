/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "effects/effects_base/effectstypes.h"
#include "effects/effects_base/ieffectsconfiguration.h"
#include "effects/effects_base/ieffectsprovider.h"
#include "async/asyncable.h"
#include "modularity/ioc.h"

#include <QObject>

namespace au::appshell {
class PluginPreferencesModel : public QObject, public muse::async::Asyncable
{
    Q_OBJECT

    Q_PROPERTY(effects::EffectMenuOrganization effectMenuOrganization READ effectMenuOrganization NOTIFY effectMenuOrganizationChanged)

    muse::Inject<effects::IEffectsConfiguration> effectsConfiguration;

public:
    explicit PluginPreferencesModel(QObject* parent = nullptr);

    effects::EffectMenuOrganization effectMenuOrganization() const;
    Q_INVOKABLE void setEffectMenuOrganization(effects::EffectMenuOrganization);

    QStringList lv2CustomPaths() const;
    QStringList vst3CustomPaths() const;

    bool lv2Supported() const;
    bool vst3Supported() const;

    Q_INVOKABLE void addLv2Path();
    Q_INVOKABLE void setLv2Path(int index, const QString& path);
    Q_INVOKABLE void removeLv2Path(int index);

    Q_INVOKABLE void addVst3Path();
    Q_INVOKABLE void setVst3Path(int index, const QString& path);
    Q_INVOKABLE void removeVst3Path(int index);

    Q_INVOKABLE bool pathExists(const QString& path) const;

    Q_INVOKABLE void init();

signals:
    void effectMenuOrganizationChanged();
    void lv2CustomPathsChanged();
    void vst3CustomPathsChanged();
};
}
