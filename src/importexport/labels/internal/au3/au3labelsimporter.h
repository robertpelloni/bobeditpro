/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

#include "../../ilabelsimporter.h"

namespace au::importexport {
class Au3LabelsImporter : public ILabelsImporter, public muse::Contextable
{
    muse::ContextInject<context::IGlobalContext> globalContext = { this };

public:
<<<<<<< HEAD
    Au3LabelsImporter() = default;
=======
    Au3LabelsImporter(const muse::modularity::ContextPtr& ctx)
        : muse::Contextable(ctx) {}
>>>>>>> upstream/master

    muse::Ret importData(const muse::io::path_t& filePath) override;
};
}
