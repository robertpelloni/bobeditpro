# SetupBobUi.cmake
# Configures the in-tree build of BobUI (custom Qt fork)

message(STATUS "Configuring BobUI (In-tree Qt build)...")

# Ensure the submodule is present
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/bobui/CMakeLists.txt")
    message(FATAL_ERROR "BobUI submodule not found. Please run 'git submodule update --init --recursive'.")
endif()

# Configure BobUI options
# We likely want to build only the necessary parts to save time
set(QT_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(QT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(QT_BUILD_BENCHMARKS OFF CACHE BOOL "" FORCE)

# Add the subdirectory
# Note: bobui is a qtbase fork, so it should define Qt::Core, etc.
add_subdirectory(${CMAKE_SOURCE_DIR}/bobui)

# Define standard Qt lists for downstream consumption (replicating logic from SetupQt6)
set(qt_components
    Core
    Gui
    Widgets
    Network
    Qml
    Quick
    QuickControls2
    QuickWidgets
    ShaderTools
    Xml
    Svg
    Core5Compat
)

set(QT_LIBRARIES
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Network
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::QuickWidgets
    Qt::Xml
    Qt::Svg
    Qt::Core5Compat
)

if(OS_IS_LIN)
    list(APPEND qt_components DBus)
    list(APPEND QT_LIBRARIES Qt::DBus)
endif()

# Since we are building in-tree, we don't need find_package(Qt6).
# However, we might need to expose some variables that find_package usually sets.
set(Qt6_FOUND TRUE)
set(Qt6_VERSION "${QT_REPO_MODULE_VERSION}")

message(STATUS "BobUI Configured. Qt Version: ${Qt6_VERSION}")
