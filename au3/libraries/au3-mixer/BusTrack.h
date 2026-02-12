/**********************************************************************

  Audacity: A Digital Audio Editor

  @file BusTrack.h

  @brief A track that acts as a mixing bus.

**********************************************************************/
#pragma once

#include "au3-playable-track/PlayableTrack.h"
#include "au3-mixer/AudioIOSequences.h" // For MIXER_API

//! A track that acts as a mixing bus, summing inputs from other tracks.
class MIXER_API BusTrack final : public PlayableTrack
{
public:
    BusTrack();
    BusTrack(const BusTrack& orig, ProtectedCreationArg&&);
    ~BusTrack() override;

    static const TypeInfo& ClassTypeInfo();
    const TypeInfo& GetTypeInfo() const override;

    // Track overrides
    Holder Clone(bool backup) const override;
    Holder TrackEmptyCopy() const override;

    Holder PasteInto(AudacityProject& project, TrackList& list) const override;

    // Editing operations (mostly no-ops for BusTrack content)
    Holder Cut(double t0, double t1, bool moveClips) override;
    Holder Copy(double t0, double t1, bool forClipboard = true) const override;
    void Clear(double t0, double t1, bool moveClips) override;
    void Paste(double t, const Track& src, bool moveClips) override;
    void Silence(double t0, double t1, ProgressReporter reportProgress = {}) override;
    void InsertSilence(double t, double len) override;

    // Serialization
    void WriteXML(XMLWriter& xmlFile) const override;
    // BusTrack inherits Track::HandleCommonXMLAttribute and PlayableTrack::HandleXMLAttribute
    bool HandleXMLAttribute(const std::string_view& attr, const XMLAttributeValueView& value);

    // Child tag handling for Aux Sends
    bool HandleXMLTag(const std::string_view& tag, const AttributesList& attrs) override;
    XMLTagHandler* HandleXMLChild(const std::string_view& tag) override;

    float GetVolume() const { return mVolume; }
    void SetVolume(float v) { mVolume = v; }

    float GetPan() const { return mPan; }
    void SetPan(float p) { mPan = p; }

private:
    float mVolume{ 1.0f };
    float mPan{ 0.0f };
};

ENUMERATE_TRACK_TYPE(BusTrack);
