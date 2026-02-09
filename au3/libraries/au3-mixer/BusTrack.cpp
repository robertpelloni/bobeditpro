/**********************************************************************

  Audacity: A Digital Audio Editor

  @file BusTrack.cpp

  @brief Implementation of BusTrack.

**********************************************************************/
#include "BusTrack.h"
#include "au3-xml/XMLWriter.h"
#include "au3-strings/TranslatableString.h"
#include "au3-track/Track.h"
#include <memory>

BusTrack::BusTrack()
{
}

BusTrack::BusTrack(const BusTrack& orig, ProtectedCreationArg&&)
    : PlayableTrack(orig, {})
    , mVolume{ orig.mVolume }
    , mPan{ orig.mPan }
{
}

BusTrack::~BusTrack() = default;

static const Track::TypeInfo& typeInfo()
{
    static const Track::TypeInfo info{
        { "bus", "bus", XO("Bus Track") },
        true,
        &PlayableTrack::ClassTypeInfo()
    };
    return info;
}

const Track::TypeInfo& BusTrack::ClassTypeInfo()
{
    return typeInfo();
}

const Track::TypeInfo& BusTrack::GetTypeInfo() const
{
    return typeInfo();
}

auto BusTrack::Clone(bool backup) const -> Holder
{
   auto copy = std::make_shared<BusTrack>(*this, ProtectedCreationArg{});
   return copy;
}

auto BusTrack::TrackEmptyCopy() const -> Holder
{
    auto copy = std::make_shared<BusTrack>();
    copy->Init(*this);
    return copy;
}

auto BusTrack::PasteInto(AudacityProject& project, TrackList& list) const -> Holder
{
   auto t = std::make_shared<BusTrack>();
   list.Add(t);
   t->Init(*this);
   return t;
}

auto BusTrack::Cut(double t0, double t1, bool moveClips) -> Holder
{
    return {};
}

auto BusTrack::Copy(double t0, double t1, bool forClipboard) const -> Holder
{
    return {};
}

void BusTrack::Clear(double t0, double t1, bool moveClips)
{
}

void BusTrack::Paste(double t, const Track& src, bool moveClips)
{
}

void BusTrack::Silence(double t0, double t1, ProgressReporter reportProgress)
{
}

void BusTrack::InsertSilence(double t, double len)
{
}

void BusTrack::WriteXML(XMLWriter& xmlFile) const
{
    xmlFile.StartTag(wxT("bustrack"));
    this->WriteCommonXMLAttributes(xmlFile);
    this->PlayableTrack::WriteXMLAttributes(xmlFile);

    xmlFile.WriteAttr(wxT("gain"), mVolume);
    xmlFile.WriteAttr(wxT("pan"), mPan);

    xmlFile.EndTag(wxT("bustrack"));
}

bool BusTrack::HandleXMLAttribute(const std::string_view& attr, const XMLAttributeValueView& valueView)
{
    if (PlayableTrack::HandleXMLAttribute(attr, valueView))
        return true;

    if (attr == "gain") {
        mVolume = valueView.ToDouble();
        return true;
    }
    if (attr == "pan") {
        mPan = valueView.ToDouble();
        return true;
    }

    return false;
}
