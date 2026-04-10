#pragma once

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

#include "iconnectingdotspainter.h"

#include "au3wrap/au3types.h"
#include "WaveMetrics.h"

namespace au::projectscene {
<<<<<<< HEAD
class ConnectingDotsPainter : public IConnectingDotsPainter
{
    muse::Inject<au::context::IGlobalContext> globalContext;

public:
    ConnectingDotsPainter() = default;
=======
class ConnectingDotsPainter : public IConnectingDotsPainter, public muse::Contextable
{
    muse::ContextInject<au::context::IGlobalContext> globalContext{ this };

public:
    ConnectingDotsPainter(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}
>>>>>>> upstream/master
    void paint(QPainter& painter, const trackedit::ClipKey& clipKey, const IWavePainter::Params& params) override;
};
}
