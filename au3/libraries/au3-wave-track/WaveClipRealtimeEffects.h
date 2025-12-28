/**********************************************************************

  Audacity: A Digital Audio Editor

  WaveClipRealtimeEffects.h

  (c) 2024 Audacity Team

**********************************************************************/

#ifndef __AUDACITY_WAVECLIP_REALTIME_EFFECTS__
#define __AUDACITY_WAVECLIP_REALTIME_EFFECTS__

#include "WaveClip.h"
#include "au3-realtime-effects/RealtimeEffectList.h"

//! Adapter class to attach RealtimeEffectList to a WaveClip
class WAVE_TRACK_API WaveClipRealtimeEffects final
    : public RealtimeEffectList
    , public WaveClipListener
{
public:
    WaveClipRealtimeEffects(WaveClip& clip);
    ~WaveClipRealtimeEffects() override;

    // WaveClipListener implementation
    void MarkChanged() noexcept override;
    void Invalidate() override;
    void WriteXMLAttributes(XMLWriter& writer) const override;
    void WriteXMLTags(XMLWriter& writer) const override;
    bool HandleXMLAttribute(
        const std::string_view& attr, const XMLAttributeValueView& valueView) override;
    void MakeStereo(WaveClipListener&& other, bool aligned) override;
    void SwapChannels() override;
    void Erase(size_t index) override;

    // ClientData implementation
    std::unique_ptr<ClientData::Cloneable<WaveClipListener>> Clone() const override;

    static RealtimeEffectList& Get(WaveClip& clip);
    static const RealtimeEffectList& Get(const WaveClip& clip);

private:
    WaveClip& mClip;
};

#endif
