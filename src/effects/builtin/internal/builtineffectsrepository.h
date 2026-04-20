/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "../ibuiltineffectsrepository.h"

namespace au::effects {
class BuiltinEffectsRepository : public IBuiltinEffectsRepository
{
    muse::Inject<IEffectsViewRegister> effectsViewRegister;

public:
    BuiltinEffectsRepository() = default;

    void preInit();
    void init();

    muse::async::Notification effectMetaListUpdated() const override;
    EffectMetaList effectMetaList() const override;
    void registerMeta(const EffectMeta& meta) override;

private:
    muse::async::Notification m_effectMetaListUpdated;
    EffectMetaList m_metas;
};
}
