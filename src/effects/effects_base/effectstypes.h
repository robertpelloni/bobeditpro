/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

#include "framework/global/types/string.h"
#include "framework/global/types/ratio.h"
#include "framework/actions/actiontypes.h"

class Effect;
class EffectInstanceEx;
class RealtimeEffectState;
class EffectSettingsAccess;
struct EffectSettings;
class wxString;

namespace muse {
class String;
namespace uicomponents {
class MenuItem;
using MenuItemList = QList<MenuItem*>;
}
}

namespace au::effects {
using secs_t = muse::number_t<double>;
using percent_t = muse::number_t<float>;
using ratio_t = muse::ratio_t;
using db_t = muse::db_t;
using rms_t = float;

using EffectId = muse::String;              // PluginID from AU3
using Effect = ::Effect;                    // Effect from AU3
using EffectInstanceId = int;
using EffectInstance = ::EffectInstanceEx;  // EffectInstanceEx from AU3
using EffectSettings = ::EffectSettings;
using EffectSettingsAccess = ::EffectSettingsAccess;
using EffectSettingsAccessPtr = std::shared_ptr<EffectSettingsAccess>;
using RealtimeEffectState = ::RealtimeEffectState;
using RealtimeEffectStatePtr = std::shared_ptr<RealtimeEffectState>;
using TrackId = long;
using EffectChainLinkIndex = int;

static const muse::String EFFECT_TITLE_ATTRIBUTE(u"title");
static const muse::String EFFECT_DESCRIPTION_ATTRIBUTE(u"description");
static const muse::String EFFECT_TYPE_ATTRIBUTE(u"type");
static const muse::String EFFECT_CATEGORY_ATTRIBUTE(u"category");
static const muse::String EFFECT_IS_REALTIME_CAPABLE_ATTRIBUTE(u"isRealtimeCapable");
static const muse::String EFFECT_PARAMS_ARE_INPUT_AGNOSTIC_ATTRIBUTE(u"paramsAreInputAgnostic");
static const muse::String EFFECT_VERSION_ATTRIBUTE(u"version");
static const muse::String EFFECT_MODULE_ATTRIBUTE(u"module");
static const muse::String EFFECT_ACTIVATED_ATTRIBUTE(u"activated"); // `AudioPluginInfo`'s `enabled` field actually has semantic "valid".

enum class EffectMenuOrganization {
    Grouped = 0,
    Flat = 1,
};

enum class EffectUIMode {
    VendorUI = 0,      // Use plugin's native/graphical UI
    FallbackUI = 1,   // Use Audacity's fallback UI
};

class EffectFamilies
{
    Q_GADGET
public:
    enum class EffectFamily {
        Unknown = -1,
        Builtin,
        VST3,
#ifdef Q_OS_LINUX
        LV2,
#endif
#ifdef Q_OS_MACOS
        AudioUnit,
#endif
        Nyquist,
        _count
    };
    Q_ENUM(EffectFamily)
};

using EffectFamily = EffectFamilies::EffectFamily;

enum class EffectCategory {
    Unspecified = -1,
    None,
    VolumeAndCompression,
    Fading,
    PitchAndTempo,
    EqAndFilters,
    NoiseRemovalAndRepair,
    DelayAndReverb,
    DistortionAndModulation,
    Special,
    SpectralTools,
    Legacy,
};

enum class EffectType {
    Unknown = -1,
    Analyzer,
    Generator,
    Processor,
    Tool,
    _count
};

struct EffectMeta {
    EffectId id;
    EffectFamily family = EffectFamily::Unknown;
    EffectType type = EffectType::Unknown;
    muse::String title;
    muse::String description;
    muse::String vendor;
    muse::String version;
    muse::String module;
    muse::io::path_t path;

    muse::String category;

    bool isRealtimeCapable = false;
    bool paramsAreInputAgnostic = true;
    bool isActivated = true;
    bool isLoadable = true;

    bool isValid() const { return !id.empty(); }
};

using EffectMetaList = std::vector<EffectMeta>;

const std::string EFFECT_OPEN_ACTION = "action://effects/open?effectId=%1";
const std::string REALTIME_EFFECT_ADD_ACTION = "action://effects/realtime-add?effectId=%1";
const std::string REALTIME_EFFECT_REPLACE_ACTION = "action://effects/realtime-replace?effectId=%1";

const std::string DESTRUCTIVE_EFFECT_VIEWER_URI = "audacity://effects/destructive_viewer?instanceId=%1&effectFamily=%2";

inline std::string makeEffectAction(const std::string& action, const EffectId& id)
{
    return QString::fromStdString(action).arg(id).toStdString();
}

inline EffectId effectIdFromAction(const muse::actions::ActionQuery& action)
{
    return EffectId::fromStdString(action.param("effectId").toString());
}

inline EffectId effectIdFromAction(const QString& action)
{
    return effectIdFromAction(muse::actions::ActionQuery { action });
}

using PresetId = wxString;
using PresetIdList = std::vector<PresetId>;

struct PresetKey {
    EffectId effectId;
    std::string realtimeEffectState;
};

struct PresetSavedInfo {
    EffectInstanceId instanceId = -1;
    EffectId effectId;
    std::string presetId;
};

class IEffectMenuItemFactory
{
public:
    virtual ~IEffectMenuItemFactory() = default;
    virtual muse::uicomponents::MenuItem* makeMenuSeparator() = 0;
    virtual muse::uicomponents::MenuItem* makeMenuEffectItem(const EffectId& effectId) = 0;
    virtual muse::uicomponents::MenuItem* makeMenuEffect(const muse::String& title, const muse::uicomponents::MenuItemList& items) = 0;
};
}
