# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Girder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Barrel.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/model/Ladder.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/model/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Level.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/DemoLevel.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/control/PlatformPainter.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/control/EntityPainter.cpp
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/LevelView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/LayerStack.cpp
    )

# Utility
set(UtilSources
#    ${CMAKE_CURRENT_SOURCE_DIR}/util/Repository.cpp
)

# add src code to target
add_executable(DonkeyKong
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${UtilSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )