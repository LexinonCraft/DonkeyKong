# Model
set(ModelSources
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Girder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Barrel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/BarrelStack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Beam.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Ladder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/HammerPowerUp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/Stage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/util/BaseEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/components/Climbable.cpp
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
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/DonkeyKong.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Pauline.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/stages/Stage100M.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/DissolvingPlatform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/components/JumpableComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/entities/Ghost.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/animations/PlayerDeathAnimation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/animations/Stage25MCompletionAnimation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/model/animations/Stage100MCompletionAnimation.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_CURRENT_SOURCE_DIR}/control/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/GameOverControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/StageControl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/control/TitleScreenControl.cpp
    )

# View
set(ViewSources
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/BarrelRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/BarrelStackRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/BeamRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/DissolvingPlatformRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/DonkeyKongRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/GhostRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/GirderRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/HammerRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/LadderRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/PaulineRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/renderers/PlayerRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/DrawableComponentFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/views/AbstractSceneView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/views/GameOverView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/views/StageTransitionView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/views/StageView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/views/TitleScreenView.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/AssetsManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/DrawableComponentRepository.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/Layer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/LayerStack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/view/ScoreEffect.cpp
    )

# Utility
set(UtilSources
    ${CMAKE_CURRENT_SOURCE_DIR}/util/Positions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util/Math.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util/Format.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/util/GlibcCompat.cpp
    )

# add src code to target
add_executable(DonkeyKong
        ${ModelSources}
        ${ControlSources}
        ${ViewSources}
        ${UtilSources}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        )
