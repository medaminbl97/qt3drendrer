cmake_minimum_required(VERSION 3.16)

project(qt3drenderer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

# Collect all .cpp files from src
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Collect all .h files from inc
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")

#Collect all .ui files from ui
file(GLOB_RECURSE UIS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui")

qt_add_executable(qt3drenderer
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_link_libraries(qt3drenderer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qt3drenderer PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set_target_properties(qt3drenderer PROPERTIES WIN32_EXECUTABLE OFF)


target_include_directories(qt3drenderer PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

include(GNUInstallDirs)
install(TARGETS qt3drenderer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
