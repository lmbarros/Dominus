# Make QT-generated headers visible
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(DominusSources
    DominusMain.cpp
    DominusMainWindow.cpp)

set(DominusUIs
    DominusMainWindow.ui)

qt4_wrap_ui(DOMINUS_UIS_H
    ${DominusUIs})

qt4_wrap_cpp(DOMINUS_UI_MOC_SRCS
    DominusMainWindow.h)

add_executable(Dominus WIN32
    ${DominusSources}
    ${DOMINUS_UI_MOC_SRCS}
    ${DOMINUS_UIS_H})

set_property(TARGET Dominus
    PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

target_link_libraries(Dominus
    ${QT_LIBRARIES}
    ${QT_QTMAIN_LIBRARY}
    ${QT_QTWEBKIT_LIBRARY})