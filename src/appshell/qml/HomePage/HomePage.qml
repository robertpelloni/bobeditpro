import QtQuick 2.15

import Muse.Ui 1.0
import Muse.UiComponents
import Muse.Dock 1.0

import Audacity.Project 1.0
import Muse.Learn

import "."

DockPage {
    id: root

    property string section: "dashboard"
    property string subSection: ""

    property var window: null

    ProjectsPageModel {
        id: projectsPageHelper
    }

    objectName: "Home"
    uri: "musescore://home"

    onSetParamsRequested: function (params) {
        if (Boolean(params["section"])) {
            setCurrentCentral(params["section"])

            if (Boolean(params["subSection"])) {
                subSection = params["subSection"]
            }
        }
    }

    onSectionChanged: {
        Qt.callLater(root.setCurrentCentral, section)
    }

    function setCurrentCentral(name) {
        if (section === name || !Boolean(name)) {
            return
        }

        section = name

        switch (name) {
        case "dashboard":
            root.central = dashboardComp
            break
        case "learn":
            root.central = learnComp
            break
        // Keep fallback paths in case they are routed to
        case "projects":
            root.central = dashboardComp
            break
        case "account":
            root.central = dashboardComp
            break
        }
    }

    panels: [
        DockPanel {
            id: menuPanel

            objectName: "homeMenu"

            readonly property int maxFixedWidth: 260
            readonly property int minFixedWidth: 76
            readonly property bool iconsOnly: root.window ? root.window.width < (root.window.minimumWidth + maxFixedWidth - minFixedWidth) : false
            readonly property int currentFixedWidth: iconsOnly ? minFixedWidth : maxFixedWidth

            width: currentFixedWidth
            minimumWidth: currentFixedWidth
            maximumWidth: currentFixedWidth

            floatable: false
            closable: false

            HomeMenu {
                currentPageName: root.section
                iconsOnly: menuPanel.iconsOnly
                cloudEnabled: projectsPageHelper.cloudEnabled

                onSelected: function (name) {
                    root.setCurrentCentral(name)
                }
            }
        }
    ]

    central: dashboardComp

    Component {
        id: dashboardComp
        UnifiedDashboard {
            cloudEnabled: projectsPageHelper.cloudEnabled
            projectsModel: projectsPageHelper
        }
    }

    Component {
        id: learnComp

        LearnPage {
            section: root.subSection
        }
    }
}
