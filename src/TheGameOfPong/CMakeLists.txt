project(LibTheGameOfPong)

add_library(${PROJECT_NAME} STATIC 
    IGameObject.cpp
    IPlayer.cpp
    PlayerHuman.cpp
    PlayerFollower.cpp
    ElasticBall.cpp
    Scoreboard.cpp
    GameEngine.cpp
    TheGameOfPong.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${Pong-RL_SOURCE_DIR}/include/TheGameOfPong)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
