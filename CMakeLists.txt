cmake_minimum_required(VERSION 3.10.0)
project(Pong-RL
    VERSION 1.0.0
    DESCRIPTION "The Game of Pong with different RL implementations"
    HOMEPAGE_URL "https://github.com/Retr0-code/Pong-RL"
)

set(SRC_THE_GAME_OF_PONG
    src/TheGameOfPong/IGameObject.cpp
    src/TheGameOfPong/IPlayer.cpp
    src/TheGameOfPong/ElasticBall.cpp
    src/TheGameOfPong/PlayerHuman.cpp
    src/TheGameOfPong/TheGameOfPong.cpp
    src/TheGameOfPong/IEnviroment.cpp
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_THE_GAME_OF_PONG})
