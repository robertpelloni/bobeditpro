/**********************************************************************

  Audacity: A Digital Audio Editor

  WaveClipRealtimeEffects.cpp

  (c) 2024 Audacity Team

**********************************************************************/

#include "WaveClipRealtimeEffects.h"
#include "au3-xml/XMLWriter.h"

WaveClipRealtimeEffects::WaveClipRealtimeEffects(WaveClip& clip)
    : mClip{ clip }
{
}

WaveClipRealtimeEffects::~WaveClipRealtimeEffects() = default;

void WaveClipRealtimeEffects::MarkChanged() noexcept
{
    // Realtime effects usually don't change the clip structure,
    // so strictly speaking we might not need to mark the clip as changed
    // for every parameter tweak, but for structural changes (add/remove effect)
    // we definitely should.
    // For now, we rely on the RealtimeEffectList's own state management.
}

void WaveClipRealtimeEffects::Invalidate()
{
    // Called when the clip is resampled or changed destructively.
    // We might want to clear cached states in effects if needed.
}

void WaveClipRealtimeEffects::WriteXMLAttributes(XMLWriter& writer) const
{
}

void WaveClipRealtimeEffects::WriteXMLTags(XMLWriter& writer) const
{
    RealtimeEffectList::WriteXML(writer);
}

bool WaveClipRealtimeEffects::HandleXMLAttribute(
    const std::string_view& attr, const XMLAttributeValueView& valueView)
{
    // Same as above, RealtimeEffectList uses tags, not attributes on the clip.
    return false;
}

 XMLTagHandler* WaveClipRealtimeEffects::HandleXMLChild(const std::string_view& tag)
 {
     if (tag == RealtimeEffectList::XMLTag()) {
         return static_cast<XMLTagHandler*>(this);
     }
     return nullptr;
 }

void WaveClipRealtimeEffects::MakeStereo(WaveClipListener&& other, bool aligned)
{
    // When merging two mono clips into stereo, we need to decide what to do with effects.
    // Usually, we keep the left channel's effects (this).
    // The `other` (right channel) effects are discarded or merged.
    // For now, we do nothing, effectively keeping 'this' effects.
}

void WaveClipRealtimeEffects::SwapChannels()
{
    // Effects are usually processing stereo streams if the clip is stereo.
    // Swapping channels in the clip might require notifying effects,
    // but standard VST/AU handling usually just processes the buffer it gets.
}

void WaveClipRealtimeEffects::Erase(size_t index)
{
    // Handle channel deletion if necessary.
}

std::unique_ptr<ClientData::Cloneable<WaveClipListener>>
WaveClipRealtimeEffects::Clone() const
{
    auto copy = std::make_unique<WaveClipRealtimeEffects>(mClip);
    static_cast<RealtimeEffectList&>(*copy) = *this; // Copy the effects list
    return copy;
}

static const WaveClip::Attachments::RegisteredFactory key{
    [](WaveClip& clip) {
        return std::make_unique<WaveClipRealtimeEffects>(clip);
    }
};

RealtimeEffectList& WaveClipRealtimeEffects::Get(WaveClip& clip)
{
    return clip.Attachments::Get<WaveClipRealtimeEffects>(key);
}

const RealtimeEffectList& WaveClipRealtimeEffects::Get(const WaveClip& clip)
{
    return Get(const_cast<WaveClip&>(clip));
}
