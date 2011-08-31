# Make QT-generated headers visible
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(DominusSources
    DominusMain.cpp
    WebPage.cpp)

qt4_wrap_cpp(DOMINUS_MOC_SRCS
    WebPage.hpp)

add_executable(Dominus WIN32
    ${DominusSources}
    ${DOMINUS_MOC_SRCS})

set_property(TARGET Dominus
    PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

target_link_libraries(Dominus
    ${QT_LIBRARIES}
    ${QT_QTMAIN_LIBRARY}
    ${QT_QTWEBKIT_LIBRARY})
