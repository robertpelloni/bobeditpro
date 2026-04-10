#pragma once

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

#include "isamplespainter.h"

#include "au3wrap/au3types.h"
#include "WaveMetrics.h"

namespace au::projectscene {
<<<<<<< HEAD
class SamplesPainter : public ISamplesPainter
{
    muse::Inject<au::context::IGlobalContext> globalContext;

public:
    SamplesPainter() = default;
=======
class SamplesPainter : public ISamplesPainter, public muse::Contextable
{
    muse::ContextInject<au::context::IGlobalContext> globalContext{ this };

public:
    SamplesPainter(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}
>>>>>>> upstream/master
    void paint(QPainter& painter, const trackedit::ClipKey& clipKey, const IWavePainter::Params& params) override;
};
}
