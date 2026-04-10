/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

#include "uicomponents/qml/Muse/UiComponents/toolbaritem.h"

namespace au::playback {
class PlaybackToolBarBPMItem : public muse::uicomponents::ToolBarItem
{
    Q_OBJECT

    Q_PROPERTY(double currentValue READ currentValue WRITE setCurrentValue NOTIFY currentValueChanged FINAL)

<<<<<<< HEAD
    muse::Inject<context::IGlobalContext> globalContext;
=======
    muse::ContextInject<context::IGlobalContext> globalContext{ this };
>>>>>>> upstream/master

public:
    explicit PlaybackToolBarBPMItem(const muse::ui::UiAction& action, muse::uicomponents::ToolBarItemType::Type type,
                                    QObject* parent = nullptr);

    double currentValue() const;
    void setCurrentValue(double value);

signals:
    void currentValueChanged();

private:
    void onProjectChanged();

    void updateValues();

    context::IPlaybackStatePtr playbackState() const;

    double m_currentValue = 0.0;
};
}
