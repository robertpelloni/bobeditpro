#include "MultibandCompressorEffect.h"
#include "au3-translations/au3-translations.h"

namespace au::effects {

const ComponentInterfaceSymbol MultibandCompressorEffect::Symbol{
    XO("Multiband Compressor")
};

MultibandCompressorEffect::MultibandCompressorEffect() {
}

MultibandCompressorEffect::~MultibandCompressorEffect() {
}

ComponentInterfaceSymbol MultibandCompressorEffect::GetSymbol() const {
    return Symbol;
}

::EffectType MultibandCompressorEffect::GetType() const {
    return EffectTypeProcess;
}

OptionalMessage MultibandCompressorEffect::LoadFactoryDefaults(EffectSettings& settings) const {
    return {};
}

unsigned MultibandCompressorEffect::GetAudioInCount() const {
    return 1;
}

unsigned MultibandCompressorEffect::GetAudioOutCount() const {
    return 1;
}

size_t MultibandCompressorEffect::ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock, size_t blockLen) {
    // Basic pass-through for now
    for (size_t c = 0; c < GetAudioInCount(); ++c) {
        if (inBlock[c] && outBlock[c]) {
            std::copy(inBlock[c], inBlock[c] + blockLen, outBlock[c]);
        }
    }
    return blockLen;
}

MultibandCompressorEffect::Instance::~Instance() {
}

bool MultibandCompressorEffect::Init() {
    return true;
}

}
