/*
* Audacity: A Digital Audio Editor
*/
#pragma once

#include "uicomponents/qml/Muse/UiComponents/abstracttoolbarmodel.h"

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

namespace au::projectscene {
class UndoRedoToolBarModel : public muse::uicomponents::AbstractToolBarModel
{
    Q_OBJECT

<<<<<<< HEAD
    muse::Inject<au::context::IGlobalContext> context;
=======
    muse::ContextInject<au::context::IGlobalContext> context { this };
>>>>>>> upstream/master

public:

    Q_INVOKABLE void load() override;

private:

    bool m_loaded = false;
};
}
