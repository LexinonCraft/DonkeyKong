# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Girder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Barrel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Ladder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/HammerPowerUp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Stage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/util/BaseEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/components/ClimbableComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/components/PlatformComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/components/UpdatableComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/util/EntityRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/DrawableComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/PlayerData.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/components/EnemyComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/components/PickableComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/StageSequence.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/stages/Stage25M.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/stages/Stage100M.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/DissolvingPlatform.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/StageControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/TitleScreenControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/StageTransitionControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/GameOverControl.cpp
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/StageView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/LayerStack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/TitleScreenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/AssetsManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/AbstractSceneView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/StageTransitionView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/GameOverView.cpp
    )

# Utility
set(UtilSources
    ${CMAKE_CURRENT_SOURCE_DIR}/util/Positions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util/Math.cpp
    )

# add src code to target
add_executable(DonkeyKong
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${UtilSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )
