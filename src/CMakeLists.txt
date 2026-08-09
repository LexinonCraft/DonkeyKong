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
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/LayerStack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/LevelView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/PlatformPainter.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/EntityPainter.cpp
    )

# add src code to target
add_executable(DonkeyKong
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )