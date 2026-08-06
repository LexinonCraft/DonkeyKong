# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Girder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Barrel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Ladder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Level.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/DemoLevel.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/BarrelControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlayerControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlatformPainter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/EntityPainter.cpp
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    )

# add src code to target
add_executable(DonkeyKong
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )