enable_testing()

# Model
set(ModelSources
    ${CMAKE_SOURCE_DIR}/src/model/Girder.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Barrel.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Ladder.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Level.cpp
    ${CMAKE_SOURCE_DIR}/src/model/DemoLevel.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_SOURCE_DIR}/src/control/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/control/BarrelControl.cpp
    ${CMAKE_SOURCE_DIR}/src/control/PlayerControl.cpp
    ${CMAKE_SOURCE_DIR}/src/control/PlatformPainter.cpp
    ${CMAKE_SOURCE_DIR}/src/control/EntityPainter.cpp
    )

# View
set(ViewSources
    ${CMAKE_SOURCE_DIR}/src/view/Layer.cpp
    )

set(TestSources
    ${CMAKE_CURRENT_SOURCE_DIR}/GameTest.cpp
    )

add_executable(Test
    ${ModelSources}
    ${ControlSources}
    ${ViewSources}
    ${TestSources}
    )
