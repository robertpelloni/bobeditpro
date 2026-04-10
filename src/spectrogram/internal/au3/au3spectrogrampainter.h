/*
 * Audacity: A Digital Audio Editor
 */
#pragma once

#include "ispectrogrampainter.h"

#include "context/iglobalcontext.h"
#include "au3wrap/au3types.h"

#include "framework/global/modularity/ioc.h"
#include "framework/global/async/asyncable.h"

namespace au::spectrogram {
<<<<<<< HEAD
class Au3SpectrogramPainter final : public ISpectrogramPainter, public muse::async::Asyncable
{
    muse::Inject<context::IGlobalContext> globalContext;

public:
=======
class Au3SpectrogramPainter final : public ISpectrogramPainter, public muse::async::Asyncable, public muse::Contextable
{
    muse::ContextInject<context::IGlobalContext> globalContext { this };

public:
    Au3SpectrogramPainter(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}
>>>>>>> upstream/master
    ~Au3SpectrogramPainter() override = default;

    void init();

    void paintClip(QPainter&, const ClipInfo&, const ViewInfo&, const SelectionInfo&) override;

private:
    std::weak_ptr<au3::Au3Project> m_au3Project;
};
}
