enable_testing()

set(ControlSources
    ${CMAKE_SOURCE_DIR}/src/control/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/control/BarrelControl.cpp
    )

set(ModelSources
    ${CMAKE_SOURCE_DIR}/src/model/Girder.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Barrel.cpp
    )

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
