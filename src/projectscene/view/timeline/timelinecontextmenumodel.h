/**********************************************************************

  Audacity: A Digital Audio Editor

**********************************************************************/

#pragma once

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

#include "uicomponents/qml/Muse/UiComponents/abstractmenumodel.h"

namespace au::projectscene {
class TimelineContextMenuModel : public muse::uicomponents::AbstractMenuModel
{
    Q_OBJECT

<<<<<<< HEAD
    muse::Inject<context::IGlobalContext> globalContext;
=======
    muse::ContextInject<context::IGlobalContext> globalContext { this };
>>>>>>> upstream/master

public:
    Q_INVOKABLE void load() override;

private:

    muse::uicomponents::MenuItemList makeRulerItems();
};
}
