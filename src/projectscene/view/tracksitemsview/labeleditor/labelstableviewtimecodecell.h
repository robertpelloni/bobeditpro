/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include <QObject>

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"
#include "playback/iplayback.h"

#include "uicomponents/qml/Muse/UiComponents/internal/tableviewcell.h" // todo: public?

namespace au::projectscene {
<<<<<<< HEAD
class LabelsTableViewTimecodeCell : public muse::uicomponents::TableViewCell
=======
class LabelsTableViewTimecodeCell : public muse::uicomponents::TableViewCell, public muse::Contextable
>>>>>>> upstream/master
{
    Q_OBJECT
    QML_ELEMENT;

    Q_PROPERTY(double sampleRate READ sampleRate NOTIFY sampleRateChanged FINAL)
    Q_PROPERTY(double tempo READ tempo NOTIFY timeSignatureChanged FINAL)
    Q_PROPERTY(int upperTimeSignature READ upperTimeSignature NOTIFY timeSignatureChanged FINAL)
    Q_PROPERTY(int lowerTimeSignature READ lowerTimeSignature NOTIFY timeSignatureChanged FINAL)

<<<<<<< HEAD
    muse::Inject<context::IGlobalContext> globalContext;
    muse::Inject<playback::IPlayback> playback;
=======
    muse::ContextInject<context::IGlobalContext> globalContext{ this };
    muse::ContextInject<playback::IPlayback> playback{ this };
>>>>>>> upstream/master

public:
    explicit LabelsTableViewTimecodeCell(QObject* parent = nullptr);
    LabelsTableViewTimecodeCell(const TableViewCell* other);

    double sampleRate() const;
    double tempo() const;
    int upperTimeSignature() const;
    int lowerTimeSignature() const;

signals:
    void sampleRateChanged();
    void timeSignatureChanged();
};
}
