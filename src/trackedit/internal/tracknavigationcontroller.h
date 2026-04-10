/*
* Audacity: A Digital Audio Editor
*/

#pragma once

#include "framework/actions/actionable.h"
#include "async/asyncable.h"

#include "framework/global/modularity/ioc.h"
#include "trackedit/iselectioncontroller.h"
#include "actions/iactionsdispatcher.h"
#include "ui/inavigationcontroller.h"

#include "trackedit/internal/itracknavigationcontroller.h"

namespace au::trackedit {
enum class SelectionDirection {
    Up,
    Down
};

<<<<<<< HEAD
class TrackNavigationController : public ITrackNavigationController, public muse::actions::Actionable, public muse::async::Asyncable
{
    muse::Inject<muse::actions::IActionsDispatcher> dispatcher;
    muse::Inject<au::trackedit::ISelectionController> selectionController;
    muse::Inject<muse::ui::INavigationController> navigationController;

public:
=======
class TrackNavigationController : public ITrackNavigationController, public muse::actions::Actionable, public muse::async::Asyncable,
    public muse::Contextable
{
    muse::ContextInject<muse::actions::IActionsDispatcher> dispatcher{ this };
    muse::ContextInject<muse::ui::INavigationController> navigationController{ this };
    muse::ContextInject<au::context::IGlobalContext> globalContext{ this };
    muse::ContextInject<au::trackedit::ISelectionController> selectionController{ this };
    muse::ContextInject<au::trackedit::ITrackeditInteraction> trackeditInteraction{ this };

public:
    TrackNavigationController(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}

>>>>>>> upstream/master
    void init();
    void focusTrackByIndex(const muse::actions::ActionData& args) override;
    void focusPrevTrack() override;
    void focusNextTrack() override;
    void navigateUp(const muse::actions::ActionData& args) override;
    void navigateDown(const muse::actions::ActionData& args) override;
    void toggleSelectionOnFocusedTrack() override;
    void trackRangeSelection() override;
    void multiSelectionUp() override;
    void multiSelectionDown() override;

private:
    void updateSelectionStart(SelectionDirection direction);
    void updateTrackSelection(TrackIdList& selectedTracks, const TrackId& previousFocusedTrack);

    std::optional<TrackId> m_selectionStart;
    std::optional<TrackId> m_lastSelectedTrack;
};
}
