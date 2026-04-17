#include "foldertrack.h"
#include <algorithm>
#include "au3-components/XMLWriter.h"
#include "au3-components/XMLTagHandler.h"
#include "au3-components/StringHelpers.h"

// Define a type for Folder tracks
namespace {
    const std::string_view FOLDER_TRACK_TAG = "foldertrack";
}

FolderTrack::FolderTrack()
    : PlayableTrack()
{
}

FolderTrack::FolderTrack(const FolderTrack& other)
    : PlayableTrack(other)
    , m_expanded(other.m_expanded)
    , m_childTracks(other.m_childTracks)
{
}

FolderTrack::~FolderTrack()
{
}

std::shared_ptr<Track> FolderTrack::Clone() const
{
    return std::make_shared<FolderTrack>(*this);
}

bool FolderTrack::IsExpanded() const
{
    return m_expanded;
}

void FolderTrack::SetExpanded(bool expanded)
{
    if (m_expanded != expanded) {
        m_expanded = expanded;
        Notify();
    }
}

void FolderTrack::AddChildTrack(int trackId)
{
    if (!ContainsChildTrack(trackId)) {
        m_childTracks.push_back(trackId);
        Notify();
    }
}

void FolderTrack::RemoveChildTrack(int trackId)
{
    auto it = std::remove(m_childTracks.begin(), m_childTracks.end(), trackId);
    if (it != m_childTracks.end()) {
        m_childTracks.erase(it, m_childTracks.end());
        Notify();
    }
}

bool FolderTrack::ContainsChildTrack(int trackId) const
{
    return std::find(m_childTracks.begin(), m_childTracks.end(), trackId) != m_childTracks.end();
}

const std::vector<int>& FolderTrack::GetChildTracks() const
{
    return m_childTracks;
}

float FolderTrack::GetChannelVolume(int channel) const
{
    return PlayableTrack::GetChannelVolume(channel);
}

void FolderTrack::SetChannelVolume(int channel, float volume)
{
    PlayableTrack::SetChannelVolume(channel, volume);
}

void FolderTrack::HandleXMLTag(const std::string_view& tag, const AttributesList& attrs)
{
    if (tag == FOLDER_TRACK_TAG) {
        for (const auto& attr : attrs) {
            if (attr.first == "expanded") {
                m_expanded = au3::StringToBool(attr.second);
            }
        }
    }
    PlayableTrack::HandleXMLTag(tag, attrs);
}

XMLTagHandler* FolderTrack::HandleXMLChild(const std::string_view& tag)
{
    // Need a handler for <child_track id="123"/>
    return PlayableTrack::HandleXMLChild(tag);
}

void FolderTrack::WriteXML(XMLWriter& xmlFile) const
{
    xmlFile.StartTag(FOLDER_TRACK_TAG);
    xmlFile.WriteAttr("expanded", m_expanded);

    // Write out children
    for (int childId : m_childTracks) {
        xmlFile.StartTag("child_track");
        xmlFile.WriteAttr("id", childId);
        xmlFile.EndTag("child_track");
    }

    PlayableTrack::WriteXML(xmlFile);
    xmlFile.EndTag(FOLDER_TRACK_TAG);
}
