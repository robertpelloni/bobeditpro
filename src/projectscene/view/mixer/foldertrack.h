#pragma once

#include "au3-playable-track-interface/PlayableTrack.h"
#include <vector>
#include <memory>

/**
 * @brief Represents a Track Folder in the timeline.
 * A FolderTrack can visually collapse/expand child tracks and function as a VCA group or an implicit Bus.
 */
class FolderTrack final : public PlayableTrack {
public:
    FolderTrack();
    FolderTrack(const FolderTrack& other);
    ~FolderTrack() override;

    std::shared_ptr<Track> Clone() const override;

    bool IsExpanded() const;
    void SetExpanded(bool expanded);

    // Track containment
    void AddChildTrack(int trackId);
    void RemoveChildTrack(int trackId);
    bool ContainsChildTrack(int trackId) const;
    const std::vector<int>& GetChildTracks() const;

    // PlayableTrack overrides
    void HandleXMLTag(const std::string_view& tag, const AttributesList& attrs) override;
    XMLTagHandler* HandleXMLChild(const std::string_view& tag) override;
    void WriteXML(XMLWriter& xmlFile) const override;

    // We override GetChannelVolume and GetChannelPan to apply to the children
    float GetChannelVolume(int channel) const override;
    void SetChannelVolume(int channel, float volume) override;

private:
    bool m_expanded{true};
    std::vector<int> m_childTracks;
};
