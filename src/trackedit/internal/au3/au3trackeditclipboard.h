/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "trackedit/itrackeditclipboard.h"
#include "trackedit/iclipboarddata.h"

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

namespace au::trackedit {
class Au3TrackData;
using Au3TrackDataPtr = std::shared_ptr<Au3TrackData>;

<<<<<<< HEAD
class Au3TrackeditClipboard : public ITrackeditClipboard
{
    muse::Inject<au::context::IGlobalContext> globalContext;

public:
=======
class Au3TrackeditClipboard : public ITrackeditClipboard, public muse::Contextable
{
    muse::GlobalInject<IClipboardData> clipboardData;

    muse::ContextInject<au::context::IGlobalContext> globalContext { this };

public:
    Au3TrackeditClipboard(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}

>>>>>>> upstream/master
    std::vector<ITrackDataPtr> trackDataCopy() const override;
    void clearTrackData() override;
    bool trackDataEmpty() const override;
    size_t trackDataSize() const override;
    void addTrackData(ITrackDataPtr) override;

    void setMultiSelectionCopy(bool newValue) override;
    bool isMultiSelectionCopy() const override;

private:
    friend class Au3TrackEditClipboardTests;

    static std::set<int64_t> getGroupIDs(const std::vector<Au3TrackDataPtr>& tracksData);
    std::vector<int64_t> createNewGroupIDs(const std::set<int64_t>& groupIDs) const;
    static void updateTracksDataWithIDs(const std::vector<Au3TrackDataPtr>& tracksData, const std::set<int64_t>& groupIDs,
                                        const std::vector<int64_t>& newGroupIDs);
};
}
