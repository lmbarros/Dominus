# Make QT-generated headers visible
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    diluculum/include)

set(DominusSources
    DominusMain.cpp
    ScriptRunner.cpp

    # Lua
    lua/src/all.c

    # Diluculum
    diluculum/Sources/InternalUtils.cpp
    diluculum/Sources/LuaExceptions.cpp
    diluculum/Sources/LuaFunction.cpp
    diluculum/Sources/LuaState.cpp
    diluculum/Sources/LuaUserData.cpp
    diluculum/Sources/LuaUtils.cpp
    diluculum/Sources/LuaValue.cpp
    diluculum/Sources/LuaVariable.cpp
    diluculum/Sources/LuaWrappers.cpp)

if(CMAKE_SYSTEM MATCHES "Linux")
    add_definitions(-DLUA_USE_LINUX)
endif(CMAKE_SYSTEM MATCHES "Linux")


qt4_wrap_cpp(DOMINUS_MOC_SRCS
    ScriptRunner.hpp)

add_executable(Dominus WIN32
    ${DominusSources}
    ${DOMINUS_MOC_SRCS})

set_property(TARGET Dominus
    PROPERTY RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

target_link_libraries(Dominus
    ${QT_LIBRARIES}
    ${QT_QTMAIN_LIBRARY}
    ${QT_QTWEBKIT_LIBRARY})
