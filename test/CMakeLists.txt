enable_testing()

# Model
set(ModelSources
    ${CMAKE_SOURCE_DIR}/src/model/entities/Girder.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/Barrel.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/Ladder.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/HammerPowerUp.cpp
    ${CMAKE_SOURCE_DIR}/src/model/Stage.cpp
    ${CMAKE_SOURCE_DIR}/src/model/util/BaseEntity.cpp
    ${CMAKE_SOURCE_DIR}/src/model/components/ClimbableComponentRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/model/components/PlatformComponentRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/model/components/UpdatableComponentRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/model/util/EntityRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/model/PlayerData.cpp
    ${CMAKE_SOURCE_DIR}/src/model/components/EnemyComponentRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/model/components/PickableComponentRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/model/StageSequence.cpp
    ${CMAKE_SOURCE_DIR}/src/model/stages/Stage25M.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/DonkeyKong.cpp
    ${CMAKE_SOURCE_DIR}/src/model/stages/Stage100M.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/DissolvingPlatform.cpp
    ${CMAKE_SOURCE_DIR}/src/model/components/JumpableComponentRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/Ghost.cpp
    ${CMAKE_SOURCE_DIR}/src/model/animations/PlayerDeathAnimation.cpp
    ${CMAKE_SOURCE_DIR}/src/model/animations/Stage25MCompletionAnimation.cpp
    ${CMAKE_SOURCE_DIR}/src/model/animations/Stage100MCompletionAnimation.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/Pauline.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/Beam.cpp
    ${CMAKE_SOURCE_DIR}/src/model/entities/BarrelStack.cpp
    )

# Controller
set(ControlSources
    ${CMAKE_SOURCE_DIR}/src/control/Game.cpp
    ${CMAKE_SOURCE_DIR}/src/control/GameOverControl.cpp
    ${CMAKE_SOURCE_DIR}/src/control/StageControl.cpp
    ${CMAKE_SOURCE_DIR}/src/control/TitleScreenControl.cpp
    )

# View
set(ViewSources
    ${CMAKE_SOURCE_DIR}/src/view/renderers/BarrelRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/BarrelStackRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/BeamRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/DissolvingPlatformRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/DonkeyKongRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/GhostRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/GirderRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/HammerRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/LadderRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/PaulineRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/renderers/PlayerRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/views/AbstractSceneView.cpp
    ${CMAKE_SOURCE_DIR}/src/view/views/GameOverView.cpp
    ${CMAKE_SOURCE_DIR}/src/view/views/StageTransitionView.cpp
    ${CMAKE_SOURCE_DIR}/src/view/views/StageView.cpp
    ${CMAKE_SOURCE_DIR}/src/view/views/TitleScreenView.cpp
    ${CMAKE_SOURCE_DIR}/src/view/AssetsManager.cpp
    ${CMAKE_SOURCE_DIR}/src/view/DrawableComponentRepository.cpp
    ${CMAKE_SOURCE_DIR}/src/view/DrawableComponentFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/view/Layer.cpp
    ${CMAKE_SOURCE_DIR}/src/view/LayerStack.cpp
    ${CMAKE_SOURCE_DIR}/src/view/ScoreEffect.cpp
    )

# Utility
set(UtilSources
    ${CMAKE_SOURCE_DIR}/src/util/Positions.cpp
    ${CMAKE_SOURCE_DIR}/src/util/Math.cpp
    )

set(TestSources
    ${CMAKE_CURRENT_SOURCE_DIR}/GameTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TestStage.cpp
    )

add_executable(Test
    ${ModelSources}
    ${ControlSources}
    ${ViewSources}
    ${UtilSources}
    ${TestSources}
    )
