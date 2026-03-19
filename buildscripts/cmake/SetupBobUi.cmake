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

# Disable system find_package for Qt modules since we build them in-tree
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6 ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Core ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Gui ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Widgets ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Network ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Qml ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Quick ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6QuickControls2 ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6QuickWidgets ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6ShaderTools ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Xml ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Svg ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Core5Compat ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6DBus ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Concurrent ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_Qt6Test ON CACHE BOOL "" FORCE)
set(CMAKE_DISABLE_FIND_PACKAGE_WrapAtomic ON CACHE BOOL "" FORCE)

# Set found variables to satisfy any manual checks
set(Qt6Core_FOUND TRUE)
set(Qt6Gui_FOUND TRUE)
set(Qt6Widgets_FOUND TRUE)
set(Qt6Network_FOUND TRUE)
set(Qt6Qml_FOUND TRUE)
set(Qt6Quick_FOUND TRUE)
set(Qt6QuickControls2_FOUND TRUE)
set(Qt6QuickWidgets_FOUND TRUE)
set(Qt6ShaderTools_FOUND TRUE)
set(Qt6Xml_FOUND TRUE)
set(Qt6Svg_FOUND TRUE)
set(Qt6Core5Compat_FOUND TRUE)
set(Qt6DBus_FOUND TRUE)
set(Qt6Concurrent_FOUND TRUE)
set(Qt6Test_FOUND TRUE)

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
