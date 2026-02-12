/*!********************************************************************

  Audacity: A Digital Audio Editor

  @file PlayableTrack.h
  @brief Extends Track with notions of mute and solo setting

  Dominic Mazzoni

  Paul Licameli split from Track.h

**********************************************************************/
#ifndef __AUDACITY_PLAYABLE_TRACK__
#define __AUDACITY_PLAYABLE_TRACK__

#include "au3-preferences/Prefs.h"
#include "au3-track/Track.h"
#include <vector>

struct AuxSend {
    int mDestinationId{ 0 };
    float mAmount{ 0.0f };
    float mPan{ 0.0f };
    bool mPreFader{ false };

    bool operator==(const AuxSend& other) const {
        return mDestinationId == other.mDestinationId &&
               mAmount == other.mAmount &&
               mPan == other.mPan &&
               mPreFader == other.mPreFader;
    }
    bool operator!=(const AuxSend& other) const { return !(*this == other); }
};

//! Track subclass holding data representing sound (as notes, or samples, or ...)
class PLAYABLE_TRACK_API AudioTrack /* not final */ : public Track
{
public:
    AudioTrack();
    AudioTrack(const Track& orig, ProtectedCreationArg&& a);

    static const TypeInfo& ClassTypeInfo();

    // Serialize, not with tags of its own, but as attributes within a tag.
    void WriteXMLAttributes(XMLWriter& WXUNUSED(xmlFile)) const {}

    // Return true iff the attribute is recognized.
    bool HandleXMLAttribute(const std::string_view& /*attr*/, const XMLAttributeValueView& /*value*/)
    { return false; }
};

ENUMERATE_TRACK_TYPE(AudioTrack);

//! AudioTrack subclass that can also be audibly replayed by the program
class PLAYABLE_TRACK_API PlayableTrack /* not final */ : public AudioTrack
{
public:
    PlayableTrack();
    PlayableTrack(const PlayableTrack& orig, ProtectedCreationArg&&);

    static const TypeInfo& ClassTypeInfo();

    bool GetMute() const { return DoGetMute(); }
    bool GetSolo() const { return DoGetSolo(); }
    bool GetNotMute() const { return !DoGetMute(); }
    bool GetNotSolo() const { return !DoGetSolo(); }
    void SetMute(bool m);
    void SetSolo(bool s);

    static constexpr int MasterRouteId = 0;
    int GetRouteId() const { return mRouteId; }
    void SetRouteId(int id) { mRouteId = id; }

    // Serialize, not with tags of its own, but as attributes within a tag.
    void WriteXMLAttributes(XMLWriter& xmlFile) const;

    // Return true iff the attribute is recognized.
    bool HandleXMLAttribute(const std::string_view& attr, const XMLAttributeValueView& value);

    // Aux Sends
    const std::vector<AuxSend>& GetAuxSends() const { return mAuxSends; }
    void AddAuxSend(const AuxSend& send) { mAuxSends.push_back(send); }
    void RemoveAuxSend(int destId);
    void SetAuxSend(int destId, float amount, float pan, bool pre);
    AuxSend* GetAuxSend(int destId);

    void WriteXMLAuxSends(XMLWriter& xmlFile) const;
    bool HandleAuxSendTag(const std::string_view& tag, const AttributesList& attrs);

protected:
    bool DoGetMute() const;
    void DoSetMute(bool value);
    bool DoGetSolo() const;
    void DoSetSolo(bool value);

private:
    int mRouteId{ MasterRouteId };
    std::vector<AuxSend> mAuxSends;
};

ENUMERATE_TRACK_TYPE(PlayableTrack);

enum SoloBehavior {
    SoloBehaviorSimple,
    SoloBehaviorMulti
};

extern PLAYABLE_TRACK_API EnumSetting<SoloBehavior> TracksBehaviorsSolo;

#endif
